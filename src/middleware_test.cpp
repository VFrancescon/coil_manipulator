#include <middleware_test.h>

//TESTING BRANCH
//We keep the most basic version of the test file here so I can verify the class, but still develop

int main(void){
    std::vector<float> input_current;
    MiddlewareLayer mid;
    for(int i = 0; i < 20; i++){
        input_current.push_back(0.01+i*0.01);
    }
 
    // input_current.push_back(0.0);

    std::cout << "\nEverything initialised properly.\nWe will write current to all PSUs starting at 0.01, 20 steps.\nPress enter to begin";
    std::cin.get();
    
    // mid.TurnOffSupply();
    mid.set3DVector(input_current, input_current, input_current);
    std::cout << "Field in X direction at the end of writing loop: " << mid.getXField() << "\n";
}