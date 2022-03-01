#include "CppLinuxSerial/SerialPort.hpp"
#include "instructions.h"
#include <iostream>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <memory>
using namespace mn::CppLinuxSerial;



class DXKDP_PSU{

private:
    void DXKDP_Setup();
public:
    /*default constructor, here for debugging mainly
    will instantiate a power supply at ttyUSB0, addr 1*/
    DXKDP_PSU();
    DXKDP_PSU(std::string COM_PORT);
    DXKDP_PSU(std::string COM_PORT, float V_conv, float I_conv);
    ~DXKDP_PSU();
    SerialPort serialPort;
    
    float Vconv = 0.01, Iconv = 0.01;
    
    void PsuWrite(input_message msgIn);
    void PsuRead(output_message &msgOut);
    void PsuWrite(std::vector<uint8_t> input);
    std::vector<uint8_t> PsuRead();
};