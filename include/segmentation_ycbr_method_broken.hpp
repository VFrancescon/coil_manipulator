#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <iostream>
#include <pylon/PylonIncludes.h>

using namespace std;
using namespace cv;

Mat MaskBlack(Mat &frame);
cv::Mat convert_RGB_to_YCBR(Mat &rgb);
cv::Mat get_current_frame(Pylon::CInstantCamera &camera);
int camera_test();


Mat MaskBlack(Mat &frame){
    // Mat converted_frame = convert_RGB_to_YCBR(frame);
    Mat converted_frame;
    cv::cvtColor(frame, converted_frame, cv::COLOR_RGB2YCrCb);
    // Mat new_img;
    // converted_frame.copyTo(new_img);
    // new_img.convertTo(converted_frame, CV_8);
    // cv::cvtColor(frame, converted_frame, cv::COLOR_)
    // cout << cv::mean(new_img.row(20)) << "\n";
    // return converted_frame;
    // procFrame.copyTo(new_input);
    cout << "Conversion finished.\n";
    // Mat procFrame = frame;
    
    // double c1Min = 0.172;
    // double c1Max = 0.303;
    // double c2Min = 0.213;
    // double c2Max = 0.572;
    // double c3Min = 0.482;
    // double c3Max = 0.614;
    double c1Min = 0.0;
    double c1Max = 255.0;
    double c2Min = 0.0;
    double c2Max = 255.0;
    double c3Min = 0.0;
    double c3Max = 255.0;


    Mat mask = Mat::zeros( converted_frame.rows, converted_frame.cols, CV_8UC1 );
    for (int i = 0; i < converted_frame.rows; i++) {
        // cv::mean(converted_frame.row(i))
        for (int j = 0; j < converted_frame.cols; j++) {
            // cout << converted_frame.rows << " " << converted_frame.cols << "\n";
            // cout << i << " " << j << "\n";

            //get bgr pixel
            Vec3f yuvPixel = converted_frame.at<Vec3f>(i, i);
            // cout << yuvPixel << "\n";
            // cout << yuvPixel[0] << "\n";
            // cout << yuvPixel[1] << "\n";
            // cout << yuvPixel[2] << "\n\n";
            

            float Y = yuvPixel[0] / 255;                
            float U = yuvPixel[1] / 255;
            float V = yuvPixel[2] / 255;
            // cout << cv::sqrt(Y*Y + U*U + V*V) << "\n";
            // cout << Y << "\n";

            if ((V >= c1Min && V <= c1Max)) {
                // cout << "correct!\n";
                mask.at<uchar>(i, j) = 255;
            }

            // if ((V >= c1Min && V <= c1Max) &&
            //     (U >= c2Min && U <= c2Max) &&
            //     (Y >= c3Min && Y <= c3Max)) {
            //     cout << "correct!\n";
            //     mask.at<uchar>(i, j) = 255;
            // }
        }
    }
    cout << "MaskBlack finished \n";
    return mask;
}


cv::Mat convert_RGB_to_YCBR(Mat &rgb){
    //sample input and output
    // float data[3][1] = { 98,76,88 };
    // Mat input( 1, 1, CV_32FC3, data) ;
    Mat new_rgb;
    rgb.copyTo(new_rgb);
    Mat output( rgb.rows, rgb.cols, CV_32FC3 );

    //iterate over all pixels
    for(int i = 0; i < new_rgb.rows; i++) {
        for(int j = 0; j < new_rgb.cols; j++) {
            // cout << new_rgb.rows << " " << new_rgb.cols << "\n";
            // cout << i << " " << j << "\n";

            //get bgr pixel
            Vec3f bgrPixel = new_rgb.at<Vec3f>(i, j);

            cout << bgrPixel << "\n";
            // cout << bgrPixel[0] << "\n";
            // cout << bgrPixel[1] << "\n";
            // cout << bgrPixel[2] << "\n\n";

            float B = bgrPixel[0];
            float G = bgrPixel[1];
            float R = bgrPixel[2];

            //actual conversion from BGR to YCrCb
            float delta = 0.5f;
            float Y  = 0.299f * R + 0.587f * G + 0.114f * B;
            float Cb = (B - Y) * 0.564f + delta;
            float Cr = (R - Y) * 0.713f + delta;

            //store into result image
            Vec3f yCrCbPixel( Y, Cr, Cb );
            output.at<Vec3f>(i, j) = yCrCbPixel;
        }
    }
    return output;
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


int camera_test(){
    int exitCode = 0;
    cv::namedWindow("Display Window", WINDOW_AUTOSIZE);


    Pylon::PylonInitialize();
    Pylon::CImageFormatConverter formatConverter;
    formatConverter.OutputPixelFormat = Pylon::PixelType_BGR8packed;
    Pylon::CPylonImage pylonImage;
    Mat opencvImage;


    try{

        const int cFramesPerSecond = 20;
        const uint32_t cQuality = 90;
        Pylon::CInstantCamera camera(Pylon::CTlFactory::GetInstance().CreateFirstDevice() );
        std::cout << "Camera Model: " << camera.GetDeviceInfo().GetModelName() << "\n";

        camera.Open();

        Pylon::CIntegerParameter width( camera.GetNodeMap() , "Width");
        Pylon::CIntegerParameter height( camera.GetNodeMap() , "Height" );
        Pylon::CEnumParameter pixelFormat(camera.GetNodeMap(), "PixelFormat");

        // cv::Size frameSize = Size((int)width.GetValue(), (int)height.GetValue());
        // int codec = cv::VideoWriter::fourcc('M', 'J', 'P', 'G');

        width.TrySetValue(640, Pylon::IntegerValueCorrection_Nearest);
        height.TrySetValue(480, Pylon::IntegerValueCorrection_Nearest);

        Pylon::CPixelTypeMapper pixelTypeMapper( &pixelFormat);
        Pylon::EPixelType pixelType = pixelTypeMapper.GetPylonPixelTypeFromNodeValue(pixelFormat.GetIntValue());


        camera.StartGrabbing(Pylon::GrabStrategy_LatestImageOnly);
        Pylon::CGrabResultPtr ptrGrabResult;

        while(camera.IsGrabbing()){
            camera.RetrieveResult(5000, ptrGrabResult, Pylon::TimeoutHandling_ThrowException);

            if(ptrGrabResult->GrabSucceeded()){
                std::cout << "SizeX: " << ptrGrabResult->GetWidth() << "\n";
                std::cout << "SizeY: " << ptrGrabResult->GetHeight() << "\n";
                const uint8_t* pImageBuffer = (uint8_t*) ptrGrabResult->GetBuffer();
                std::cout << "Grey value of first pixel: " << (uint32_t) pImageBuffer[0] << "\n\n";

                formatConverter.Convert(pylonImage, ptrGrabResult);
                opencvImage = cv::Mat(ptrGrabResult->GetHeight(), ptrGrabResult->GetWidth(), CV_8UC3, (uint8_t *) pylonImage.GetBuffer());
                imshow("Display Window", opencvImage);
                waitKey(25);
            }
        }

    }
    catch(const Pylon::GenericException &e){
        std::cerr << "An exception occurred.\n"
            << e.GetDescription() << "\n";
        exitCode = 1;
    }

    Pylon::PylonTerminate();
    return exitCode;
}
