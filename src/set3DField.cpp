#include <middleware_test.h>


int main(int argc, char *argv[]){
    float I_X, I_Y, I_Z;
    if(argc == 4){
        std::cout << "ARSGS: " << argv[1] << " " << argv[2] << " " << argv[3] << "\n";
        try{
        I_X = std::stof(argv[1]);
        I_Y = std::stof(argv[2]);        
        I_Z = std::stof(argv[3]);
        } catch( std::invalid_argument &e){
            std::cout << "One of the provided arguments was invalid. Arguments:\n" << argv[1] << " " << argv[2] << " " << argv[3] << "\n";
            return;
        }
        
        bool psu_only_mode = true; 
        MiddlewareLayer mid(psu_only_mode);


        mid.set3DField(I_X, I_Y, I_Z);
        std::cout << "Holding field as printed above. press enter to quit\n";
        std::cin.get();
    } else{
        std::cout << "Incorrect number of arguments provided\n.";
    }

    std::cout << "./field3d <Bx> <By> <Bz>\n";
    std::cout << "Each argument sets the respective field\n";

    return 0;
}