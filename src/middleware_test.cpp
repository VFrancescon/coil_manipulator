#include <middleware_test.h>

int main(int argc, char* argv[]){
    
    std::string filename = "/home/vittorio/coil_manipulator/Uopt2_Nav2_OPT2RE.csv";
    if(argc == 2) {
        filename = argv[1];
        }
    
    std::ifstream file(filename, std::ios::in);
    std::string line, word;
    
    getline(file,line);

    
    while(std::getline(file, line)){
        int counter = 0;
        std::stringstream sstr(line);
        // std::cout << line << "\n";
        while(std::getline(sstr, word, ',')){

            if(counter == 6) bx.push_back(std::stof(word));
            if(counter == 7) by.push_back(std::stof(word));
            if(counter == 8) bz.push_back(std::stof(word));
            counter++;
        }
    }
    
    MiddlewareLayer mid;
    

    // std::cout << "Everything initialised properly.\nWe will write current to all PSUs starting at 0.01, 20 steps.\nPress enter to begin";
    std::cout << "Press enter to begin stepping through the csv";
    std::cin.get();
    
    // std::thread th1(&MiddlewareLayer::set3DVector, &mid, bx, by, bz);
    mid.set3DVector(bx, by, bz);
    
    //std::cout << "Field in X direction at the end of writing loop: " << mid.getXField();
}