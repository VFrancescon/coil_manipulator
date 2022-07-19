#include <middleware_test.h>


int main(int argc, char *argv[]){
    if(argc > 3){
        std::cout << "ARSGS: " << argv[1] << " " << argv[2] << " " << argv[3] << "\n";
    
        float I_X = std::stof(argv[1]);
        float I_Y = std::stof(argv[2]);        
        float I_Z = std::stof(argv[3]);

        MiddlewareLayer mid;


        mid.set3DField(I_X, I_Y, I_Z);
        std::cout << "Holding field as printed above. press enter to quit\n";
        std::cin.get();
    }

    return 0;
}