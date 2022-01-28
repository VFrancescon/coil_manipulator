#include <opencv/camera_test.h>

static const uint32_t c_countOfImagesToGrab = 100000;

using namespace cv;
int main(int argc, char** argv){
    int exitCode = 0;
    cv::namedWindow("Display Window", WINDOW_AUTOSIZE);
    

    Pylon::PylonInitialize();
    
    Pylon::CImageFormatConverter formatConverter;
    formatConverter.OutputPixelFormat= Pylon::PixelType_BGR8packed;
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

        cv::Size frameSize= Size((int)width.GetValue(), (int)height.GetValue());
        int codec = cv::VideoWriter::fourcc('M', 'J', 'P', 'G');

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