#include <opencv/tip_tracking.h>
#include <algorithm>
#include <opencv2/ximgproc.hpp>

using namespace cv;

int main(void){
    
    std::string image_path = "/home/vittorio/coil_manipulator/src/opencv/RAL_DEMO_SC3.png";
    Mat img = imread(image_path, IMREAD_COLOR);

    if(img.empty())
    {
        std::cout << "Could not read the image: " << image_path << "\n";
        return 1;
    }

    Mat canny, threshold_img, img_copy, skeleton, cnts_bin;
    int rows,cols;
    rows = img.rows / 2;
    cols = img.cols / 2;

    resize(img, img, Size(rows, cols), INTER_LINEAR);

    //create a greyscale copy of the image
    cvtColor(img, img_copy, COLOR_BGR2GRAY);
    
    //apply blur and threshold so that only the tentacle is visible
    blur(img_copy, img_copy, Size(5,5));
    threshold(img_copy, threshold_img, 50, 255, THRESH_BINARY); 
    
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
    
    //take the filled contour and thin it using Zhang Suen method. 
    ximgproc::thinning(cnts_bin, skeleton, 0);

    //find contours of the skeleton
    contours.clear();
    hierarchy.clear();
    findContours(skeleton, contours, hierarchy, RETR_LIST, CHAIN_APPROX_SIMPLE);
    
    //draw the contour on the image for visualisation purposes
    drawContours(img, contours, -1, Scalar(255,255,0), 1, LINE_8, hierarchy);
    // std::cout << "size of skeleton contour is: " << contours.size() << "\n";
    
    //find rightmost point of the skeleton contour
    Point extRight = (
        *std::max_element(contours[0].begin(), contours[0].end(),
                    [](const Point& lhs, const Point& rhs) {
                        return (lhs.x < rhs.x);}
    ));

    //mark the rightmost point
    circle(img, extRight, 4, Scalar(0,0,255), FILLED);
    putText(img, "extRight", extRight, FONT_HERSHEY_COMPLEX_SMALL, 1.0, Scalar(255,255,255));

    //find downmost point of the skeleton contour
    Point extDown = (
        *std::max_element(contours[0].begin(), contours[0].end(),
                    [](const Point& lhs, const Point& rhs) {
                        return (lhs.y < rhs.y);}
    ));

    //mark the rightmost point
    circle(img, extDown, 4, Scalar(0,0,255), FILLED);
    putText(img, "extDown", extDown, FONT_HERSHEY_COMPLEX_SMALL, 1.0, Scalar(255,255,255));

    //find rightmost downmost point of the skeleton contour
    Point extDownRight = (
        *std::max_element(contours[0].begin(), contours[0].end(),
                    [](const Point& lhs, const Point& rhs) {
                        return (lhs.x < rhs.x && lhs.y < rhs.y);}
    ));

    //mark the rightmost point
    circle(img, extDownRight, 4, Scalar(0,0,255), FILLED);
    putText(img, "extDownRight", extDownRight, FONT_HERSHEY_COMPLEX_SMALL, 1.0, Scalar(255,255,255));


    //show the results
    imshow("Tip detection", img);
    // imshow("Skeleton", skeleton);
    
    char c= (char)waitKey(0);
    
    destroyAllWindows();
    return 0;
}