#include <algorithm>
#include <opencv2/ximgproc.hpp>
#include <opencv2/video.hpp>
#include <fstream>
#include <chrono>
#include <unistd.h>
#include <pylon/PylonIncludes.h>

using namespace cv;


int main(int argc, char * argv[])
{
    //trying to force a merge conflict
    auto png = Pylon::EImageFileFormat::ImageFileFormat_Tiff;
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
    width.TrySetValue(640*3, Pylon::IntegerValueCorrection_Nearest);
    height.TrySetValue(480*3, Pylon::IntegerValueCorrection_Nearest);
    Pylon::CPixelTypeMapper pixelTypeMapper( &pixelFormat);
    Pylon::EPixelType pixelType = pixelTypeMapper.GetPylonPixelTypeFromNodeValue(pixelFormat.GetIntValue());
    camera.StartGrabbing(Pylon::GrabStrategy_LatestImageOnly);
    Pylon::CGrabResultPtr ptrGrabResult;
    camera.RetrieveResult(5000, ptrGrabResult, Pylon::TimeoutHandling_ThrowException);
    formatConverter.Convert(pylonImage, ptrGrabResult);
    pylonImage.Save(png, "capture1");
    

    

    return 0;
}
