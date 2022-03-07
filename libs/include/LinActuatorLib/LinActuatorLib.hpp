#include <CppLinuxSerial/SerialPort.hpp>
#include <string.h>


using namespace mn::CppLinuxSerial;



class LinearActuator{

private:
    /*Setup timeout and open COM port*/
    void ActuatorSetup();

    uint8_t Ext1mm = 49, Ctr1mm = 50, Shtdwn = 51;

    /*  
    Because of how CppLinuxSerial is built, we need a vector for each instruction
    The introducer instructions are simple enough we might as well build them once
    and let them be.
    */

    std::vector<uint8_t> Ext1mm_vect = {Ext1mm};
    std::vector<uint8_t> Ctr1mm_vect = {Ctr1mm};
    std::vector<uint8_t> Shtdwn_vect = {Shtdwn};

public:
    SerialPort serialPort;

    /*Default Constructor, takes standard COM Port ttyUSB0, 1 DOF*/
    LinearActuator();

    /*COM Port Overload Constructor. Lets you choose port, 1 DOF*/
    LinearActuator(std::string COM);

    /*Destructor*/
    ~LinearActuator();

    /*1D extension, 1mm*/
    void LinearExtend();

    /*1D contraction, 1mm*/
    void LinearContract();
    
    /*1D Shutdown*/
    void LinearStop();

};