#include <opencv/tip_tracking.h>
#include <algorithm>
#include <opencv2/ximgproc.hpp>
#include <opencv2/video.hpp>
#include <fstream>
#include <chrono>
#include <unistd.h>
using namespace cv;
int main(void){
    Mat img;
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
    width.TrySetValue(640*3, Pylon::IntegerValueCorrection_Nearest);
    height.TrySetValue(480*3, Pylon::IntegerValueCorrection_Nearest);
    Pylon::CPixelTypeMapper pixelTypeMapper( &pixelFormat);
    Pylon::EPixelType pixelType = pixelTypeMapper.GetPylonPixelTypeFromNodeValue(pixelFormat.GetIntValue());
    camera.StartGrabbing(Pylon::GrabStrategy_LatestImageOnly);
    Pylon::CGrabResultPtr ptrGrabResult;
    camera.RetrieveResult(5000, ptrGrabResult, Pylon::TimeoutHandling_ThrowException);
    const uint8_t* preImageBuffer = (uint8_t*) ptrGrabResult->GetBuffer();
    formatConverter.Convert(pylonImage, ptrGrabResult);
    img = cv::Mat(ptrGrabResult->GetHeight(), ptrGrabResult->GetWidth(), CV_8UC3, (uint8_t *) pylonImage.GetBuffer());

    // VideoWriter video_out(home_path + "coil_manipulator/output.avi", VideoWriter::fourcc('M', 'J', 'P', 'G'), 10, 
    //             Size(img.rows / 2, img.cols * 3 / 8));

    //resizing the image for faster processing
    int rows = img.rows / 2;
    int cols = img.cols * 3 / 8; 
    resize(img, img, Size(rows, cols), INTER_LINEAR);

    while(camera.IsGrabbing()){
        camera.RetrieveResult(5000, ptrGrabResult, Pylon::TimeoutHandling_ThrowException);
        const uint8_t* pImageBuffer = (uint8_t*) ptrGrabResult->GetBuffer();
        formatConverter.Convert(pylonImage, ptrGrabResult);
        img = cv::Mat(ptrGrabResult->GetHeight(), ptrGrabResult->GetWidth(), CV_8UC3, (uint8_t *) pylonImage.GetBuffer());

        // cap >> img;
        if(img.empty())
        {
            break;
        }
        rows = img.rows / 2;
        cols = img.cols * 3 / 8;
        
        //make image smaller 
        resize(img, img, Size(rows, cols), INTER_LINEAR);

        imshow("Camera Feed", img);
        char c= (char)waitKey(1);
        if(c==27) break;
    }
    Pylon::PylonTerminate();
    destroyAllWindows();
    return 0;
}