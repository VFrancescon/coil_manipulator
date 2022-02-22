#include <libs/PSU/PSU_LIB.h>

DXKDP_PSU::DXKDP_PSU(){
    //default constructor, here for debugging mainly
    //will instantiate a power supply at ttyUSB0, addr 1

    std::cout << "Psu lib is being called\n";
    //std::unique_ptr<SerialPort> FirstPort("dev/ttyUSB0", );
    std::unique_ptr<SerialPort> SerialDevice(
        new SerialPort("/dev/ttyUSB0", BaudRate::B_9600, NumDataBits::EIGHT, Parity::NONE, NumStopBits::ONE)
        );
}

DXKDP_PSU::DXKDP_PSU(std::string &COM_PORT){
    //default constructor, here for debugging mainly
    //will instantiate a power supply at ttyUSB0, addr 1

    std::cout << "Psu lib is being called\n";

    std::unique_ptr<SerialPort> SerialDevice(
        new SerialPort(COM_PORT, BaudRate::B_9600, NumDataBits::EIGHT, Parity::NONE, NumStopBits::ONE)
        );

}

void DXKDP_PSU::DXKDP_Setup(){
    SerialDevice->Open();
    SerialDevice->SetTimeout(-1);
}

void DXKDP_PSU::PsuWrite(input_message msgIn){
    SerialDevice->WriteBinary(msgIn.instruction);
}

void DXKDP_PSU::PsuRead(output_message msgOut){
    SerialDevice->WriteBinary(msgOut.output);
}

DXKDP_PSU::~DXKDP_PSU(){
    //SerialDevice->Close();
}