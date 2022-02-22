//!
//! @file 			initial_serial_comm.h
//! @author 		Vittorio Francescon <vittorio.francescon@gmail.com> 
//! @created		07/12/2021
//! @last-modified 	08/12/2021
//! @brief			Header for Initial testing file for serial comms.
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
    

    

public:
    DXKDP_PSU();
    DXKDP_PSU(std::string &COM_PORT, unsigned int addr);
    std::unique_ptr<input_message> message;



};