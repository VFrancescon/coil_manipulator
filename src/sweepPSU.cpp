#include <DxkdpLib/DxkdpLib.hpp>
#include <stdio.h>
#include <iostream>
#include <unistd.h>
#define ONEMILLION 1000000


int main(int argc, char* argv[]){
    
    int maxAbs, step;

    if(argc == 3){
        DXKDP_PSU psu("/dev/ttyUSB1", 0.1, 0.01);
        maxAbs = std::stoi(argv[1]);
        step = std::stoi(argv[2]);

        psu.WriteVI(60,0);
        psu.PoCtrl(0x01);
        psu.setPolarity(0x00);
        usleep(ONEMILLION);


        std::cout << "Slowly stepping to -maxAbs\n";
        psu.WriteCurrent(maxAbs/4);
        std::cout << "One quarter" << -maxAbs/4  << "\n";
        usleep(10*ONEMILLION);
        psu.WriteCurrent(maxAbs/2);
        std::cout << "Half" << -maxAbs/2 << "\n";
        usleep(10*ONEMILLION);
        psu.WriteCurrent(maxAbs/4*3);
        std::cout << "Three quarter" << -maxAbs/4 * 3 << "\n";
        usleep(10*ONEMILLION);



        std::cout << "Stepped to -maxAbs. Press enter to begin";
        std::cin.get();
        for(int i = maxAbs; i != 30; i = i - step){
            double current = (double) i;
            std::cout << "Setting current= " << -current << "\n";
            psu.WriteCurrent(current);
            std::cout << "current set. going to sleep\n\n";
            usleep(10*ONEMILLION);
        }
        psu.setPolarity(0x01);
        for(int i = 30; i < maxAbs+1; i = i + step){
            double current = (double) i;
            std::cout << "Setting current= " << current << "\n";
            psu.WriteCurrent(current);
            std::cout << "current set. going to sleep\n\n";
            usleep(10*ONEMILLION);
        }

        psu.WriteVI(0,0);
        psu.PoCtrl(0x0);
    }
    return 0;
}