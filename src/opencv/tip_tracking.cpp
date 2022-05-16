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
        
        //draw the contour on the image for visualisation purposes
        drawContours(img, contours, -1, Scalar(255,255,0), 1, LINE_8, hierarchy);
        
        //find rightmost point of the skeleton contour
        Point extRight = (
            *std::max_element(contours[0].begin(), contours[0].end(),
                        [](const Point& lhs, const Point& rhs) {
                            return (lhs.x < rhs.x);}
        ));

        //mark the rightmost point
        circle(img, extRight, 4, Scalar(255,0,0), FILLED);
        putText(img, "extRight", extRight, FONT_HERSHEY_COMPLEX_SMALL, 1.0, Scalar(255,0,0));

        //find downmost point of the skeleton contour
        Point extDown = (
            *std::max_element(contours[0].begin(), contours[0].end(),
                        [](const Point& lhs, const Point& rhs) {
                            return (lhs.y < rhs.y);}
        ));

        //mark the downmost point
        circle(img, extDown, 4, Scalar(0,0,255), FILLED);
        putText(img, "extDown", extDown, FONT_HERSHEY_COMPLEX_SMALL, 1.0, Scalar(0,0,255));

        //find rightmost downmost point of the skeleton contour
        Point extDownRight = (
            *std::max_element(contours[0].begin(), contours[0].end(),
                        [](const Point& lhs, const Point& rhs) {
                            return (lhs.x < rhs.x && lhs.y < rhs.y);}
        ));

        //mark the down-rightmost point
        circle(img, extDownRight, 4, Scalar(0,255,255), FILLED);
        putText(img, "extDownRight", extDownRight, FONT_HERSHEY_COMPLEX_SMALL, 1.0, Scalar(0,255,255));

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