#include <DxkdpLib/DxkdpLib.hpp>

DXKDP_PSU::DXKDP_PSU(){
    //default constructor, here for debugging mainly
    //will instantiate a power supply at ttyUSB0, addr 1

    //std::cout << "Psu lib is being called\n";
    //std::unique_ptr<SerialPort> FirstPort("dev/ttyUSB0", );
    // std::unique_ptr<SerialPort> SerialDevice(
    //     new SerialPort("/dev/ttyUSB2", BaudRate::B_9600, NumDataBits::EIGHT, Parity::NONE, NumStopBits::ONE)
    //     );
    SerialPort SerialDevice("/dev/ttyUSB0", BaudRate::B_9600, NumDataBits::EIGHT, Parity::NONE, NumStopBits::ONE);

    SerialDevice.SetTimeout(500);
    SerialDevice.Open();
    std::cout << "Serial port has been opened\n";
}

DXKDP_PSU::DXKDP_PSU(std::string &COM_PORT){
    //default constructor, here for debugging mainly
    //will instantiate a power supply at ttyUSB0, addr 1

    std::cout << "Psu lib is being called\n";

    // std::unique_ptr<SerialPort> SerialDevice(
    //     new SerialPort(COM_PORT, BaudRate::B_9600, NumDataBits::EIGHT, Parity::NONE, NumStopBits::ONE)
    // );
    // SerialPort SerialDevice(COM_PORT, BaudRate::B_9600, NumDataBits::EIGHT, Parity::NONE, NumStopBits::ONE);
    
    SerialPort SerialDevice("/dev/ttyUSB0", BaudRate::B_9600, NumDataBits::EIGHT, Parity::NONE, NumStopBits::ONE);
    SerialDevice.SetTimeout(500);
    SerialDevice.Open();
    
    

}

void DXKDP_PSU::DXKDP_Setup(){
    SerialDevice.SetTimeout(500);
    SerialDevice.Open();
    
}

void DXKDP_PSU::PsuWrite(input_message msgIn){
    SerialDevice.WriteBinary(msgIn.instruction);
}

void DXKDP_PSU::PsuRead(output_message msgOut){
    std::cout << "\nPrint before read attemp\n";
    SerialDevice.ReadBinary(msgOut.output);
}

DXKDP_PSU::~DXKDP_PSU(){
    SerialDevice.Close();
}