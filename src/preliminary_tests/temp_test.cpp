#include <libs/PSU/PSU_LIB.h>


int main(void){
    std::cout << "Press enter to begin";
    std::cin.get();

    DXKDP_PSU PSU;
    std::cout << "Reading instruction\n";
    for(auto i: PSU.message->instruction) printf("%02X ", i);
    
    std::cout << "\nEnd of program.\n";
    std::cin.get();

}
