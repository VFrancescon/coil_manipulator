#include <DxkdpLib/DxkdpLib.hpp>

int main(int argc, char** argv) {
    // DXKDP_PSU X1("/dev/ttyUSB0", 0.1, 0.01);
    DXKDP_PSU X2("/dev/ttyUSB1", 0.1, 0.01);

    DXKDP_PSU Y1("/dev/ttyUSB4", 0.01, 0.01);
    DXKDP_PSU Y2("/dev/ttyUSB5", 0.01, 0.01);

    DXKDP_PSU Z1("/dev/ttyUSB2", 0.01, 0.01);
    DXKDP_PSU Z2("/dev/ttyUSB3", 0.01, 0.01);


    //setup VI
    // X1.WriteVI(60,0);
    X2.WriteVI(60,0);
    Y1.WriteVI(60,0);
    Y2.WriteVI(60,0);
    Z1.WriteVI(60,0);
    Z2.WriteVI(60,0);

    //setup Power
    // X1.PoCtrl(0x01);
    X2.PoCtrl(0x01);
    Y1.PoCtrl(0x01);
    Y2.PoCtrl(0x01);
    Z1.PoCtrl(0x01);
    Z2.PoCtrl(0x01);

    //print that setup is complete
    std::cout << "Setup Complete\n";
    //ask user to press enter to start
    std::cout << "Press Enter to Start\n";
    std::cin.get();

    //start cycling currents

    //setup negative polarities
    // X1.setPolarity(0x01);
    X2.setPolarity(0x01);
    Y1.setPolarity(0x00);
    Y2.setPolarity(0x01);
    Z1.setPolarity(0x00);

    //decreasing for loop. from i=20 to i =0. step 2
    for(int i = 25; i >= 0; i = i - 2){
        //print a separator and the current value of i
        std::cout << "-------------------\n";
        std::cout << "i = " << i << "\n";
        // X1.WriteVI(60,i);
        //sleep for 0.2 seconds
        usleep(50000);
        X2.WriteVI(60,i);
        usleep(50000);
        Y1.WriteVI(60,i);
        usleep(50000);
        Y2.WriteVI(60,i);
        usleep(50000);
        Z1.WriteVI(60,i);
        usleep(50000);
        Z2.WriteVIGen2(60, -i);
        usleep(100000);
    }

    //setup positive polarities
    // X1.setPolarity(0x00);
    X2.setPolarity(0x00);
    Y1.setPolarity(0x01);
    Y2.setPolarity(0x00);
    Z1.setPolarity(0x01);

    for(int i = 0; i < 25; i = i + 2){
        //print a separator and the current value of i
        std::cout << "-------------------\n";
        std::cout << "i = " << i << "\n";

        // X1.WriteVI(60,i);
        //sleep for 0.2 seconds
        usleep(50000);
        X2.WriteVI(60,i);
        usleep(50000);
        Y1.WriteVI(60,i);
        usleep(50000);
        Y2.WriteVI(60,i);
        usleep(50000);
        Z1.WriteVI(60,i);
        usleep(50000);
        Z2.WriteVIGen2(60, i);
        usleep(100000);
    }

    //print a divider and that the program is shutting down
    std::cout << "-------------------\n";
    std::cout << "Shutting Down\n";

    // shutdown
    // X1.PoCtrl(0x00);
    X2.PoCtrl(0x00);
    Y1.PoCtrl(0x00);
    Y2.PoCtrl(0x00);
    Z1.PoCtrl(0x00);
    Z2.PoCtrl(0x00);

    //call writeVI on all objects with 0,0 args
    // X1.WriteVI(0,0);
    X2.WriteVI(0,0);
    Y1.WriteVI(0,0);
    Y2.WriteVI(0,0);
    Z1.WriteVI(0,0);
    Z2.WriteVI(0,0);

    return 0;
}