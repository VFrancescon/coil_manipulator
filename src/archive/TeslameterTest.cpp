#include <TeslameterTest.hpp>
#include <unistd.h>


int main(int argc, char* argv[]){
    Teslameter tmeter("/dev/ttyUSB4");
    std::cout << "Programme started. Press enter to instantiate teslameter class.";
    std::cin.get();


    std::cout << "Press enter to read x axis field.";
    std::cin.get();
    std::cout << "X axis reading: " << tmeter.SingleAxisReading(Teslameter::AXIS::X) << "\n";

    std::cout << "Press enter to read all axis field.";
    std::cin.get();
    std::vector<float> triaxisreading = tmeter.AllAxisReading();
    
}



