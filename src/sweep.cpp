#include <HCoilMiddlewareLib/HCoilMiddlewareLib.hpp>
#include <stdio.h>
#include <iostream>
#include <unistd.h>
#define ONEMILLION 1000000

#include <chrono>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std::chrono_literals;

int f()
{
    std::this_thread::sleep_for(10s); //change value here to less than 1 second to see Success
    return 1;
}



void f_wrapper(double field, MiddlewareLayer &mid)
{
    std::mutex m;
    std::condition_variable cv;
    // int retValue;
    
    // mid.set3DField();
    std::thread t([&mid, &cv, &field]() 
    {
        mid.set3DField(field, 0, 0);
        cv.notify_one();
    });

    // std::thread t([&cv, &retValue]() 
    // {
    //     retValue = f();
    //     cv.notify_one();
    // });

    t.detach();

    {
        std::unique_lock<std::mutex> l(m);
        if(cv.wait_for(l, 2s) == std::cv_status::timeout) 
            throw std::runtime_error("Timeout");
    }

    // return retValue;    
}

int main(int argc, char* argv[]){
    // bool timedout = false;
    // try {
    //     f_wrapper();
    // }
    // catch(std::runtime_error& e) {
    //     std::cout << e.what() << std::endl;
    //     timedout = true;
    // }

    // if(!timedout)
    //     std::cout << "Success" << std::endl;

    // return 0;
    
    int maxAbs, step;

    if(argc == 3){
        bool PSU_ONLY = true;
        std::cout << "Before constructor\n";
        MiddlewareLayer mid(PSU_ONLY);

        maxAbs = std::stoi(argv[1]);
        step = std::stoi(argv[2]);

        std::cout << "Slowly stepping to -maxAbs\n";
        // for (double prep = 0.0; prep > -maxAbs - 1; prep--){
        //     // double field = (double) prep;
        //     // std::cout << "Setting the field = " << prep  << "\n";
            
        //     // Give 3 tries to set the field, avoids haulting
        //     for (int i = 0; i < 3; i++){
        //         std::cout << "Setting the field = " << prep  << "\n";
        //         bool field_was_set = false;
        //         try {
        //             mid.set3DField(prep, 0, 0);
        //             f_wrapper(prep, mid);
        //             field_was_set = true;
        //         }
        //         catch(std::runtime_error& e) {
        //             std::cout << e.what() << std::endl;
        //             std::cout << "Timed out, on try " << i+1 << ". Let's try it again\n";
        //         }
        //         if (field_was_set){
        //             break;
        //         }
        //     }
        //     std::cout << "Field set. going to sleep\n\n";
        //     usleep(5*ONEMILLION);
        // }
        // std::cout << "Slowly stepping to -maxAbs\n";
        mid.set3DField(-maxAbs/4, 0, 0);
        std::cout << "One quarter" << -maxAbs/4  << "\n";
        usleep(2*ONEMILLION);
        mid.set3DField(-maxAbs/2, 0, 0);
        std::cout << "Half" << -maxAbs/2 << "\n";
        usleep(2*ONEMILLION);
        mid.set3DField(-maxAbs/4*3, 0, 0);
        std::cout << "Three quarter" << -maxAbs/4 * 3 << "\n";
        usleep(2*ONEMILLION);



        std::cout << "Stepped to -maxAbs. Press enter to begin";
        std::cin.get();
        for(int i = -maxAbs; i < maxAbs+1; i = i + step){
            double field = (double) i;
            std::cout << "Setting field= " << field << "\n";
            mid.set3DField(field, 0, 0);
            std::cout << "Field set. going to sleep\n\n";
            usleep(2*ONEMILLION);
        }
    }
    return 0;
}