#include <DxkdpLib/DxkdpLib.hpp>

DXKDP_PSU::DXKDP_PSU() : serialPort("/dev/ttyUSB0", BaudRate::B_9600, NumDataBits::EIGHT, Parity::NONE, NumStopBits::ONE)
{
    //default constructor, here for debugging mainly
    //will instantiate a power supply at ttyUSB0, addr 1

    this->DXKDP_Setup();
    std::cout << "Serial port has been opened";
}

DXKDP_PSU::DXKDP_PSU(std::string COM_PORT) : serialPort(COM_PORT, BaudRate::B_9600, NumDataBits::EIGHT, Parity::NONE, NumStopBits::ONE)
{
   this->DXKDP_Setup();
}

DXKDP_PSU::DXKDP_PSU(std::string COM_PORT, float V_conv, float I_conv) : serialPort(COM_PORT, BaudRate::B_9600, NumDataBits::EIGHT, Parity::NONE, NumStopBits::ONE)
{
   
   this->Vconv = V_conv;
   this->Iconv = I_conv;
   this->DXKDP_Setup();
}

void DXKDP_PSU::DXKDP_Setup(){
    this->serialPort.SetTimeout(-1);
    this->serialPort.Open();
    
}

void DXKDP_PSU::PsuWrite(input_message msgIn){
    this->serialPort.WriteBinary(msgIn.instruction);
}

void DXKDP_PSU::PsuWrite(std::vector<uint8_t> input){
    this->serialPort.WriteBinary(input);
}

void DXKDP_PSU::PsuRead(output_message &msgOut){
    
    this->serialPort.ReadBinary(msgOut.output1);
    
}

/*
This just does not work, not sure why
*/
std::vector<uint8_t> DXKDP_PSU::PsuRead(){
    std::vector<uint8_t> output;
    this->serialPort.ReadBinary(output);
}

DXKDP_PSU::~DXKDP_PSU(){
    this->serialPort.Close();
}