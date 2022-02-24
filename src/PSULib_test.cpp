#include <PSULib_test.hpp>

std::vector<uint8_t> Encoder20(uint8_t PO_STATE, uint8_t addr){
    input_message msgIn(0x20, addr);
    msgIn.cont1_set = 1;
    msgIn.set_contents(PO_STATE);
    
    
    return msgIn.instruction;
}

std::vector<uint8_t> Encoder21(float Voltage, uint8_t addr){
    //std::cout << "Voltage is: " << Voltage << "\n";
    input_message msgIn(0x21, addr);
    DecToHex(Voltage, V_conv, msgIn);
    msgIn.InstructionAssembler();
    return msgIn.instruction;
}

std::vector<uint8_t> Encoder22(float Current, uint8_t addr){
    //std::cout << "Current is: " << Current << "\n";
    input_message msgIn(0x22, addr);
    DecToHex(Current, I_conv, msgIn);
    msgIn.InstructionAssembler();
    return msgIn.instruction;
}

std::vector<uint8_t> Encoder23(float Voltage, float Current, uint8_t addr){
    //std::cout << "Current is: " << Current << "\n";
    input_message msgIn(0x23, addr);
    DecToHex(Voltage, V_conv, msgIn, 1);
    DecToHex(Current, I_conv, msgIn, 2);
    msgIn.InstructionAssembler();
    return msgIn.instruction;
}

std::vector<uint8_t> Encoder24(uint8_t VoltageP, uint8_t CurrentP, uint8_t addr){
    input_message msgIn(0x24, addr);
    msgIn.cont1_set = 1;
    msgIn.cont2_set = 2;
    msgIn.set_contents(VoltageP, CurrentP);
    //msgIn.InstructionAssembler();
    return msgIn.instruction;
}

std::vector<uint8_t> Encoder26(uint8_t addr){
    input_message msgIn(0x26, addr);
    msgIn.InstructionAssembler();
    return msgIn.instruction;
}

std::vector<uint8_t> Encoder28(uint8_t addr){
    input_message msgIn(0x28, addr);
    msgIn.InstructionAssembler();
    return msgIn.instruction;
}

std::vector<uint8_t> Encoder2B(uint8_t addr){
    input_message msgIn(0x2B, addr);
    msgIn.InstructionAssembler();
    return msgIn.instruction;
}

void Decoder26(output_message &msgOut){
    std::cout << "\n----------------\n Concatenation\n\n";
    std::cout << "\nSize of concatenated vector: " << msgOut.output3.size();
    std::cout << "\nContents: ";
    for(auto i : msgOut.output3) printf("%02X ", i);

    msgOut.ADDR = msgOut.output3[1];
    msgOut.CODE = msgOut.output3[2];
    msgOut.LENGTH = msgOut.output3[3];
    msgOut.V_LOW = msgOut.output3[4];
    msgOut.V_HIGH = msgOut.output3[5];
    msgOut.I_LOW = msgOut.output3[6];
    msgOut.I_HIGH = msgOut.output3[7];
    msgOut.CC_OP = msgOut.output3[8];

    ReadVoltage = HexToValue(msgOut.V_HIGH, msgOut.V_LOW, V_conv);
    std::cout << "\nCalculated in func, V float is: " << ReadVoltage;
    ReadCurrent = HexToValue(msgOut.I_HIGH, msgOut.I_LOW, I_conv);
    std::cout << "\nCalculated in func, I float is: " << ReadCurrent;
    POState = (bool)msgOut.PO_STATE;
}

void Decoder28(output_message &msgOut){
    // std::cout << "\n----------------\n Concatenation\n\n";
    // std::cout << "\nSize of concatenated vector: " << msgOut.output3.size();
    // std::cout << "\nContents: ";
    // for(auto i : msgOut.output3) printf("%02X ", i);

    msgOut.ADDR = msgOut.output3[1];
    msgOut.CODE = msgOut.output3[2];
    msgOut.LENGTH = msgOut.output3[3];
    msgOut.PO_STATE = msgOut.output3[4];
    msgOut.V_LOW = msgOut.output3[5];
    msgOut.V_HIGH = msgOut.output3[6];
    msgOut.I_LOW = msgOut.output3[7];
    msgOut.I_HIGH = msgOut.output3[8];

    ReadVoltage = HexToValue(msgOut.V_HIGH, msgOut.V_LOW, V_conv);
    std::cout << "\nCalculated in func, V float is: " << ReadVoltage;
    ReadCurrent = HexToValue(msgOut.I_HIGH, msgOut.I_LOW, I_conv);
    std::cout << "\nCalculated in func, I float is: " << ReadCurrent;
    POState = (bool)msgOut.PO_STATE;
}

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
    // std::cout << "\n----------------\n Concatenation\n\n";
    // std::cout << "\nSize of concatenated vector: " << msgOut.output3.size();
    // std::cout << "\nContents: ";
    // for(auto i : msgOut.output3) printf("%02X ", i);

    msgOut.ADDR = msgOut.output3[1];
    msgOut.CODE = msgOut.output3[2];
    msgOut.LENGTH = msgOut.output3[3];
    msgOut.V_STEP = msgOut.output3[4];
    msgOut.I_STEP = msgOut.output3[5];

    V_conv = pow(10, -int(msgOut.V_STEP));
    I_conv = pow(10, -int(msgOut.I_STEP));


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
        msgIn.cont3_set = 1;
        msgIn.cont4_set = 1;
        break;
    
    default:
        msgIn.CONT1 = (uint8_t)hexConverted;
        msgIn.CONT2 = (uint8_t)(hexConverted >> 8);
        msgIn.cont1_set = 1;
        msgIn.cont2_set = 1;
        break;
    }

    // printf("\nlsb %02X ", msgIn.CONT1);
    // printf("msb %02X\n", msgIn.CONT2);

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
            
            // std::string str = "/dev/ttyUSB0";
            // DXKDP_PSU PSU(str);
            // V_conv = 0.01;
            // I_conv = 0.01;
            output_message msgOut;
            Decoder2B(msgOut);

            std::cout << "V_conv " << V_conv;
            std::cout << "I_conv " << I_conv << "\n";

            std::vector<uint8_t> vect;
            vect = Encoder20(0x01);
            
            std::cout << "20: Contents of input message:\n";
            for(auto i: vect) printf("%02X ", i); std::cout << "\n\n";

            vect.clear();
            vect = Encoder21(41.68);
            std::cout << "21: Contents of input message:\n";
            for(auto i: vect) printf("%02X ", i); std::cout << "\n\n";

            vect.clear();
            vect = Encoder22(12.1);
            std::cout << "22: Contents of input message:\n";
            for(auto i: vect) printf("%02X ", i); std::cout << "\n";

            vect.clear();
            vect = Encoder23(29.1, 15.2);
            std::cout << "23: Contents of input message:\n";
            for(auto i: vect) printf("%02X ", i); std::cout << "\n";

            vect.clear();
            vect = Encoder23(0x01, 0x01);
            std::cout << "23: Contents of input message:\n";
            for(auto i: vect) printf("%02X ", i); std::cout << "\n";

            vect.clear();
            vect = Encoder24(0x01, 0x01);
            std::cout << "24: Contents of input message:\n";
            for(auto i: vect) printf("%02X ", i); std::cout << "\n";

            vect.clear();
            vect = Encoder26();
            std::cout << "26: Contents of input message:\n";
            for(auto i: vect) printf("%02X ", i); std::cout << "\n";


            // std::cout << "\nInput command: ";
            // for(auto i:msgIn.instruction) printf("%02X ", i);
            //PSU.PsuWrite(msgIn);

            // output_message msgOut;
            //PSU.PsuRead(msgOut);
            // Decoder2B(msgOut);
        break;
    }
    



    std::cout << "\nEnd of program.\n";

}
