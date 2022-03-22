#include <CppLinuxSerial/SerialPort.hpp>
#include <string.h>
using namespace mn::CppLinuxSerial;

/*
*   General Notes:
*   We use SCPI to talk to the Teslameter (Lakeshore F71).
*   As SCPI commands can be chained in a line, we set each command as a string   
*   And the member functions combine them through string concatenation
*   given a = "hello" and b = " world", c = a + b = "hello world"
*/

class Teslameter{
private:
    /*
    Usual setup method. Sets timeout, sensing mode, units 
    */
    void TeslameterSetup();
    
    /*Command to set the range to automatic*/
    std::string autoRange   = "SENS:FIEL:RANG:AUTO 1";
    /*Command to set the field to tesla*/
    std::string fieldTesla  = "UNIT:FIEL TESL";
    /*Command to fetch the field in a direction. MUST ADD X/Y/Z/ALL to complete command*/
    std::string fetchField  = "FETC:FIEL:DC? ";

    /*Allows command to send an ack response 
    Format: "response;1;"
    Where "1;" is the ACK bit*/
    std::string confirmed   = "*OPC?";
    /*Need to attach a line feed to each command to complete them*/
    std::string lineFeed    = "\n\0";

public:
    SerialPort serialPort;
    /*Default constructor for the class.
    Defaults to COM Port ttyUSB0*/
    Teslameter();
    /*
    Overloaded constructor. Lets us specify the COM port */
    Teslameter(std::string COM);
    ~Teslameter();
    
    /*Enum class to differentiate axis
    More of an exercise for me to get familiar with the practice*/
    enum class AXIS{
        X,
        Y,
        Z
    };

    /*Returns field reading in axis Axis. Look at enum class AXIS for details*/
    float SingleAxisReading(Teslameter::AXIS Axis);
    /*Returns field reading in all directions in a vector*/
    std::vector<float> AllAxisReading();


    
};