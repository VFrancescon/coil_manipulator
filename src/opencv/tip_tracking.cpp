#include <opencv/tip_tracking.h>
#include <algorithm>
#include <opencv2/ximgproc.hpp>

using namespace cv;

int main(void){
    std::string image_path = "/home/vittorio/coil_manipulator/src/opencv/RAL_DEMO_SC2.png";
    Mat img = imread(image_path, IMREAD_COLOR);

    if(img.empty())
    {
        std::cout << "Could not read the image: " << image_path << "\n";
        return 1;
    }
    // imshow("Display window", img);
    Mat canny, threshold_img, img_copy, skeleton, cnts_bin;

    cvtColor(img, img_copy, COLOR_BGR2GRAY);
    blur(img_copy, img_copy, Size(5,5));
    threshold(img_copy, threshold_img, 60, 255, THRESH_BINARY); 
    
    

    // int canny_th = 170;
    // Canny(img_copy, canny, canny_th, canny_th*3, 3);

    std::vector<std::vector<Point> > contours;
    std::vector<Vec4i> hierarchy;
    findContours(threshold_img, contours, hierarchy, RETR_LIST, CHAIN_APPROX_SIMPLE);
    
    cnts_bin = Mat::zeros(threshold_img.size(), CV_8UC1);
    drawContours(cnts_bin, contours, -1, Scalar(255,255,255), CV_FILLED, LINE_8, hierarchy);
    skeleton = Mat::zeros(img_copy.rows, img_copy.rows, CV_8U);
    bitwise_not(cnts_bin, cnts_bin);
    ximgproc::thinning(cnts_bin, skeleton, 0);

    contours.clear();
    hierarchy.clear();
    findContours(skeleton, contours, hierarchy, RETR_LIST, CHAIN_APPROX_SIMPLE);
    std::cout << "size of skeleton contour is: " << contours.size() << "\n";
    
    Point extRight = (
        *std::max_element(contours[0].begin(), contours[0].end(),
                      [](const Point& lhs, const Point& rhs) {
                        return (lhs.x < rhs.x);}
    ));

    
    circle(img, extRight, 8, Scalar(0,0,255), FILLED);
    putText(img, "extRight", extRight, FONT_HERSHEY_COMPLEX_SMALL, 1.0, Scalar(255,255,255));


    /**
     * @brief convex hull intersections method below
     * 
     */
    // Mat dst = Mat::zeros(canny.rows, canny.cols, CV_8UC3);
    
    // RNG rng;
    
    // std::vector<std::vector<Point>> hull(contours.size());
    
    // for(int i = 0; i < contours.size(); i++){
    //     convexHull(contours[i], hull[i]);
    // }
    
    // std::vector<Point> intersects;
    // for(int i = 0; i < hull.size(); i++){
    //     std::vector<Point> hull_pts = hull[i];
    //     std::vector<Point> contour_pts = contours[i];
    //     for(auto j: hull_pts){
    //         for(auto k: contour_pts){
    //             if( j.x == k.x && j.y == k.y) intersects.push_back(j);
    //         }
    //     }
    // }

    // for(auto i: intersects){
    //     Scalar rand_col(rng.uniform(0, 256), rng.uniform(0,256), rng.uniform(0,256));
    //     circle(img_copy, i, 8, rand_col, FILLED);
    // }

    // for(int i = 0; i < contours.size(); i++){
    //     Scalar rand_col(rng.uniform(0, 256), rng.uniform(0,256), rng.uniform(0,256));
    //     drawContours( img_copy, contours, i, rand_col, 2, 8, hierarchy );
    //     drawContours(img_copy, hull, i, rand_col, 2);
        
    // }

    

    //moments centroid method
    // Moments mu = moments(outline);
    // Point centroid( (int)(mu.m10/mu.m00),(int)(mu.m01/mu.m00) );
    // double orientation = 0.5 * cvFastArctan(2*mu.m11, mu.m20-mu.m02);
    // Point endp( (int) (600*cos(orientation) ) + centroid.x, (int) (600*sin(orientation) ) + centroid.y);
    // circle(img_copy, centroid, 8, Scalar(0,255,255), FILLED);
    // putText(img_copy, "centroid", centroid, FONT_HERSHEY_COMPLEX_SMALL, 1.0, Scalar(255,255,255));
    // line(img_copy, centroid, endp, Scalar(255,0,255), 2);


    
    
    
    
    // //rightmost point method
    // Point extRight = (
    //     *std::max_element(outline.begin(), outline.end(),
    //                   [](const Point& lhs, const Point& rhs) {
    //                     return (lhs.x < rhs.x);}
    // ));

    
    // circle(img_copy, extRight, 8, Scalar(0,0,255), FILLED);
    // putText(img_copy, "extRight", extRight, FONT_HERSHEY_COMPLEX_SMALL, 1.0, Scalar(255,255,255));




    // //middle index of contour method
    // int midpoint = outline.size()/2;

    // circle(img_copy, outline[midpoint], 8, Scalar(0,0,255), FILLED);
    // putText(img_copy, "mid", outline[midpoint], FONT_HERSHEY_COMPLEX_SMALL, 1.0, Scalar(255,255,255));





    // //lenght of the contour method
    // int x1, x2, y1, y2;
    // int SquareSum = 0;
    // int mid_index;
    // for(int i = 0; i < outline.size(); i++){
    //     if(i+1 == outline.size() ) break;
    //     x1 = outline[i].x;
    //     x2 = outline[i+1].x;
    //     y1 = outline[i].y;
    //     y2 = outline[i+1].y;
    //     SquareSum += (x2-x1)*(x2-x1) + (y2-y1)*(y2-y1);
    //     // std::cout << "x2-x1: " << x2-x1 << " y2-y1: " << y2-y1 << "\n";
    // }
    // std::cout << "lenght of the line: " << sqrt(SquareSum) << " Squared " << SquareSum << "\n";
    // int half_SquareSum = SquareSum/25 * 14;
    // double mid_length = (sqrt(SquareSum)) /2;
    // std::cout << "Mid lenght: " << mid_length << "\n";
    // SquareSum = 0;
    // for(int i = 0; i < outline.size(); i++){
    //     if(i+1 == outline.size() ) break;
    //     x1 = outline[i].x;
    //     x2 = outline[i+1].x;
    //     y1 = outline[i].y;
    //     y2 = outline[i+1].y;
    //     SquareSum += (x2-x1)*(x2-x1) + (y2-y1)*(y2-y1);
    //     if(SquareSum >= half_SquareSum) {
    //         std::cout << "SquareSum: " << SquareSum << " halfSquare " << half_SquareSum << "\n";
    //         mid_index = i;
    //         break;
    //     }
    // }
    // std::cout << "available indeces: " << outline.size() << " length-wise mid at: " << mid_index << "\n"; 
    // circle(img_copy, outline[mid_index], 8, Scalar(0,0,255), FILLED);
    // putText(img_copy, "mid_l", outline[mid_index], FONT_HERSHEY_COMPLEX_SMALL, 1.0, Scalar(255,255,255));

    
    
    imshow("Tip detection", img);
    // imshow("Skeleton", skeleton);
    // std::cout << "contour contains " << contours.size() << " items. \n";
    // std::cout << "There are " << points.size() << " points in the main one\n";
    // imshow("Contour", dst);
    int k = waitKey(0); // Wait for a keystroke in the window

    

}