#include <DxkdpLib/DxkdpLib.hpp>
#include <iostream>
#include <string>

int main(int argc, char* argv[]){

    if(argc == 3){
        DXKDP_PSU supply("/dev/ttyUSB1", 0.1, 0.01);
        std::cout << "No input. Will enable Power out. Press enter to disable power out and quit.\n";
        supply.PoCtrl(0x01);
        std::cin.get();
        supply.PoCtrl(0x00);
    }
    if(argc == 2){
        std::string address = argv[1];
        DXKDP_PSU supply(address, 0.1, 0.01);
        supply.setPolarity(0x00);
        std::cout << "Set polarity successfully. Quitting\n";
    }

    if(argc == 1){
        DXKDP_PSU supply1("/dev/ttyUSB2", 0.01, 0.01);
        DXKDP_PSU supply2("/dev/ttyUSB3", 0.01, 0.01);
        
        supply1.PoCtrl(0x01);
        supply2.PoCtrl(0x01);
        supply1.WriteVI(20, 15.35);
        supply2.WriteVI(20, 15.35);
        std::cout << "Set VI. Press enter to exit\n";
        std::cin.get();
        supply1.WriteVI(0,0);
        supply2.WriteVI(0,0);
        supply1.PoCtrl(0x00);
        supply2.PoCtrl(0x00);
    }

    return 0;
}