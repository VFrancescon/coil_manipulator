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
#include <unistd.h>
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
    std::vector<u_int8_t> instruction;

    uint8_t Check_Bit_Calc(input_message &input_struct){
        uint16_t CALCULATION = input_struct.ADDR + input_struct.CODE + input_struct.LENGTH;
        
        CHECK = CALCULATION;
        printf("From within function, check bit is: %02X\n", CHECK);
        
        return CHECK;
    }
    std::vector<u_int8_t> InstructionAssembler(input_message &input_struct){
        input_struct.CHECK = Check_Bit_Calc(input_struct);
        uint8_t l = input_struct.LENGTH;
        instruction.clear();
        if(l == 0x01){
            instruction.push_back(input_struct.SYNCH);
            instruction.push_back(input_struct.ADDR);
            instruction.push_back(input_struct.CODE);
            instruction.push_back(input_struct.LENGTH);
            instruction.push_back(input_struct.CONT1);
            instruction.push_back(input_struct.CHECK);
        }
        else if(l == 0x02){
            instruction.push_back(input_struct.SYNCH);
            instruction.push_back(input_struct.ADDR);
            instruction.push_back(input_struct.CODE);
            instruction.push_back(input_struct.LENGTH);
            instruction.push_back(input_struct.CONT1);
            instruction.push_back(input_struct.CONT2);
            instruction.push_back(input_struct.CHECK);
        }
        else if(l == 0x03){
            instruction.push_back(input_struct.SYNCH);
            instruction.push_back(input_struct.ADDR);
            instruction.push_back(input_struct.CODE);
            instruction.push_back(input_struct.LENGTH);
            instruction.push_back(input_struct.CONT1);
            instruction.push_back(input_struct.CONT2);
            instruction.push_back(input_struct.CONT3);
            instruction.push_back(input_struct.CHECK);
        }
        else if(l == 0x04){
            instruction.push_back(input_struct.SYNCH);
            instruction.push_back(input_struct.ADDR);
            instruction.push_back(input_struct.CODE);
            instruction.push_back(input_struct.LENGTH);
            instruction.push_back(input_struct.CONT1);
            instruction.push_back(input_struct.CONT2);
            instruction.push_back(input_struct.CONT3);
            instruction.push_back(input_struct.CONT4);
            instruction.push_back(input_struct.CHECK);
        }
        else{
            instruction.push_back(input_struct.SYNCH);
            instruction.push_back(input_struct.ADDR);
            instruction.push_back(input_struct.CODE);
            instruction.push_back(input_struct.LENGTH);
            instruction.push_back(input_struct.CHECK);
        }
        return instruction;
    }
};