#include <PSULib_test.hpp>

float V_conv, I_conv;

void SysInfoDecoder(output_message &out){
    std::cout << "\nSize of given vect is:" << out.output3.size();
    // for(int i = 0; i < 20; i++) printf("at %d contains %02X\n", i, out.output[i]);
    //for(auto i : out.output1) printf("%02X ", i );
    
    out.ADDR = out.output3[1];
    out.CODE = out.output3[2];
    out.LENGTH = out.output3[3];
    out.V_STEP = out.output3[4];
    out.I_STEP = out.output3[5];

    V_conv = pow(10, -int(out.V_STEP));
    I_conv = pow(10, -int(out.I_STEP));
    printf("\nVSTEP %02X hex, ISTEP %02X hex", out.V_STEP, out.I_STEP);
    printf("\nV_Conv: %f  I_Conv: %f ", V_conv, I_conv);
    

    out.V_HIGH = out.output3[9];
    out.V_LOW = out.output3[10];

    printf("\n\nVH %02X VL %02X", out.V_HIGH, out.V_LOW);
    uint16_t V_H = (out.V_HIGH << 8) + (out.V_LOW);
    printf("\nVoltage: %04X Hex %d Dec ",V_H, V_H);
    printf("Therefore V= %f", float(V_H)*V_conv);

    out.I_HIGH = out.output3[11];
    out.I_LOW = out.output3[12];

    printf("\n\nIH %02X IL %02X", out.I_HIGH, out.I_LOW);
    uint16_t I_H = (out.I_HIGH << 8) + (out.I_LOW);
    printf("\nCurrent: %04X Hex %d Dec ",I_H, I_H);
    printf("Therefore I= %f", float(I_H)*I_conv);

}

int main(void){
    float V_conv, I_conv;



    std::cout << "Press enter to begin";
    std::cin.get();
    std::string str = "/dev/ttyUSB0";
    DXKDP_PSU PSU(str);
    
    input_message msgIn;
    std::cout << "\nInput command: ";
    for(auto i:msgIn.instruction) printf("%02X ", i);
    PSU.PsuWrite(msgIn);

    output_message msgOut;
    PSU.PsuRead(msgOut);
    // std::cout << "\nsize of first output: " << msgOut.output1.size();
    // std::cout << "\nContents of first output: ";
    // for(auto i : msgOut.output1) printf("%02X ", i);
    
    // std::cout << "\nsize of second output: " << msgOut.output2.size();
    // std::cout << "\nContents of second output: ";
    // for(auto i : msgOut.output2) printf("%02X ", i);
    
    msgOut.output3.insert(msgOut.output3.end(), msgOut.output1.begin(), msgOut.output1.end());
    msgOut.output3.insert(msgOut.output3.end(), msgOut.output2.begin(), msgOut.output2.end());

    std::cout << "\n----------------\n Concatenation\n\n";
    std::cout << "\nSize of concatenated vector: " << msgOut.output3.size();
    std::cout << "\nContents: ";
    for(auto i : msgOut.output3) printf("%02X ", i);

    SysInfoDecoder(msgOut);

    std::cout << "\nEnd of program.\n";
    //std::cin.get();

}
