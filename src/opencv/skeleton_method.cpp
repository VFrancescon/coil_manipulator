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

    Mat canny, threshold_img, img_copy, skeleton, cnts_bin;
    int rows,cols;
    rows = img.rows /2;
    cols = img.cols /2;

    resize(img, img, Size(rows,cols), INTER_LINEAR);

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
    skeleton = Mat::zeros(img_copy.rows, img_copy.rows, CV_8UC1);
    //invert for thinning to work
    bitwise_not(cnts_bin, cnts_bin);
    
    //take the filled contour and thin it using Zhang Suen method. 
    ximgproc::thinning(cnts_bin, skeleton, 0);

    //find contours of the skeleton
    contours.clear();
    hierarchy.clear();
    findContours(skeleton, contours, hierarchy, RETR_LIST, CHAIN_APPROX_SIMPLE);
    
    //draw the contour on the image for visualisation purposes
    drawContours(img, contours, -1, Scalar(255,255,0), CV_FILLED, LINE_8, hierarchy);
    // std::cout << "size of skeleton contour is: " << contours.size() << "\n";
    
    

    //find rightmost point of the skeleton contour
    // Point extRight = (
    //     *std::max_element(contours[0].begin(), contours[0].end(),
    //                 [](const Point& lhs, const Point& rhs) {
    //                     return (lhs.x < rhs.x);}
    // ));

    // //mark the rightmost point
    // circle(img, extRight, 4, Scalar(0,0,255), FILLED);
    // putText(img, "extRight", extRight, FONT_HERSHEY_COMPLEX_SMALL, 1.0, Scalar(255,255,255));


    //Trying to track the endpoint of a contour
    std::vector<Point> cntLine;
    // Mat cntMat;
    // // bitwise_not(skeleton, skeleton);
    findNonZero(skeleton, cntLine);
    // std::cout << "size of cntLine " << cntLine.size() << "\n";
    // // // bitwise_not(skeleton, skeleton);
    // Point endpoint;
    // for(auto i: cntLine){
    //     int neighbor_counter = 0;
    //     if( (int) skeleton.at<uchar>(i.x-1, i.y+1) > 0 ) neighbor_counter++; 
    //     if( (int) skeleton.at<uchar>(i.x+0, i.y+1) > 0 ) neighbor_counter++;
    //     if( (int) skeleton.at<uchar>(i.x+1, i.y+1) > 0 ) neighbor_counter++;
    //     if( (int) skeleton.at<uchar>(i.x-1, i.y+0) > 0 ) neighbor_counter++;
    //     if( (int) skeleton.at<uchar>(i.x+1, i.y+0) > 0 ) neighbor_counter++;
    //     if( (int) skeleton.at<uchar>(i.x-1, i.y-1) > 0 ) neighbor_counter++;
    //     if( (int) skeleton.at<uchar>(i.x+0, i.y-1) > 0 ) neighbor_counter++;
    //     if( (int) skeleton.at<uchar>(i.x+1, i.y-1) > 0 ) neighbor_counter++;
    //     std::cout << "point x: " << i.x << " y: " << i.y << " neighbor count " << neighbor_counter << "\n";
    //     std::cout << "straight below: " << (int) skeleton.at<uchar>(i.x+0, i.y+1) << "\n";
    //     if(neighbor_counter == 1) endpoint = i;
    // }
    // std::cout << "Endpoint at: " << endpoint.x << " " << endpoint.y<< "\n";
    // circle(img, endpoint, 4, Scalar(255,255,255), FILLED);

    // std::cout << "\nnon-zero count: " << cntLine.size() << " and point count " << point_cnt << "\n";
    Point endpoint;
    for(auto i: cntLine){
        // std::cout << "\n\nNEW POINT: " << i.x << " " << i.y << " holds " << (int) skeleton.at<uchar>(i.y, i.x) <<"\n\n";
        int neighbor_counter = 0;
        for(int j = -1; j < 2; j++){
            for(int k = -1; k < 2; k++){
                if(j == 0 && k == 0) continue;
                // std::cout << "point: " << i.x + j << " , " << i.y+k << " ";
                // // std::cout << "value: " << (int) skeleton.at<uchar>(i.x+j, i.y+k) << "\n";
                // printf("value %d\n", skeleton.at<uchar>(i.y+k, i.x+j));
                if( (int) skeleton.at<uchar>(i.y+k, i.x+j) > 0  ) neighbor_counter++;
            }
        }
        if(neighbor_counter == 1) endpoint = i;
    }

    std::cout << "Endpoint at: " << endpoint.x << " , " << endpoint.y << "\n";
    circle(img, endpoint, 4, Scalar(0,0,255), FILLED);
    putText(img, "Endpoint", endpoint, FONT_HERSHEY_COMPLEX_SMALL, 1.0, Scalar(0,0,255));

    //Line to goal section
    // Point Goal(300,300);
    // circle(img, Goal, 4, Scalar(0,0,255), FILLED);
    // putText(img, "Goal", Goal, FONT_HERSHEY_COMPLEX_SMALL, 1.0, Scalar(0,0,255));

    // line(img, extRight, Goal, Scalar(0,255,255), 1, LINE_8);
    // std::cout << "dx " << abs(extRight.x - Goal.x) << " dy " << abs(extRight.y - Goal.y) << "\n";
    


    
    
    // LineIterator it(img, extRight, Goal, 8);
    
    
    // for(int i = 0; i < it.count; i++, ++it)
    // {
    //     Point pt= it.pos(); 
    //     // std::cout << "Coordinates;";
    // }
    //show the results
    imshow("Tip detection", img);
    // imshow("Skeleton", skeleton);
    // imshow("cntmat", cntMat);
    
    char c= (char)waitKey(0);

    
    destroyAllWindows();
    return 0;
}