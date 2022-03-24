#include <PSULib_test.hpp>


int main(int argc, char *argv[]){
    std::cout << "Press enter to begin";
    std::cin.get();
    std::string str = "/dev/ttyUSB1";
    DXKDP_PSU PSU(str, 0.01, 0.01);
    long cmdIn1;
    float cmdIn2, cmdIn3;

    
    if(argc > 1) cmdIn1 = strtol(argv[1], NULL, 16);
    if(argc > 2) cmdIn2 = atof(argv[2]);
    if(argc > 3) cmdIn3 = atof(argv[3]);

    std::cout << "in1: " << argv[1] << " in2: " << argv[2] << "\n";
    std::cout << "in1: " << cmdIn1 << " in2: " << cmdIn2 << "\n";
    
    switch(argc)
    {
        
    case 2:
            std::cout << "Argument given was: " << argv[1] << " which is not on the list\n";
        break;
    case 3:
        if(cmdIn1 == 0x20){
            if((int)cmdIn2 == 0x01){
                PSU.PoCtrl(0x01);
            }
            else PSU.PoCtrl(0x00);
        }
        else if(cmdIn1 == 0x21){
            PSU.WriteVoltage(cmdIn2);
        }
        else if(cmdIn1 == 0x22){
            PSU.WriteCurrent(cmdIn2);
        }

        else if(cmdIn1 == 0x24){
            if((int)cmdIn2 == 0x01){
                PSU.setPolarity(0x01);
            }
            else{
                PSU.setPolarity(0x00);
            }
        }
        break;
    case 4:
        if(cmdIn1 == 0x23){
            PSU.WriteVI(cmdIn2, cmdIn3);
        }
        break;

    default:
            std::cout << "No arguments given\n";
        break;
    }
    
    std::cout << "\nEnd of program.\n";

}