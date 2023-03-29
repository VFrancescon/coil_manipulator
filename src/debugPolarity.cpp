#include "CppLinuxSerial/SerialPort.hpp"

using namespace mn::CppLinuxSerial;

int main(int argc, char* argv[]){
    std::string COM_PORT = "/dev/ttyUSB3";
    SerialPort z2(
        COM_PORT, BaudRate::B_9600, NumDataBits::EIGHT, Parity::NONE, NumStopBits::ONE
    );
    
    std::vector<uint8_t> inputVect, outputVect;

    inputVect.push_back(0x01);
    inputVect.push_back(0x06);
    inputVect.push_back(0x00);
    inputVect.push_back(0x01);
    inputVect.push_back(0x00);
    inputVect.push_back(0x01);
    inputVect.push_back(0x19);
    inputVect.push_back(0xCA);

    z2.SetTimeout(100);
    z2.Open();
    std::cout << "Opened port. Press enter";
    std::cin.get();

    z2.WriteBinary(inputVect);
    z2.ReadBinary(outputVect);

    if(outputVect.size() > 0){
        std::cout << "Printing output\n";
        for(auto i: outputVect) printf("%02X ", i);
    } else std::cout << "No return value from PO=ON\n";
    std::cout << "Press enter to continue.";
    std::cin.get();

    inputVect.clear();
    outputVect.clear();
    inputVect.push_back(0x01);
    inputVect.push_back(0x06);
    inputVect.push_back(0x00);
    inputVect.push_back(0x02);
    inputVect.push_back(0x01);
    inputVect.push_back(0xF4);
    inputVect.push_back(0x28);
    inputVect.push_back(0x1D);
    z2.WriteBinary(inputVect);
    z2.ReadBinary(outputVect);

    if(outputVect.size() > 0){
        std::cout << "Printing output\n";
        for(auto i: outputVect) printf("%02X ", i);
    } else std::cout << "No return value from I=0.5\n";
    std::cout << "Press enter to continue.";
    std::cin.get();

    
    inputVect.clear();
    outputVect.clear();
    inputVect.push_back(0x01);
    inputVect.push_back(0x06);
    inputVect.push_back(0x00);
    inputVect.push_back(0x04);
    inputVect.push_back(0x00);
    inputVect.push_back(0x03);
    inputVect.push_back(0x88);
    inputVect.push_back(0x0A);
    if(outputVect.size() > 0){
        std::cout << "Printing output\n";
        for(auto i: outputVect) printf("%02X ", i);
    } else std::cout << "No return value from Polarity Switching\n";
    std::cout << "Press enter to continue.";
    std::cin.get();
    return 0;
}