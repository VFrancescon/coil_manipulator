#include <DxkdpLib/DxkdpLib.hpp>

DXKDP_PSU::DXKDP_PSU() : serialPort("/dev/ttyUSB0", BaudRate::B_9600, NumDataBits::EIGHT, Parity::NONE, NumStopBits::ONE)
{
    //default constructor, here for debugging mainly
    //will instantiate a power supply at ttyUSB0, addr 1

    //std::unique_ptr<SerialPort> FirstPort("dev/ttyUSB0", );
    // std::unique_ptr<SerialPort> SerialDevice(
    //     new SerialPort("/dev/ttyUSB2", BaudRate::B_9600, NumDataBits::EIGHT, Parity::NONE, NumStopBits::ONE)
    //     );
    //SerialPort RS232Device("/dev/ttyUSB0", BaudRate::B_9600, NumDataBits::EIGHT, Parity::NONE, NumStopBits::ONE);

    // this->serialPort.SetTimeout(5000);
    // this->serialPort.Open();
    this->DXKDP_Setup();
    std::cout << "Serial port has been opened";
}

DXKDP_PSU::DXKDP_PSU(std::string COM_PORT) : serialPort(COM_PORT, BaudRate::B_9600, NumDataBits::EIGHT, Parity::NONE, NumStopBits::ONE)
{
    //default constructor, here for debugging mainly
    //will instantiate a power supply at ttyUSB0, addr 1


    // std::unique_ptr<SerialPort> SerialDevice(
    //     new SerialPort(COM_PORT, BaudRate::B_9600, NumDataBits::EIGHT, Parity::NONE, NumStopBits::ONE)
    // );
    // SerialPort SerialDevice(COM_PORT, BaudRate::B_9600, NumDataBits::EIGHT, Parity::NONE, NumStopBits::ONE);
    
    
   this->DXKDP_Setup();
}

void DXKDP_PSU::DXKDP_Setup(){
    this->serialPort.SetTimeout(24499);
    this->serialPort.Open();
    
}

void DXKDP_PSU::PsuWrite(input_message msgIn){
    this->serialPort.WriteBinary(msgIn.instruction);
}

void DXKDP_PSU::PsuRead(output_message &msgOut){
    //std::cout << "\nPrint before read attemp\n";
    //SerialDevice.ReadBinary(msgOut.output);

    //std::cout << "\n-----------------\nFirst try\n";
    this->serialPort.ReadBinary(msgOut.output1);
    //std::cout << "\nResult: ";
    //for(auto i : msgOut.output1) printf("%02X ", i);

    //std::cout << "\n-----------------\nSecond try\n";
    this->serialPort.ReadBinary(msgOut.output2);
    //std::cout << "\nResult: ";
    //for(auto i : msgOut.output2) printf("%02X ", i);

    // std::cout << "\n-----------------\nThird try\n";
    // this->serialPort.ReadBinary(msgOut.output3);
    // std::cout << "\nResult: ";
    // for(auto i : msgOut.output3) printf("%02X ", i);
}

DXKDP_PSU::~DXKDP_PSU(){
    this->serialPort.Close();
}