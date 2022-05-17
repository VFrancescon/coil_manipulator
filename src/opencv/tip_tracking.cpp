#include <opencv/tip_tracking.h>
#include <algorithm>
#include <opencv2/ximgproc.hpp>

using namespace cv;

int main(void){
    
    VideoCapture cap("/home/vittorio/coil_manipulator/src/opencv/BothRoutes_INOUT_V1.mp4");
    if(!cap.isOpened()){
	    std::cout << "Error opening video stream or file" << "\n";
	    return -1;
    }
    Mat img, canny, threshold_img, img_copy, skeleton, cnts_bin;
    int rows,cols;
    while(1){
        cap >> img;
        
        rows = img.rows * 3 / 8;
        cols = img.cols * 3 / 8;

        resize(img, img, Size(rows, cols), INTER_LINEAR);
        
        if(img.empty()) break;

        //create a greyscale copy of the image
        cvtColor(img, img_copy, COLOR_BGR2GRAY);
        
        //apply blur and threshold so that only the tentacle is visible
        blur(img_copy, img_copy, Size(5,5));
        threshold(img_copy, threshold_img, 60, 255, THRESH_BINARY); 
        
        //set up vectors for findContours to output to
        std::vector<std::vector<Point> > contours;
        std::vector<Vec4i> hierarchy;
        //find contours, ignore hierarchy
        findContours(threshold_img, contours, hierarchy, RETR_LIST, CHAIN_APPROX_SIMPLE);
        cnts_bin = Mat::zeros(threshold_img.size(), CV_8UC1);
        
        //draw contours and fill the open area
        drawContours(cnts_bin, contours, -1, Scalar(255,255,255), CV_FILLED, LINE_8, hierarchy);
        //empty matrix. Set up to 8-bit 1 channel data. Very important to set up properly.
        skeleton = Mat::zeros(img_copy.rows, img_copy.rows, CV_8U);
        //invert for thinning to work
        bitwise_not(cnts_bin, cnts_bin);
        
        //take the filled contour and thin it using Zhang Suen method. Only works with 8-bit 1 channel data. 
        ximgproc::thinning(cnts_bin, skeleton, 0);

        //find contours of the skeleton
        contours.clear();
        hierarchy.clear();
        findContours(skeleton, contours, hierarchy, RETR_LIST, CHAIN_APPROX_SIMPLE);
        
        //draw the skeleton on the image for visualisation purposes
        drawContours(img, contours, -1, Scalar(255,255,0), CV_FILLED, LINE_8, hierarchy);
        
        //store all points of the skeleton into a vector
        std::vector<Point> cntLine;
        findNonZero(skeleton, cntLine);
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
        putText(img, "Endpoint", endpoint, FONT_HERSHEY_COMPLEX_SMALL, 1.0, Scalar(0,0,255));

        // Scalar tipCol(0,0,255);
        // //find rightmost point of the skeleton contour
        // Point extRight = (
        //     *std::max_element(contours[0].begin(), contours[0].end(),
        //                 [](const Point& lhs, const Point& rhs) {
        //                     return (lhs.x < rhs.x);}
        // ));

        // if(extRight.y <= 10) {
        //     extRight = (
        //     *std::max_element(contours[0].begin(), contours[0].end(),
        //                 [](const Point& lhs, const Point& rhs) {
        //                     return (lhs.y < rhs.y);}
        //     ));
        //     tipCol = (120,120,255);
        // }

        // //mark the rightmost point
        // circle(img, extRight, 4, tipCol, FILLED);
        // putText(img, "Tip", extRight, FONT_HERSHEY_COMPLEX_SMALL, 1.0, tipCol);


        //show the results
        imshow("Tip detection", img);
        // imshow("Skeleton", skeleton);
        
        char c= (char)waitKey(10);
        if(c==27) break;
    }
    
    cap.release();
    destroyAllWindows();
    return 0;
}