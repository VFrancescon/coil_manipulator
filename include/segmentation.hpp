#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <iostream>
#include <pylon/PylonIncludes.h>
#include <MatlabEngine.hpp>
#include <MatlabDataArray.hpp>

using namespace std;
using namespace cv;
// using namespace matlab;

// data::TypedArray<uint8_t> normalise_RGB_image(Mat &rgb, matlab::data::ArrayFactory &factory);
cv::Mat get_current_frame(Pylon::CInstantCamera &camera);

matlab::data::Array normalise_RGB_image(Mat &rgb, matlab::data::ArrayFactory &factory){
    matlab::data::TypedArray<double> norm_image = factory.createArray<double>({ rgb.rows, rgb.cols, 3});
    // matlab::data::Array norm_image = factory.createArray({ 1,4 }, { -2.0, 2.0, 6.0, 8.0 });
    
    for (int i = 0; i < rgb.rows; i++){
        for (int j = 0; j < rgb.cols; j++){
            // [Row][Coloumn] = (row, column)
            // cout << rgb.size() << "\n";
            // cout << i << " " << j <<  "\n";
            // cout << rgb.at<uint8_t>(i,j) << "\n";
            Vec3f bgrPixel = rgb.at<Vec3b>(i,j);
            // cout << bgrPixel << "\n";
            for (int k = 2; k >= 0; k--){
                norm_image[i][j][k] = bgrPixel[k] / 255;
                // cout << norm_image[i][j][k] << " ";
            }
            // cout << "\n";
            // norm_image[i][j][] = rgb.at<Vec3f>(i,j); 
        }
    }
    cout << "Normalisation is finished\n";
    return norm_image;
}

cv::Mat get_current_frame(Pylon::CInstantCamera &camera){
    Pylon::CImageFormatConverter formatConverter;
    formatConverter.OutputPixelFormat = Pylon::PixelType_BGR8packed;
    Pylon::CPylonImage pylonImage;
    Mat opencvImage;

    if (camera.IsGrabbing()){
        Pylon::CGrabResultPtr ptrGrabResult;
        camera.RetrieveResult(5000, ptrGrabResult, Pylon::TimeoutHandling_ThrowException);
        // camera.GrabOne(5000, ptrGrabResult, Pylon::TimeoutHandling_ThrowException);

        if(ptrGrabResult->GrabSucceeded()){
            formatConverter.Convert(pylonImage, ptrGrabResult);
            cv::Mat tmpImage = cv::Mat(ptrGrabResult->GetHeight(), ptrGrabResult->GetWidth(), CV_8UC3, (uint8_t *) pylonImage.GetBuffer());
            tmpImage.copyTo(opencvImage);
            // std::cout << opencvImage << "\n";
        } else {
            std::cout << "[ERROR]: Couldn't retrieve the frame!!!\n";
        }
    }
    // opencvImage = cv::Mat::zeros(3,3,CV_32F);
    // std::cout << opencvImage << "\n";
    return opencvImage;
}
