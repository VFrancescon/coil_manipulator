#include <PSULib_test.hpp>


/*
Takes Voltage, Current and Step Size from the PSUs.
A bit unsure what the voltage actually represents as of now.
*/
void Decoder2B(output_message &msgOut){
    
    /*Block here is for debugging of the two vectors read*/
    //std::cout << "\nSize of given vect is:" << msgOut.output3.size();
    // std::cout << "\nsize of first output: " << msgOut.output1.size();
    // std::cout << "\nContents of first output: ";
    // for(auto i : msgOut.output1) printf("%02X ", i);
    // std::cout << "\nsize of second output: " << msgOut.output2.size();
    // std::cout << "\nContents of second output: ";
    // for(auto i : msgOut.output2) printf("%02X ", i);
    
    /*Next 2 lines combine the vectors into something usable*/
    // msgOut.output3.insert(msgOut.output3.end(), msgOut.output1.begin(), msgOut.output1.end());
    // msgOut.output3.insert(msgOut.output3.end(), msgOut.output2.begin(), msgOut.output2.end());
    std::cout << "\n----------------\n Concatenation\n\n";
    std::cout << "\nSize of concatenated vector: " << msgOut.output3.size();
    std::cout << "\nContents: ";
    for(auto i : msgOut.output3) printf("%02X ", i);



    msgOut.ADDR = msgOut.output3[1];
    msgOut.CODE = msgOut.output3[2];
    msgOut.LENGTH = msgOut.output3[3];
    msgOut.V_STEP = msgOut.output3[4];
    msgOut.I_STEP = msgOut.output3[5];

    V_conv = pow(10, -int(msgOut.V_STEP));
    I_conv = pow(10, -int(msgOut.I_STEP));
    printf("\nVSTEP %02X hex, ISTEP %02X hex", msgOut.V_STEP, msgOut.I_STEP);
    printf("\nV_Conv: %f  I_Conv: %f ", V_conv, I_conv);

    msgOut.V_HIGH = msgOut.output3[9];
    msgOut.V_LOW = msgOut.output3[10];

    msgOut.I_HIGH = msgOut.output3[11];
    msgOut.I_LOW = msgOut.output3[12];

    // float VoltageFloat = (float)HexToDec(msgOut.V_HIGH, msgOut.V_LOW) * V_conv;
    // std::cout << "\nCalculated in func, V float is: " << VoltageFloat;
    // float CurrentFloat = (float)HexToDec(msgOut.I_HIGH, msgOut.I_LOW) * I_conv;
    // std::cout << "\nCalculated in func, I float is: " << CurrentFloat;

    float VoltageFloat = HexToValue(msgOut.V_HIGH, msgOut.V_LOW, V_conv);
    std::cout << "\nCalculated in func, V float is: " << VoltageFloat;
    float CurrentFloat = HexToValue(msgOut.I_HIGH, msgOut.I_LOW, I_conv);
    std::cout << "\nCalculated in func, I float is: " << CurrentFloat;

}

/*Takes high and low bit, combines them into an int*/
int HexToDec(uint8_t MSB, uint8_t LSB){
    uint16_t combinedHex = (MSB << 8) + LSB;
    return (int)combinedHex;
}

float HexToValue(uint8_t MSB, uint8_t LSB, float Conv){
    uint16_t combinedHex = (MSB << 8) + LSB;
    return (float)combinedHex * Conv;
}

void DecToHex(float value, float Conv, input_message &msgIn, int entry){
    uint16_t hexConverted = int(value/Conv);
    switch (entry)
    {
    case 2:
        msgIn.CONT3 = (uint8_t)hexConverted;
        msgIn.CONT4 = (uint8_t)(hexConverted >> 8);
        break;
    
    default:
        msgIn.CONT1 = (uint8_t)hexConverted;
        msgIn.CONT2 = (uint8_t)(hexConverted >> 8);
        break;
    }

    // printf("lsb %02X ", msgIn.CONT1);
    // printf("msb %02X ", msgIn.CONT2);

}

int main(int argc, char *argv[]){
    std::cout << "Press enter to begin";
    std::cin.get();
    float cmd_line;
    input_message msgIn;
    switch(argc)
    {
    case 2:
            cmd_line = atof(argv[1]);
            DecToHex(cmd_line, 0.01, msgIn);
        break;
    default:
            
            std::string str = "/dev/ttyUSB0";
            DXKDP_PSU PSU(str);
            
            
            std::cout << "\nInput command: ";
            for(auto i:msgIn.instruction) printf("%02X ", i);
            //PSU.PsuWrite(msgIn);

            output_message msgOut;
            //PSU.PsuRead(msgOut);
            Decoder2B(msgOut);
        break;
    }
    



    std::cout << "\nEnd of program.\n";

}
