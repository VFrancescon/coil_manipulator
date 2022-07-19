#include <opencv/tip_tracking.h>
#include <algorithm>
#include <opencv2/ximgproc.hpp>
#include <opencv2/video.hpp>
#include <a-star/source/AStar.hpp>
#include <fstream>
#include <chrono>
#include <unistd.h>

using namespace cv;
/**
 * @brief comparator function for std::sort. Do not use directly.
 * 
 * Compares x components of two points and puts the greater x on the right
 * 
 * @param lhs Left hand side Point
 * @param rhs Right hand side Point
 * @return true 
 * @return false 
 */
bool xWiseSort(Point lhs, Point rhs);

/**
 * @brief Currently Unused. Looks at a binary (8-bit 1 channel) Matrix and deletes isolated pixels
 * 
 * @param src source matrix (8C1U)
 * @param iterations number of iterations to run the function for
 * @return Mat matrix without the isolated pixels
 */
Mat continuityCheck(Mat src, int iterations=1);

/**
 * @brief Generates a mask to cover the introducer. Call this function before streaming the video.
 * 
 * @param src Input matrix. The initial setup featuring introducer only
 * @return Mat 8-bit 1 channel binary matrix. Use as a mask to hide the introducer.
 */
Mat IntroducerMask(Mat src);

int threshold_low = 189;
int threshold_high = 255;
const int target_frame_rate = 60;
const int target_proc_period =  1 / (double )target_frame_rate * 10e6;
int slowed_count = 0;
int main(void){
    AStar::Generator generator;

    /*Video input stuff starts here
    -----------------------------------------------------------
    */
    // VideoCapture cap("/home/vittorio/coil_manipulator/src/opencv/BothRoutes_INOUT_V1.mp4");
    // if(!cap.isOpened()){
	//     std::cout << "Error opening video stream or file" << "\n";
	//     return -1;
    // }

    Mat img, threshold_img, img_copy, skeleton, cnts_bin, masked_img;
    Mat grid;
    int rows,cols;
    int max_lenght = 0, jointCount = 0;

    // cap >> img;
    // rows = img.rows * 3 / 8;
    // cols = img.cols * 3 / 8; 
    //make image smaller 
    // resize(img, img, Size(rows, cols), INTER_LINEAR);
    /*
    -----------------------------------------------------------
    Video input stuff ends here*/

    
    /*pylon video input here
    -----------------------------------------------------------*/
    Pylon::PylonInitialize();
    Pylon::CImageFormatConverter formatConverter;
    formatConverter.OutputPixelFormat = Pylon::PixelType_BGR8packed;
    Pylon::CPylonImage pylonImage;
    Pylon::CInstantCamera camera(Pylon::CTlFactory::GetInstance().CreateFirstDevice() );
    camera.Open();
    Pylon::CIntegerParameter width     ( camera.GetNodeMap(), "Width");
    Pylon::CIntegerParameter height    ( camera.GetNodeMap(), "Height");
    Pylon::CEnumParameter pixelFormat  ( camera.GetNodeMap(), "PixelFormat");
    Size frameSize= Size((int)width.GetValue(), (int)height.GetValue());
    int codec = VideoWriter::fourcc('M', 'J', 'P', 'G');
    width.TrySetValue(640, Pylon::IntegerValueCorrection_Nearest);
    height.TrySetValue(480, Pylon::IntegerValueCorrection_Nearest);
    Pylon::CPixelTypeMapper pixelTypeMapper( &pixelFormat);
    Pylon::EPixelType pixelType = pixelTypeMapper.GetPylonPixelTypeFromNodeValue(pixelFormat.GetIntValue());
    camera.StartGrabbing(Pylon::GrabStrategy_LatestImageOnly);
    Pylon::CGrabResultPtr ptrGrabResult;
    camera.RetrieveResult(5000, ptrGrabResult, Pylon::TimeoutHandling_ThrowException);
    const uint8_t* preImageBuffer = (uint8_t*) ptrGrabResult->GetBuffer();
    formatConverter.Convert(pylonImage, ptrGrabResult);
    img = cv::Mat(ptrGrabResult->GetHeight(), ptrGrabResult->GetWidth(), CV_8UC3, (uint8_t *) pylonImage.GetBuffer());
    /*-----------------------------------------------------------
    pylon video input here*/

    
    // VideoWriter video_out("output.avi", CV_FOURCC('M', 'J', 'P', 'G'), 10, 
    //             Size(img.rows * 3 / 8, img.cols * 3 / 8));
    Mat intr_mask = Mat::zeros(img.size(), CV_8UC1);
    intr_mask = IntroducerMask(img);    
    
    // AStar::Vec2i worldSize;
    // worldSize.x = img.rows;
    // worldSize.y = img.cols;
    // generator.setWorldSize(worldSize);
    // generator.setHeuristic(AStar::Heuristic::manhattan);
    // generator.setDiagonalMovement(true);
    // Point Goal(300,300);
    // AStar::Vec2i origin, destination;
    // destination = Goal;
    // std::vector<Point> cvPath;
    // std::cout << "image size: " << img.rows << " " << img.cols << "\n";

    // while(camera.IsGrabbing()){
    while(true){
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

        camera.RetrieveResult(5000, ptrGrabResult, Pylon::TimeoutHandling_ThrowException);
        const uint8_t* pImageBuffer = (uint8_t*) ptrGrabResult->GetBuffer();
        formatConverter.Convert(pylonImage, ptrGrabResult);
        img = cv::Mat(ptrGrabResult->GetHeight(), ptrGrabResult->GetWidth(), CV_8UC3, (uint8_t *) pylonImage.GetBuffer());

        // cap >> img;

        // if(img.empty()) break;
        // sizes down from 1544x2048 to 579x774
        // rows = img.rows * 3 / 8;
        // cols = img.cols * 3 / 8;
        
        //make image smaller 
        // resize(img, img, Size(rows, cols), INTER_LINEAR);
        
        /*flip image about y*/
        // flip(img, img, 1);

        /*flip image about x*/
        // flip(img, img, 0);

        //create a greyscale copy of the image
        cvtColor(img, img_copy, COLOR_BGR2GRAY);
        
        //apply blur and threshold so that only the tentacle is visible
        blur(img_copy, img_copy, Size(5,5));
        threshold(img_copy, threshold_img, threshold_low, threshold_high, THRESH_BINARY_INV); 
        threshold_img.copyTo(masked_img, intr_mask);
        
        //set up vectors for findContours to output to
        std::vector<std::vector<Point> > contours;
        std::vector<Vec4i> hierarchy;
        //find contours, ignore hierarchy
        findContours(masked_img, contours, hierarchy, RETR_LIST, CHAIN_APPROX_SIMPLE);
        cnts_bin = Mat::zeros(masked_img.size(), CV_8UC1);
        
        //draw contours and fill the open area
        drawContours(cnts_bin, contours, -1, Scalar(255,255,255), CV_FILLED, LINE_8, hierarchy);
        //empty matrix. Set up to 8-bit 1 channel data. Very important to set up properly.
        skeleton = Mat::zeros(img_copy.rows, img_copy.rows, CV_8U);
        
        //take the filled contour and thin it using Zhang Suen method. Only works with 8-bit 1 channel data. 
        ximgproc::thinning(cnts_bin, skeleton, 0);

        //find contours of the skeleton
        contours.clear();
        hierarchy.clear();
        findContours(skeleton, contours, hierarchy, RETR_LIST, CHAIN_APPROX_SIMPLE);
        
        //draw the skeleton on the image for visualisation purposes
        drawContours(img, contours, -1, Scalar(255,255,0), CV_FILLED, LINE_8, hierarchy);

        /*end point of the contour starts here*/
        // store all points of the skeleton into a vector
        std::vector<Point> cntLine;
        findNonZero(skeleton, cntLine);
        std::sort(cntLine.begin(), cntLine.end(), xWiseSort);

        
        // if(prevCntLineSize != cntLine.size()) outputFile << frame_count << "," << cntLine.size() << "\n";
        // prevCntLineSize = cntLine.size();

        Point endpoint;

        //iterate over all points
        for(auto i: cntLine){
            int neighbor_counter = 0;
            for(int j = -1; j < 2; j++){
                for(int k = -1; k < 2; k++){
                    if(j == 0 && k == 0) continue;
                    //count neighbors immediately adjecent
                    if( (int) skeleton.at<uchar>(i.y+k, i.x+j) > 0  ) neighbor_counter++;
                }
            }
            //last point to measure 1 neighbor exactly must be the end of the line
            if(neighbor_counter == 1) endpoint = i;
        }

        // std::cout << "Endpoint at: " << endpoint.x << " , " << endpoint.y << "\n";
        circle(img, endpoint, 4, Scalar(0,0,255), FILLED);
        // putText(img, "Endpoint", endpoint, FONT_HERSHEY_COMPLEX_SMALL, 1.0, Scalar(0,0,255)); 
        /*endpoint of the contour ends here*/
        // origin = endpoint;
        // auto asPath = generator.findPath(origin, destination);
        // cvPath = AStar::Vec2iToCvPointList(asPath);
        // polylines(img, cvPath, false, Scalar(0,0,0), 2);


        jointCount = (int) cntLine.size() / 150;
        if(jointCount){
            for(int i = 0; i < jointCount; i++){
                circle(img, cntLine[150*(i)], 4, Scalar(255,0,0), FILLED);
            }
        }

        max_lenght = max((int)cntLine.size(), max_lenght);



        //show the results
        imshow("Tip detection", img);
        // imshow("Masked", intr_mask);
        // video_out.write(img);
        
        char c= (char)waitKey(1);
        if(c==27) break;
        // std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        // int duration_us = int(std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count());
        // if(duration_us < target_proc_period) {
        //     int sleep_time = target_proc_period - duration_us;
        //     double fps_count = 1 / double(duration_us) * 10e6;
        //     std::cout << "Loop takes: " << duration_us << " us or: " << fps_count << "Hz\n"
        //     << "Therefore going to sleep for " << sleep_time  <<"\n-----------\n";
        //     usleep(sleep_time);
        // } else std::cout << "Not slowed down " << slowed_count++ << "\n";
    
    }
    // outputFile.close();
    // cap.release();
    Pylon::PylonTerminate();
    // video_out.release();
    destroyAllWindows();
    
    std::cout << "Max lenght is: " << max_lenght << "\n";
    return 0;
}

Mat IntroducerMask(Mat src){
    Mat src_GRAY, element;
    //create a greyscale copy of the image
    // flip(src, src, 1);

    cvtColor(src, src_GRAY, COLOR_BGR2GRAY);
    
    //apply blur and threshold so that only the tentacle is visible
    blur(src_GRAY, src_GRAY, Size(5,5));
    threshold(src_GRAY, src_GRAY, threshold_low, threshold_high, THRESH_BINARY_INV); 
    
    element = getStructuringElement(MORPH_DILATE, Size(7,7) );
    dilate(src_GRAY, src_GRAY, element);
    
    // std::vector<Point> corners;
    // goodFeaturesToTrack(src_GRAY, corners, 6, 0.01, 10);
    // Point Top1Corner(600,600), Top2Corner(600,600), BottomCorner(0,0);
    
    // for(int i = 0; i < corners.size(); i++){
    //     if(Top1Corner.y >= corners[i].y) {
    //         Top2Corner = Top1Corner;
    //         Top1Corner = corners[i];
    //     }
    //     if(BottomCorner.y < corners[i].y) BottomCorner = corners[i]; 
    // }
    // std::cout << "Top Corners at: " << Top1Corner << " and " << Top2Corner << "\n";
    
    // int xCenter = std::min(Top1Corner.x, Top2Corner.x);
    // int yCenter = std::min(Top1Corner.y, Top2Corner.y);
    // int xWidth = abs( Top2Corner.x - Top1Corner.x);
    // int yWidth = xWidth*2;

    // Rect rect(Top1Corner.x*0.95, Top1Corner.y-xWidth, xWidth*1.25, yWidth);
    // Rect rect(RectCenter, Size(xWidth, yWidth));
    // rectangle( src_GRAY, rect, Scalar(0), FILLED);

    bitwise_not(src_GRAY, src_GRAY);

    return src_GRAY;

}

bool xWiseSort(Point lhs, Point rhs){
    return (lhs.x > rhs.x);
}


//not in use
Mat continuityCheck(Mat src, int iterations){

    std::vector<Point> points;
    findNonZero(src, points);

    for(int i = 0; i < iterations; i++){
        for(auto i: points){
                int neighbor_counter = 0;
                for(int j = -1; j < 2; j++){
                    for(int k = -1; k < 2; k++){
                        if(j == 0 && k == 0) continue;
                        //count neighbors immediately adjecent
                        if( (int) src.at<uchar>(i.y+k, i.x+j) > 0  ) neighbor_counter++;
                    }
                }
                //last point to measure 1 neighbor exactly must be the end of the line
                if(neighbor_counter == 0) src.at<uchar>(i.y, i.x) = (uchar) 0;
        }
    }

    return src;
}


