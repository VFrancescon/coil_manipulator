#include <TeslameterTest.hpp>
#include <unistd.h>

struct output_struct{
    std::string output;
};

void ReadWStruct(output_struct &output, SerialPort &serialDevice);

int main(int argc, char* argv[]){
    std::cout << "Programme started. Press enter to instantiate teslameter class.";
    std::cin.get();
    output_struct out;   
    SerialPort serialDevice("/dev/ttyUSB0", BaudRate::B_115200, NumDataBits::EIGHT, Parity::NONE, NumStopBits::ONE, FlowControl::HARDWARE);
    serialDevice.SetTimeout(500);
    serialDevice.Open();

    std::cout << "Serial port opened successfully. Press enter to continue";
    std::cin.get();

    //from logic analyzer, seems like LF= \0
    //possibly with a newline as well
    //we will attempt both now
    std::string test_message = "FETC:FIEL:DC? X;\n\0";
    // std::vector<uint8_t> output;
    std::string output;
    
    serialDevice.Write(test_message);
    std::cout << "\nMessage written.\n";

    
    usleep(500000);


    // serialDevice.ReadBinary(output);

    int available = serialDevice.Available();
    std::cout << "Available data: " << available;

    std::string outstr;

    serialDevice.Read(outstr);
    std::cout << "\nOutput String is: " << outstr << "\n";

    // ReadWStruct(out, serialDevice);
    
    // for(auto i: output) printf("%02X ", i);
    serialDevice.Close();

}



void ReadWStruct(output_struct &output, SerialPort &serialDevice){
    serialDevice.Read(output.output);

    std::cout << "\nOutput is: " << output.output << "\n";
}