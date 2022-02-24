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
    DXKDP_PSU();
    DXKDP_PSU(std::string COM_PORT);
    ~DXKDP_PSU();
    SerialPort serialPort;
    
    // std::unique_ptr<SerialPort> SerialDevice;
    
    void PsuWrite(input_message msgIn);
    void PsuRead(output_message &msgOut);
    void PsuWrite(std::vector<uint8_t> input);
    std::vector<uint8_t> PsuRead(std::vector<uint8_t> output);
};