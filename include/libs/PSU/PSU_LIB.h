//!
//! @file 			PSU_LIB.h
//! @author 		Vittorio Francescon <vittorio.francescon@gmail.com> 
//! @created		22/02/2020
//! @last-modified 	22/02/2022
//! @brief			Header for PSU Low-Level library.
//! @details
//!					SerialPort class is taken from another repo.

#include "libs/CppLinuxSerial/SerialPort.hpp"
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
    DXKDP_PSU(std::string &COM_PORT);
    ~DXKDP_PSU();
    
    
    std::unique_ptr<SerialPort> SerialDevice;
    // SerialPort SerialDevice;
    
    void PsuWrite(input_message msgIn);
    void PsuRead(output_message msgOut);
};