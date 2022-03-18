#include <CppLinuxSerial/SerialPort.hpp>
#include <string.h>
using namespace mn::CppLinuxSerial;

class Teslameter{
private:
    void TeslameterSetup();
    

    std::string autoRange   = "SENS:FIEL:RANG:AUTO 1";
    std::string fieldTesla  = "UNIT:FIEL TESL";
    std::string fetchField  = "FETC:FIEL:DC? ";

    std::string confirmed   = "*OPC?";
    std::string lineFeed    = "\n\0";

public:
    SerialPort serialPort;

    Teslameter();
    Teslameter(std::string COM);
    ~Teslameter();
    
    enum class AXIS{
        X,
        Y,
        Z
    };

    // float SingleAxisReading(int Axis);
    float SingleAxisReading(Teslameter::AXIS Axis);
    std::vector<float> AllAxisReading();
    std::string SimpleSingleAxis();


    
};