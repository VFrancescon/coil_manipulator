#include <libs/PSU/PSU_LIB.h>

DXKDP_PSU::DXKDP_PSU(){
    //default constructor, here for debugging mainly
    //will instantiate a power supply at ttyUSB0, addr 1
    
    
    std::cout << "Psu lib is being called\n";
    std::unique_ptr<input_message> input_msg_ptr();
    //std::unique_ptr<SerialPort> FirstPort("dev/ttyUSB0", );
    std::unique_ptr<SerialPort> Port1(
        new SerialPort("/dev/ttyUSB0", BaudRate::B_9600, NumDataBits::EIGHT, Parity::NONE, NumStopBits::ONE)
        );
    message = std::unique_ptr<input_message>(new input_message());


}