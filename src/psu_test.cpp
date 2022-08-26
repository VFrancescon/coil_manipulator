#include <DxkdpLib/DxkdpLib.hpp>
#include <iostream>
#include <string>

int main(int argc, char* argv[]){

    if(argc == 1){
        DXKDP_PSU supply("/dev/ttyUSB1", 0.1, 0.01);
        std::cout << "No input. Will enable Power out. Press enter to disable power out and quit.\n";
        supply.PoCtrl(0x01);
        std::cin.get();
        supply.PoCtrl(0x00);
    }
    if(argc == 2){
        std::string address = argv[1];
        DXKDP_PSU supply(address, 0.01, 0.01);
        supply.setPolarity(0x00);
        supply.WriteVI(5,5);
        supply.PoCtrl(0x01);
        std::cout << "Press enter to flip polarity\n";
        std::cin.get();
        supply.setPolarity(0x01);
        std::cin.get();

        supply.PoCtrl(0x00);

    }

    if(argc == 3){
        DXKDP_PSU supply1("/dev/ttyUSB2", 0.01, 0.01);
        DXKDP_PSU supply2("/dev/ttyUSB3", 0.01, 0.01);
        
        supply1.PoCtrl(0x01);
        supply2.PoCtrl(0x01);

        //ALL OTHER CASES
        supply1.setPolarity(0x01); //a
        supply2.setPolarity(0x01); //b

        //Y supplies case
        // supply1.setPolarity(0x01); //b
        // supply2.setPolarity(0x00); //a
        
        
        
        int s12_v = std::stof(argv[1]);
        int s12_i = std::stof(argv[2]);

        supply1.WriteVI(s12_v, s12_i);
        supply2.WriteVI(s12_v, s12_i);
        
        std::cout << "Set VI. Press enter to exit\n";
        std::cin.get();
        supply1.WriteVI(0,0);
        supply2.WriteVI(0,0);
        supply1.PoCtrl(0x00);
        supply2.PoCtrl(0x00);
    }

    return 0;
}