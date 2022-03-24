#include "CppLinuxSerial/SerialPort.hpp"
#include "instructions.h"
#include <iostream>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <memory>
#include <cstdlib>
#include <stdlib.h>
#include <cmath>

using namespace mn::CppLinuxSerial;

class DXKDP_PSU{

private:
    void DXKDP_Setup();

    /*
    Constructs the input msg to set the Power out state.
    PO VALUES
    1 = PO is on
    0 = PO is off
    defaults to off for safety
    addr is the address of the PSU
    Defaults to 1
    */
    std::vector<uint8_t> Encoder20(uint8_t PO_STATE = 0x00, uint8_t addr = 0x01);

    /*
    Constructs the input msg to set the Voltage.
    Voltage can e any float to 2dp
    defaults to 0 for safety
    addr is the address of the PSU
    Defaults to 1
    */
    std::vector<uint8_t> Encoder21(float Voltage=0, uint8_t addr=0x01);

    /*
    Constructs the input msg to set the Current.
    Current can be any float to 2dp
    defaults to 0 for safety
    addr is the address of the PSU
    Defaults to 1
    */
    std::vector<uint8_t> Encoder22(float Current=0, uint8_t addr=0x01);

    /*
    Constructs the input msg to set the Current.
    Current can be any float to 2dp
    defaults to 0 for safety
    addr is the address of the PSU
    Defaults to 1
    */
    std::vector<uint8_t> Encoder23(float Voltage=0, float Current=0, uint8_t addr=0x01);

    /*
    Constructs the input msg to set the Polarity.
    Set Voltage or Current to 1 for positive, 0 for negative
    Defaults to Positive
    */
    std::vector<uint8_t> Encoder24(uint8_t VoltageP=0x01, uint8_t CurrentP=0x01, uint8_t addr=0x01);

    /*
    Constructs the input msg to view actual values.
    Use Decoder26 to write them in msgOut.
    */
    std::vector<uint8_t> Encoder26(uint8_t addr=0x01);

    /*
    Constructs the input msg to view actual values.
    Use Decoder26 to write them in msgOut.
    */
    std::vector<uint8_t> Encoder28(uint8_t addr=0x01);

    /*
    Takes Actual current V & I
    Plus says if we are in constant current or voltage operation
    */
    void Decoder26(output_message &msgOut);

    /*
    Takes Power Out State, Voltage and Current 
    */
    void Decoder28(output_message &msgOut);

    /*
    Hex to Int, no conversion
    MSB = MSB read
    LSB = LSB read
    */
    int HexToDec(uint8_t MSB, uint8_t LSB);

    /*Hex to Float, with conversion factor 
    MSB = MSB read
    LSB = LSB read
    Conv = Conversion factor (10^-value_read)
    */
    float HexToValue(uint8_t MSB, uint8_t LSB, float Conv);

    /*Float to 16bit Hex, writes Low and High bit in the input_msg struct direclty.
    value = value to convert
    Conv = conversion factor
    entry = 1 writes to CONT1, CONT2
    entry = 2 writes to CONT3, CONT4 */
    void DecToHex(float value, float Conv, input_message &msgIn, int entry = 1);

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
    
    /*Sets Polarity polarity of Supplu PSU*/
    void setPolarity(uint8_t polarity, uint8_t addr=0x01);

    void PoCtrl(uint8_t po_state);

    void WriteVoltage(float targetV, uint8_t addr=0x01);
    void WriteCurrent(float targetI, uint8_t addr=0x01);
    void WriteVI(float targetV, float targetI, uint8_t addr=0x01);

    bool POstate;
    float ReadVoltage, ReadCurrent;


};