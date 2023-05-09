#include "DxkdpLib/DxkdpLib.hpp"

int main(int argc, char* argv[]){

    uint8_t returnVal;

    DXKDP_PSU dxkdp_psu("/dev/ttyUSB1", 0.1, 0.01);
    dxkdp_psu.WriteVI(0,0);
    dxkdp_psu.PoCtrl(0x01);

    std::cout << "PSU instantiated. Press enter";
    std::cin.get();

    //-25 -> 0 A
    dxkdp_psu.setPolarity(0x01);
    for(int i = 0; i < 25; i++){
        std::cout << "Setting i = " << i << "\n";
        returnVal = dxkdp_psu.debugWriteVI(60, 25-i);
        switch( returnVal ){
            case 0x06:
                std::cout << "Ack!\n";
                usleep(200000);
            break;

            case 0x15:
                std::cout << "Nack!\n";
                usleep(200000);
            break;

            case 0x99:
                std::cout << "No value read!\n";
                i--;
                usleep(500000);
            break;

            default:
                std::cout << "No value read!\n";
                usleep(500000);
            break;
        }
    }

    // 0 -> 25A
    dxkdp_psu.setPolarity(0x00);
    for(int i = 0; i < 25; i++){
        std::cout << "Setting i = " << i << "\n";
        returnVal = dxkdp_psu.debugWriteVI(60, i);
        switch( returnVal ){
            case 0x06:
                std::cout << "Ack!\n";
                usleep(200000);
            break;

            case 0x15:
                std::cout << "Nack!\n";
                usleep(200000);
            break;

            case 0x99:
                std::cout << "No value read!\n";
                i--;
                usleep(500000);
            break;

            default:
                std::cout << "No value read!\n";
                usleep(500000);
            break;
        }
    }
    std::cout << "Exiting\n";
    dxkdp_psu.WriteVI(0,0);
    dxkdp_psu.PoCtrl(0x00);

    return 0;
}