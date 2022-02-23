#include <PSULib_test.hpp>

float V_conv, I_conv;

void SysInfoDecoder(output_message out){
    std::cout << "\nSize of output is:" << out.output.size() << "\nContains: ";
    // for(int i = 0; i < 20; i++) printf("at %d contains %02X\n", i, out.output[i]);
    for(auto i : out.output) printf("%02X ", i );
    if(out.output.size() != 19){
        std::cout << "ERROR: Expected output is not the right size\n";
        //return;
    }
    
    out.ADDR = out.output[1];
    out.CODE = out.output[2];
    out.LENGTH = out.output[3];
    out.V_STEP = out.output[4];
    out.I_STEP = out.output[5];

    V_conv = pow(10, int(out.V_STEP));
    I_conv = pow(10, int(out.I_STEP));
    printf("\nVSTEP %02X hex, ISTEP %02X hex", out.V_STEP, out.I_STEP);
    printf("\nV_Conv: %f  I_Conv: %f ", V_conv, I_conv);
    

    out.V_HIGH = out.output[9];
    out.V_LOW = out.output[10];

    printf("\n\nVH %02X VL %02X", out.V_HIGH, out.V_LOW);
    uint16_t V_H = (out.V_HIGH << 8) + (out.V_LOW);
    printf("\nVoltage: %04X Hex %d Dec ",V_H, V_H);

    out.I_HIGH = out.output[11];
    out.I_LOW = out.output[12];

    printf("\n\nIH %02X IL %02X", out.I_HIGH, out.I_LOW);
    uint16_t I_H = (out.I_HIGH << 8) + (out.I_LOW);
    printf("\nCurrent: %04X Hex %d Dec ",I_H, I_H);

}

int main(void){
    float V_conv, I_conv;



    std::cout << "Press enter to begin";
    std::cin.get();
    std::string str = "/dev/ttyUSB0";
    DXKDP_PSU PSU;
    
    input_message msgIn;
    std::cout << "\nInput command: ";
    for(auto i:msgIn.instruction) printf("%02X ", i);

    output_message msgOut;
    PSU.PsuRead(msgOut);
    std::cout << "\nContents: ";
    for(auto i : msgOut.output) printf("%02X ", i);
    
    
    SysInfoDecoder(msgOut);

    std::cout << "\nEnd of program.\n";
    //std::cin.get();

}
