#include <opencv/tip_tracking.h>
#include <algorithm>
#include <opencv2/ximgproc.hpp>
#include <opencv2/video.hpp>
#include <a-star/source/AStar.hpp>
#include <fstream>

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


int main(void){
    AStar::Generator generator;

    // std::string lenghtCSV = "/home/vittorio/coil_manipulator/TentacleLenght.csv";

    // std::ofstream outputFile(lenghtCSV, std::ios::out);
    // outputFile << "Frame, Point Count\n";
    // int prevCntLineSize = 0, frame_count = 0;

    /*Video input stuff starts here
    -----------------------------------------------------------
    */
    
    
    VideoCapture cap("/home/vittorio/coil_manipulator/src/opencv/BothRoutes_INOUT_V1.mp4");
    if(!cap.isOpened()){
	    std::cout << "Error opening video stream or file" << "\n";
	    return -1;
    }

    Mat img, threshold_img, img_copy, skeleton, cnts_bin, masked_img;
    Mat grid;
    int rows,cols;
    
    cap >> img;
    rows = img.rows * 3 / 8;
    cols = img.cols * 3 / 8;
    
    
    /*
    -----------------------------------------------------------
    Video input stuff ends here*/

    /*pylon video input here
    -----------------------------------------------------------
    */
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
    /*-----------------------------------------------------------
    pylon video input here*/


    AStar::Vec2i worldSize;
    worldSize.x = rows;
    worldSize.y = cols;
    generator.setWorldSize(worldSize);
    generator.setHeuristic(AStar::Heuristic::manhattan);
    generator.setDiagonalMovement(true);
    Point Goal(300,300);

    //make image smaller 
    resize(img, img, Size(rows, cols), INTER_LINEAR);
    // VideoWriter video_out("output.avi", CV_FOURCC('M', 'J', 'P', 'G'), 10, 
    //             Size(img.rows * 3 / 8, img.cols * 3 / 8));
    Mat intr_mask = Mat::zeros(img.size(), CV_8UC1);
    intr_mask = IntroducerMask(img);

    AStar::Vec2i origin, destination;
    destination = Goal;
    std::vector<Point> cvPath;
    // std::cout << "image size: " << img.rows << " " << img.cols << "\n";

    while(1){

        cap >> img;
        if(img.empty()) break;
        // sizes down from 1544x2048 to 579x774
        rows = img.rows * 3 / 8;
        cols = img.cols * 3 / 8;
        
        //make image smaller 
        resize(img, img, Size(rows, cols), INTER_LINEAR);
        
        /*flip image about y*/
        // flip(img, img, 1);

        /*flip image about x*/
        // flip(img, img, 0);

        //create a greyscale copy of the image
        cvtColor(img, img_copy, COLOR_BGR2GRAY);
        
        //apply blur and threshold so that only the tentacle is visible
        blur(img_copy, img_copy, Size(5,5));
        threshold(img_copy, threshold_img, 60, 255, THRESH_BINARY_INV); 
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
        
        // ++frame_count;
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
        origin = endpoint;
        auto asPath = generator.findPath(origin, destination);
        cvPath = AStar::Vec2iToCvPointList(asPath);
        polylines(img, cvPath, false, Scalar(0,0,0), 2);

        //show the results
        imshow("Tip detection", img);
        // video_out.write(img);
        
        char c= (char)waitKey(10);
        if(c==27) break;
    }
    // outputFile.close();
    // cap.release();
    Pylon::PylonTerminate();
    // video_out.release();
    destroyAllWindows();
    return 0;
}

Mat IntroducerMask(Mat src){
    Mat src_GRAY, element;
    //create a greyscale copy of the image
    // flip(src, src, 1);

    cvtColor(src, src_GRAY, COLOR_BGR2GRAY);
    
    //apply blur and threshold so that only the tentacle is visible
    blur(src_GRAY, src_GRAY, Size(5,5));
    threshold(src_GRAY, src_GRAY, 60, 255, THRESH_BINARY_INV); 
    
    element = getStructuringElement(MORPH_DILATE, Size(3,3), Point(1,1) );
    dilate(src_GRAY, src_GRAY, element);
    
    std::vector<Point> corners;
    goodFeaturesToTrack(src_GRAY, corners, 6, 0.01, 10);
    Point Top1Corner(600,600), Top2Corner(600,600), BottomCorner(0,0);
    
    for(int i = 0; i < corners.size(); i++){
        if(Top1Corner.y >= corners[i].y) {
            Top2Corner = Top1Corner;
            Top1Corner = corners[i];
        }
        if(BottomCorner.y < corners[i].y) BottomCorner = corners[i]; 
    }
    // std::cout << "Top Corners at: " << Top1Corner << " and " << Top2Corner << "\n";
    
    int xCenter = std::min(Top1Corner.x, Top2Corner.x);
    int yCenter = std::min(Top1Corner.y, Top2Corner.y);
    int xWidth = abs( Top2Corner.x - Top1Corner.x);
    int yWidth = xWidth*2;

    Rect rect(Top1Corner.x*0.95, Top1Corner.y-xWidth, xWidth*1.25, yWidth);
    // Rect rect(RectCenter, Size(xWidth, yWidth));
    rectangle( src_GRAY, rect, Scalar(0), FILLED);

    bitwise_not(src_GRAY, src_GRAY);

    return src_GRAY;

}

bool xWiseSort(Point lhs, Point rhs){
    return (lhs.x < rhs.x);
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


