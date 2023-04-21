/**
 * @file instructions.hpp
 * @author Vittorio Francescon <vittorio.francescon@gmail.com>
 * @brief Contains hex-level headers for ingoing and outgoing instructions to
 * the PSU.
 * @version 1.0
 * @date 2022-04-01
 *
 *
 *
 */
#ifndef INSTRUCTION_H_
#define INSTRUCTION_H_
#include <stdint.h>

#include <iostream>
#include <vector>

/**
 * @brief PSU Input message struct
 * @struct input_message
 *
 */
struct input_message {
    /*Default constructor for struct. Set addr to 0x01, Code to 0x2B, L to
     * 0x00*/
    /**
     * @brief Construct a new input message object
     *
     * Sets Addr to 0x01, Code to 0x2B and L to 0x00.
     */
    input_message() {
        this->ADDR = 0x01;
        this->CODE = 0x2B;
        this->LENGTH = 0x00;
    }

    /*Advanced Constructor. Order is Code, Addr(default 1), L(default1). Call
     * set contents afterwards*/
    /**
     * @brief Construct a new input message object
     *
     *
     * @param code set the Code of this input message
     * @param addr set the PSU address of this input message (default 0x01)
     */
    input_message(uint8_t code, uint8_t addr = 0x01) {
        this->ADDR = addr;
        this->CODE = code;
    }

    /**
     * @brief Set the contents of the message. Unset contents default to 0.
     *
     * It automatically calls InstructionAssembler after execution
     *
     * @param cont1 Content for Index 1
     * @param cont2 Content for Index 2
     * @param cont3 Content for Index 3
     * @param cont4 Content for Index 4
     */
    void set_contents(uint8_t cont1 = 0x00, uint8_t cont2 = 0x00,
                      uint8_t cont3 = 0x00, uint8_t cont4 = 0x00) {
        this->CONT1 = cont1;
        this->CONT2 = cont2;
        this->CONT3 = cont3;
        this->CONT4 = cont4;
        this->InstructionAssembler();
    }

    /**
     * @brief Set the Length object
     * Counts the number of contents set and sets the lenght accordingly.
     */
    void setLength() {
        int counter = 0;
        if (cont1_set) counter++;  // printf("\n%02X ", this->CONT1);
        if (cont2_set) counter++;  // printf("%02X ", this->CONT2);
        if (cont3_set) counter++;  // printf("%02X ", this->CONT3);
        if (cont4_set) counter++;  // printf("%02X \n", this->CONT4);
        // std::cout << "\nCounter is: " << counter << "\n";
        this->LENGTH = counter;
    }

    uint8_t SYNCH = 0xAA;  //!< Synchronisation byte
    uint8_t ADDR;          //!< Address byte
    uint8_t CODE;          //!< Code byte
    uint8_t LENGTH;        //!< Length byte
    uint8_t CONT1 = 0x00;  //!< Contents 1 byte
    uint8_t CONT2 = 0x00;  //!< Contents 2 byte
    uint8_t CONT3 = 0x00;  //!< Contents 3 byte
    uint8_t CONT4 = 0x00;  //!< Contents 4 byte
    uint8_t CHECK;         //!< Check byte
    std::vector<uint8_t>
        instruction;     //!< Vector containing all (relevant) above bytes
    bool cont1_set = 0;  //!< Content set flags, needed for SetLength
    bool cont2_set = 0;  //!< Content set flags, needed for SetLength
    bool cont3_set = 0;  //!< Content set flags, needed for SetLength
    bool cont4_set = 0;  //!< Content set flags, needed for SetLength

    /**
     * @brief Calculates check byte
     *
     * Check byte is the 2 LSB of the sum of ADDR, CODE, LENGTH, CONT1-4.
     *
     * Rather then returning a result, it sets the Check bit of the struct
     * instance.
     */
    void Check_Bit_Calc() {
        uint16_t CALCULATION = this->ADDR + this->CODE + this->LENGTH +
                               this->CONT1 + +this->CONT2 + this->CONT3 +
                               +this->CONT4;

        this->CHECK = CALCULATION;
    }

    /**
     * @brief Assembles instruction with all set bytes into the instruction
     * member.
     *
     */
    void InstructionAssembler() {
        setLength();
        Check_Bit_Calc();
        uint8_t l = this->LENGTH;
        instruction.clear();

        switch (l) {
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

/**
 * @brief PSU Output message struct
 * @struct output_message
 *
 */
struct output_message {
    uint8_t SYNCH;     //!< Synch byte
    uint8_t ADDR;      //!< Address byte
    uint8_t CODE;      //!< Code byte
    uint8_t LENGTH;    //!< Length Byte
    uint8_t CHECK;     //!< Check Byte
    uint8_t V_STEP;    //!< Voltage increment Byte
    uint8_t I_STEP;    //!< Current increment Byte
    uint8_t V_HIGH;    //!< Voltage High Byte
    uint8_t V_LOW;     //!< Voltage Low Byte
    uint8_t I_HIGH;    //!< Current High Byte
    uint8_t I_LOW;     //!< Current Low Byte
    uint8_t PO_STATE;  //!< Power output state byte
    uint8_t CC_OP;     //!< Constant Current output state byte

    std::vector<uint8_t>
        output1;  //!< vector containing the first batch of raw read data
    std::vector<uint8_t>
        output2;  //!< vector containing the second batch of raw read data
    std::vector<uint8_t> output3;  //!< vector containing processed read data.
                                   //!< Unused at the moment.
};

#endif