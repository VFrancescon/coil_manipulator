#include <TeslameterTest.hpp>

int main(int argc, char* argv[]){
    std::cout << "Programme started. Press enter to instantiate teslameter class.";
    std::cin.get();
    Teslameter teslameter;

    std::cout << "Press enter to run input command\n";
    std::cin.get();

    if(argv[1] == "1"){
        teslameter.SingleAxisReading(1);
    }

    if(argv[1] == "2"){
        teslameter.AllAxisReading();
    }
}