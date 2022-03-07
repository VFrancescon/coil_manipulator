#include <CppLinuxSerial/SerialPort.hpp>
#include <string.h>
using namespace mn::CppLinuxSerial;

class Teslameter{
private:
    void TeslameterSetup();
    

    std::string autoRange = "SENS:FIEL:RANG:AUTO 1";
    std::string fieldTesla = "UNIT:FIEL TESL";
    std::string fetchField = "FETC:FIEL:DC?";

    std::string confirmed = "*OPC";

public:
    SerialPort serialPort;

    Teslameter();
    Teslameter(std::string COM);
    ~Teslameter();

    float SingleAxisReading(int AXIS);
    std::vector<float> AllAxisReading();
};