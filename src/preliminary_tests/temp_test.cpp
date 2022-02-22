#include <libs/PSU/PSU_LIB.h>
#include <libs/PSU/instructions.h>

#include <cmath>

// uint8_t VOLTAGE_STEP = 0x02;
// uint8_t CURRENT_STEP = 0x03;

float V_conv, I_conv;

void SysInfoDecoder(output_message &out){
    std::cout << "\nSize of output is:" << out.output.size() << "\nContains: ";
    for(int i = 0; i < 20; i++) printf("at %d contains %02X\n", i, out.output[i]);

    if(out.output.size() != 19) return;
    
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
    std::cout << "Press enter to begin";
    std::cin.get();
    std::string str = "dev/ttyUSB0";
    DXKDP_PSU PSU(str);
    
    output_message msgOut;
    PSU.PsuRead(msgOut);



    // float V_Target = 10.00;

    // float V_CONV = pow(10, (int)VOLTAGE_STEP);
    // float V_Effective = V_Target * V_CONV;
    
    // uint16_t V_HEX = V_Effective;
    // uint8_t VHex_High = (V_HEX >> 8);
    // uint8_t VHEX_Low = (V_HEX & 0x00FF);
    // input_message msg(0x21, 0x01, 0x02);
    // msg.set_contents(VHEX_Low, VHex_High);

    // std::cout << "Reading instruction\n";
    // for(auto i: msg.instruction) printf("%02X ", i);
    
    SysInfoDecoder(msgOut);

    std::cout << "\nEnd of program.\n";
    std::cin.get();

}
