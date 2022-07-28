#include <opencv/tip_tracking.h>
#include <algorithm>
#include <opencv2/ximgproc.hpp>
#include <a-star/source/AStar.hpp>
#include <math.h>
#define PI 3.14159265

using namespace cv;
Mat IntroducerMask(Mat src);
std::vector<std::string> decodePath(std::vector<Point> path_);

int main(void){
    
    std::string image_path = "/home/vittorio/coil_manipulator/src/opencv/RAL_DEMO_SC3.png";
    Mat img = imread(image_path, IMREAD_COLOR);

    if(img.empty())
    {
        std::cout << "Could not read the image: " << image_path << "\n";
        return 1;
    }

    Mat threshold_img, img_copy, skeleton, cnts_bin;
    int rows,cols;
    rows = img.rows / 8 * 3;
    cols = img.cols / 8 * 3;

    resize(img, img, Size(rows,cols), INTER_LINEAR);
    // Mat introducer_mask = IntroducerMask(img);

    AStar::Vec2i origin, destination, wordlsize;
    wordlsize.x = img.rows;
    wordlsize.y = img.cols;

    AStar::Generator generator;
    generator.setWorldSize(wordlsize);
    generator.setHeuristic(AStar::Heuristic::euclidean);
    generator.setDiagonalMovement(true);
    Point goal(60,60);

    //create a greyscale copy of the image
    cvtColor(img, img_copy, COLOR_BGR2GRAY);
    
    //apply blur and threshold so that only the tentacle is visible
    blur(img_copy, img_copy, Size(5,5));
    threshold(img_copy, threshold_img, 50, 255, THRESH_BINARY); 
    // Mat contourMAT = Mat::zeros(threshold_img.size(), CV_8UC1);;
    // threshold_img.copyTo(contourMAT, introducer_mask);

    //set up vectors for findContours to output to
    std::vector<std::vector<Point> > contours;
    std::vector<Vec4i> hierarchy;
    //find contours, ignore hierarchy
    findContours(threshold_img, contours, hierarchy, RETR_LIST, CHAIN_APPROX_SIMPLE);
    cnts_bin = Mat::zeros(threshold_img.size(), CV_8UC1);
    
    //draw contours and fill the open area
    drawContours(cnts_bin, contours, -1, Scalar(255,255,255), cv::FILLED, LINE_8, hierarchy);
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
    drawContours(img, contours, -1, Scalar(255,255,0), cv::FILLED, LINE_8, hierarchy);
    
    std::vector<Point> cntLine;
    findNonZero(skeleton, cntLine);

    Point endpoint;
    for(auto i: cntLine){
        int neighbor_counter = 0;
        for(int j = -1; j < 2; j++){
            for(int k = -1; k < 2; k++){
                if(j == 0 && k == 0) continue;
                if( (int) skeleton.at<uchar>(i.y+k, i.x+j) > 0  ) neighbor_counter++;
            }
        }
        if(neighbor_counter == 1) endpoint = i;
    }

    // std::cout << "Endpoint at: " << endpoint.x << " , " << endpoint.y << "\n";
    circle(img, endpoint, 4, Scalar(0,0,255), FILLED);
    // putText(img, "Endpoint", endpoint, FONT_HERSHEY_COMPLEX_SMALL, 1.0, Scalar(0,0,255));

    

    
    circle(img, goal, 4, Scalar(0,0,0), FILLED);
    origin = endpoint;    
    destination = goal;


    AStar::CoordinateList path = generator.findPath(origin, destination);
    std::vector<Point> cvPath = AStar::Vec2iToCvPointList(path);
    std::reverse(cvPath.begin(), cvPath.end());
    // polylines(img, cvPath, false, Scalar(255,0,0), 2);
    std::cout << " length of path: " << cntLine.size() << "\n";
    // std::vector<Point> goalPath;
    // for(auto i: path){
    //     goalPath.push_back(Point(i.x, i.y));
    // }
    // for(auto i: goalPath){
    //     circle(img, i, 2, Scalar(255,0,0), FILLED);
    // }
    // std::vector<std::string> InstructionPath = decodePath(cvPath);
    // // for(auto i: InstructionPath) std::cout << i << "\n";
    // for(int i = 0; i < InstructionPath.size(); i++){
    //     std::cout << "From : " << cvPath[i] << " to: " << cvPath[i+1] << " direction: " << InstructionPath[i] << "\n";
    // }
    
    imshow("Tip detection", img);
    // imshow("mask", introducer_mask);
    char c= (char)waitKey(0);
    destroyAllWindows();
    return 0;
}


Mat IntroducerMask(Mat src){
    Mat src_GRAY, element;
    //create a greyscale copy of the image


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
    std::cout << "Top Corners at: " << Top1Corner << " and " << Top2Corner << "\n";
    
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


std::vector<std::string> decodePath(std::vector<Point> path_){
    std::vector<std::string> decodedInstructions;
    int dx, dy, angleD, dxdy;
    double angleF;
    for(int i = 0; i < path_.size(); i++){
        if( i + 1 == path_.size()) break;
        dx = path_[i+1].x - path_[i].x;
        dy = path_[i+1].y - path_[i].y;
        if(dy == 0) {
            angleD = 90;
            decodedInstructions.push_back("Horizontal");
        }
        else {
            dxdy = dx/dy;
            angleF = atan(dxdy) * 180 / PI;
            angleD = (int) angleF;
            if(angleD > 0) decodedInstructions.push_back("Right");
            else if ( angleD < 0 ) decodedInstructions.push_back("Left");
            else if ( angleD == 0 ) decodedInstructions.push_back("Down");
            // std::cout << "tan(" << dx << " , " <<  dy << ") = " <<  angleD << "\n";
        }
        
    }
    return decodedInstructions;    
    
}
