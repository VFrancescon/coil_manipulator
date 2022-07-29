#include <LinActuatorLib/LinActuatorLib.hpp>
#include <iostream>
#include <vector>
#include <unistd.h>
#define ONEMILLION 1e6

int main(int argc, char* argv[]){
    std::string comPORT;
    if(argc == 3){
        comPORT = argv[2];
    } else comPORT = "/dev/ttyUSB6"; 
    
    
    if(argc == 2 || argc == 3){
        LinearActuator LinAct(comPORT);
        std::cout << "Press enter to begin";
        std::cin.get();
        double wait_timeD = (double) 0.4  * ONEMILLION;
        int wait_time = (int) wait_timeD;
        int cycles;
        
        try{ 
            cycles = std::stoi(argv[1]);
        } catch(std::invalid_argument &e){
            std::cout << "Invalid argument '" << argv[1] << "' was provided. Exiting.\n";
            return -1;
        }
        if(cycles > 0) {
            std::cout << "Extending by " << abs(cycles) << " steps\n";
            for(int i = 0; i < cycles; i++){
                LinAct.LinearExtend();
                usleep(wait_time);                
            }
        } else if (cycles < 0){
            std::cout << "Retracting by " << abs(cycles) << " steps\n";
            for(int i = 0; i < abs(cycles); i++){
                LinAct.LinearContract();
                usleep(wait_time);
                                
            }
        } else std::cout << "Cannot move by 0";

    } else{
        std::cout << "\n\n\nIntroducer CLI interface; Usage:\n";
        std::cout << "$ ./introducer <steps> <COM port>\n";
        std::cout << "Steps controls the amount of steps taken.\n";
        std::cout << "If positive, <steps> extensions occur.\n";
        std::cout << "Otherwise, it retracts by that amount\n";
        std::cout << "<COM port> allows to start the device at any com port, if valid\n";
    }

    return 0;

}
