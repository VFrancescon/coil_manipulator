/**
 * @file 15JulTests.cpp
 * @author Vittorio Francescon (vittorio.francescon@gmail.com)
 * @brief Scripts for 15th of July experiments. 
 * Consolidates middleware_test.cpp & src/tip_tracking.cpp
 * @version 0.1
 * @date 14-07-2022
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#include <iostream>
#include <opencv/tip_tracking.h>
#include <algorithm>
#include <opencv2/ximgproc.hpp>
#include <opencv2/video.hpp>
#include <a-star/source/AStar.hpp>
#include <fstream>
#include <middleware_test.h>


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
 * @brief Generates a mask to cover the introducer. Call this function before streaming the video.
 * 
 * @param src Input matrix. The initial setup featuring introducer only
 * @return Mat 8-bit 1 channel binary matrix. Use as a mask to hide the introducer.
 */
Mat IntroducerMask(Mat src);

int threshold_low = 60;
int threshold_high = 255;

int main(int argc, char ** argv){

std::string filename = "/home/vittorio/coil_manipulator/Uopt2_Nav2_OPT2RE.csv";
    
    /*
    SETUP FOR MIDDLEWARE STARTS HERE
    */
    if(argc == 2) {
        filename = argv[1];
        }
    
    std::ifstream file(filename, std::ios::in);
    std::string line, word;
    
    getline(file,line);

    while(std::getline(file, line)){
        int counter = 0;
        std::stringstream sstr(line);
        // std::cout << line << "\n";
        while(std::getline(sstr, word, ',')){

            if(counter == 6) bx.push_back(std::stof(word));
            if(counter == 7) by.push_back(std::stof(word));
            if(counter == 8) bz.push_back(std::stof(word));
            counter++;
        }
    }
    // MiddlewareLayer mid("/dev/ttyUSB2","/dev/ttyUSB3", "/dev/ttyUSB1", "/dev/ttyUSB4", "/dev/ttyUSB0");
    MiddlewareLayer mid;
    /*
    SETUP FOR MIDDLEWARE ENDS HERE
    */
    
    std::thread th1(&MiddlewareLayer::set3DVector, &mid, bx, by, bz);
    
    VideoCapture cap("/home/vittorio/coil_manipulator/src/opencv/BothRoutes_INOUT_V1.mp4");
    if(!cap.isOpened()){
	    std::cout << "Error opening video stream or file" << "\n";
	    return -1;
    }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    mid.set3DVector(bx, by, bz);

}