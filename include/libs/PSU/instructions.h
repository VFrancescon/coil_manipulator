#include <iostream>
#include <stdint.h>
#include <vector>

struct input_message{

    input_message(){
        this->ADDR = 0x01;
        this->CODE = 0x2B;
        this->LENGTH = 0x00;
        this->set_contents();
        this->InstructionAssembler();
    }
    
    input_message(uint8_t addr, uint8_t code, uint8_t length){
        this->ADDR = addr;
        this->CODE = code;
        this->LENGTH = length;
    }

    void set_contents(uint8_t cont1 = 0x00, uint8_t cont2 = 0x00, uint8_t cont3 = 0x00, uint8_t cont4 = 0x00){
        this->CONT1 = cont1;
        this->CONT2 = cont2;
        this->CONT3 = cont3;
        this->CONT4 = cont4;
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
    std::vector<u_int8_t> instruction;

    uint8_t Check_Bit_Calc(){
        uint16_t CALCULATION = this->ADDR + this->CODE + this->LENGTH
                                +this->CONT1 + +this->CONT2 + this->CONT3 + +this->CONT4;
        
        CHECK = CALCULATION;
        //printf("From within function, check bit is: %02X\n", CHECK);
        
        return CHECK;
    }
    void InstructionAssembler(){
        this->CHECK = Check_Bit_Calc();
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