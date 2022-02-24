//!
//! @file 			instructions.h
//! @author 		Vittorio Francescon <vittorio.francescon@gmail.com> 
//! @created		22/02/2020
//! @last-modified 	22/02/2022
//! @brief			Header for hex-level instructions to the PSUs.
//! @details
//!					SerialPort class is taken from another repo.
#ifndef INSTRUCTION_H_
#define INSTRUCTION_H_

#include <iostream>
#include <stdint.h>
#include <vector>

struct input_message{
    /*Default constructor for struct. Set addr to 0x01, Code to 0x2B, L to 0x00*/
    input_message(){
        this->ADDR = 0x01;
        this->CODE = 0x2B;
        this->LENGTH = 0x00;
        
    }
    
    /*Advanced Constructor. Order is Code, Addr(default 1), L(default1). Call set contents afterwards*/
    input_message(uint8_t code, uint8_t addr=0x01){
        this->ADDR = addr;
        this->CODE = code;
    }

    void set_contents(uint8_t cont1 = 0x00, uint8_t cont2 = 0x00, uint8_t cont3 = 0x00, uint8_t cont4 = 0x00){
        //int counter = 0;
        std::cout << "\nFunction is called\n";
        this->CONT1 = cont1; 
        this->CONT2 = cont2;
        this->CONT3 = cont3;
        this->CONT4 = cont4;

        // if(this->CONT1 != 0x00) counter++; printf("%02X ", this->CONT1);
        // if(this->CONT2 != 0x00) counter++; printf("%02X ", this->CONT2);
        // if(this->CONT3 != 0x00) counter++; printf("%02X ", this->CONT3);
        // if(this->CONT4 != 0x00) counter++; printf("%02X ", this->CONT4);
        // std::cout << "\nCounter is: " << counter;
        // this->LENGTH = counter;
        this->InstructionAssembler();
    }

    void setLength(){
        int counter = 0;
        if(cont1_set) counter++; printf("\n%02X ", this->CONT1);
        if(cont2_set) counter++; printf("%02X ", this->CONT2);
        if(cont3_set) counter++; printf("%02X ", this->CONT3);
        if(cont4_set) counter++; printf("%02X \n", this->CONT4);
        std::cout << "\nCounter is: " << counter;
        this->LENGTH = counter;
    }


    uint8_t SYNCH = 0xAA;
	uint8_t ADDR;
	uint8_t CODE;
	uint8_t LENGTH;
    uint8_t CONT1 = 0x00;
    uint8_t CONT2 = 0x00;
    uint8_t CONT3 = 0x00;
    uint8_t CONT4 = 0x00;
    uint8_t CHECK;
    std::vector<uint8_t> instruction;
    bool cont1_set = 0, cont2_set = 0, cont3_set = 0, cont4_set = 0;

    void Check_Bit_Calc(){
        uint16_t CALCULATION = this->ADDR + this->CODE + this->LENGTH
                            +this->CONT1 + +this->CONT2 + this->CONT3 + +this->CONT4;
        
        this->CHECK = CALCULATION;
        
    }
    void InstructionAssembler(){
        setLength();
        Check_Bit_Calc();
        uint8_t l = this->LENGTH;
        instruction.clear();
  
        switch(l){
            case 0x01:
                instruction.push_back(this->SYNCH);
                instruction.push_back(this->ADDR);
                instruction.push_back(this->CODE);
                instruction.push_back(this->LENGTH);
                instruction.push_back(this->CONT1);
                instruction.push_back(this->CHECK);
                break;
            case 0x02:
                instruction.push_back(this->SYNCH);
                instruction.push_back(this->ADDR);
                instruction.push_back(this->CODE);
                instruction.push_back(this->LENGTH);
                instruction.push_back(this->CONT1);
                instruction.push_back(this->CONT2);
                instruction.push_back(this->CHECK);
                break;
        
            case 0x03:
                instruction.push_back(this->SYNCH);
                instruction.push_back(this->ADDR);
                instruction.push_back(this->CODE);
                instruction.push_back(this->LENGTH);
                instruction.push_back(this->CONT1);
                instruction.push_back(this->CONT2);
                instruction.push_back(this->CONT3);
                instruction.push_back(this->CHECK);
                break;
            
            case 0x04:
                instruction.push_back(this->SYNCH);
                instruction.push_back(this->ADDR);
                instruction.push_back(this->CODE);
                instruction.push_back(this->LENGTH);
                instruction.push_back(this->CONT1);
                instruction.push_back(this->CONT2);
                instruction.push_back(this->CONT3);
                instruction.push_back(this->CONT4);
                instruction.push_back(this->CHECK);
                break;
            default:
                instruction.push_back(this->SYNCH);
                instruction.push_back(this->ADDR);
                instruction.push_back(this->CODE);
                instruction.push_back(this->LENGTH);
                instruction.push_back(this->CHECK);
                break;
        
        return;
        }
    }
};

struct output_message{
    uint8_t SYNCH;
	uint8_t ADDR;
	uint8_t CODE;
	uint8_t LENGTH;
    uint8_t CHECK;
    uint8_t V_STEP;
    uint8_t I_STEP;
    uint8_t V_HIGH;
    uint8_t V_LOW;
    uint8_t I_HIGH;
    uint8_t I_LOW;
    uint8_t PO_STATE;
    uint8_t CC_OP;

    // //actual declaration
    std::vector<uint8_t> output1;
    std::vector<uint8_t> output2;
    //std::vector<uint8_t> output3;

    /*Test input here*/
    std::vector<uint8_t> output3 = {
        0xAA, 0x01, 0x2B, 0x0E, 0x02, 0x03, 0x00, 0x00, 0x00, 0x13, 0x88, 0x03, 0xE8, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC5
    };

};


#endif