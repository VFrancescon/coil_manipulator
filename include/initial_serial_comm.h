//!
//! @file 			initial_serial_comm.h
//! @author 		Vittorio Francescon <vittorio.francescon@gmail.com> 
//! @created		07/12/2021
//! @last-modified 	08/12/2021
//! @brief			Header for Initial testing file for serial comms.
//! @details
//!					SerialPort class is taken from another repo.

#include "CppLinuxSerial/SerialPort.hpp"
#include <iostream>
#include <stdint.h>
#include <string.h>
using namespace mn::CppLinuxSerial;

std::string result = "AA012B0E0203000000138803E80000000000C5";

int main(void);


struct input_message{
    uint8_t SYNCH = 0xAA;
	uint8_t ADDR;
	uint8_t CODE;
	uint8_t LENGTH;
    uint8_t CONT1;
    uint8_t CONT2;
    uint8_t CONT3;
    uint8_t CONT4;
    uint8_t CHECK;
    char* msg;

    uint8_t Check_Bit_Calc(input_message &input_struct){
        uint8_t CHECK = input_struct.SYNCH + input_struct.ADDR + input_struct.CODE + input_struct.LENGTH;
        //printf("From within function, check bit is: %02X\n", CHECK);
        return CHECK;
    }
    char* InstructionAssembler(input_message &input_struct){
        input_struct.CHECK = Check_Bit_Calc(input_struct);
        char* command = new char[50] /* max message size should be 10byte, but just in case*/;
        uint8_t l = input_struct.LENGTH;
        if(l == 0x01){
            sprintf(command, "%02X%02X%02X%02X%02X%02X", input_struct.SYNCH, input_struct.ADDR, input_struct.CODE,
	        input_struct.LENGTH, input_struct.CONT1, input_struct.CHECK);
        }
        else if(l == 0x02){
            sprintf(command, "%02X%02X%02X%02X%02X%02X%02X", input_struct.SYNCH, input_struct.ADDR, input_struct.CODE,
	        input_struct.LENGTH, input_struct.CONT1, input_struct.CONT2, input_struct.CHECK);
        }
        else if(l == 0x03){
            sprintf(command, "%02X%02X%02X%02X%02X%02X%02X%02X", input_struct.SYNCH, input_struct.ADDR, input_struct.CODE,
	        input_struct.LENGTH, input_struct.CONT1, input_struct.CONT2, input_struct.CONT3, input_struct.CHECK);
        }
        else if(l == 0x04){
            sprintf(command, "%02X%02X%02X%02X%02X%02X%02X%02X%02X", input_struct.SYNCH, input_struct.ADDR, input_struct.CODE,
	        input_struct.LENGTH, input_struct.CONT1, input_struct.CONT2, input_struct.CONT3, input_struct.CONT4, input_struct.CHECK);
        }
        else{
            sprintf(command, "%02X%02X%02X%02X%02X", input_struct.SYNCH, input_struct.ADDR, input_struct.CODE,
	        input_struct.LENGTH, input_struct.CHECK);
        }
        return command;
    }
};