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
    msgOut.output3.insert(msgOut.output3.end(), msgOut.output1.begin(), msgOut.output1.end());
    msgOut.output3.insert(msgOut.output3.end(), msgOut.output2.begin(), msgOut.output2.end());
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
    std::string str = "/dev/ttyUSB0";
    DXKDP_PSU PSU(str);
    //DXKDP_PSU PSU();
    long cmdIn1;
    float cmdIn2, cmdIn3;

    uint8_t result;
    std::cout << "argc is: " << argc << "\n";
    if(argc > 1) cmdIn1 = strtol(argv[1], NULL, 16);
    //if(argc > 2) cmdIn2 = strtol(argv[2], NULL, 16);
    if(argc > 2) cmdIn2 = atof(argv[2]);
    if(argc > 3) cmdIn3 = atof(argv[3]);

    //printf("cmdIn1= %02X, cmdIn2= %f\n", cmdIn1, cmdIn2);
    output_message msgOut;
    PSU.PsuRead(msgOut);
    Decoder2B(msgOut);
    std::cout << "Vconv = " << V_conv << " Iconv = " << I_conv << "\n";
    
    // V_conv = 0.01;
    // I_conv = 0.01;
    switch(argc)
    {
        
    case 2:
            
            if(cmdIn1 == 0x20){
                PSU_ON_OFF(PSU);
            }
            if(cmdIn1 == 0x24){
                PolarityBruteforce(PSU);
            }
            else std::cout << "Argument given was: " << argv[1] << " which is not on the list\n";
        break;
    case 3:
        if(cmdIn1 == 0x20){
            if((int)cmdIn2 == 0x01){
                result = PoCtrl(PSU, 0x01);
            }
            else result = PoCtrl(PSU, 0x00);
        }
        else if(cmdIn1 == 0x21){
            result = WriteVoltage(PSU, cmdIn2);
        }
        else if(cmdIn1 == 0x22){
            result = WriteCurrent(PSU, cmdIn2);
        }
        break;
    case 4:
        if(cmdIn1 == 0x23){
            result = WriteVI(PSU, cmdIn2, cmdIn3);
        }
        break;

    default:
            std::cout << "No arguments given\n";
        break;
    }
    



    std::cout << "\nEnd of program.\n";

}

void PSU_ON_OFF(DXKDP_PSU &PSU){
    std::vector<uint8_t> input_vector = Encoder20(0x01);
    PSU.PsuWrite(input_vector);
    std::vector<uint8_t> ack = PSU.PsuRead();
    for(auto i: ack) printf("PO=1 returned: %02X\n", i);

    std::cout << "Press enter to continue";
    std::cin.get();

    input_vector.clear();
    ack.clear();
    input_vector = Encoder20(0x00);
    PSU.PsuWrite(input_vector);
    ack = PSU.PsuRead();
    for(auto i: ack) printf("PO=0 returned: %02X\n", i);

}

void PolarityBruteforce(DXKDP_PSU &PSU){
    std::vector<uint8_t> input_vector = Encoder24(0x01, 0x01);
    PSU.PsuWrite(input_vector);
    std::vector<uint8_t> ack = PSU.PsuRead();
    for(auto i: ack) printf("V=1 I=1 returned: %02X\n", i);

    std::cout << "Press enter to continue";
    std::cin.get();

    input_vector.clear();
    ack.clear();
    input_vector = Encoder24(0x00, 0x01);
    PSU.PsuWrite(input_vector);
    ack = PSU.PsuRead();
    for(auto i: ack) printf("V=0 I =1 returned: %02X\n", i);

    std::cout << "Press enter to continue";
    std::cin.get();

    input_vector.clear();
    ack.clear();
    input_vector = Encoder24(0x00, 0x00);
    PSU.PsuWrite(input_vector);
    ack = PSU.PsuRead();
    for(auto i: ack) printf("V=0 I =0 returned: %02X\n", i);

    std::cout << "Press enter to continue";
    std::cin.get();

    input_vector.clear();
    ack.clear();
    input_vector = Encoder24(0x01, 0x00);
    PSU.PsuWrite(input_vector);
    ack = PSU.PsuRead();
    for(auto i: ack) printf("V=1 I=0 returned: %02X\n", i);
}

uint8_t PoCtrl(DXKDP_PSU &PSU, uint8_t po_state){
    std::vector<uint8_t> input_vector = Encoder20(po_state);
    PSU.PsuWrite(input_vector);
    std::vector<uint8_t> ack = PSU.PsuRead();
    return ack[0];

}

uint8_t WriteVoltage(DXKDP_PSU &PSU, float targetV, uint8_t addr){
    std::vector<uint8_t> input_vector = Encoder21(targetV, addr);
    for(auto i: input_vector) printf("%02X ", i);
    PSU.PsuWrite(input_vector);
    std::vector<uint8_t> ack = PSU.PsuRead();
    return ack[0];
    // return 0x06;
}

uint8_t WriteCurrent(DXKDP_PSU &PSU, float targetI, uint8_t addr){
    std::vector<uint8_t> input_vector = Encoder22(targetI, addr);
    for(auto i: input_vector) printf("%02X ", i);
    PSU.PsuWrite(input_vector);
    std::vector<uint8_t> ack = PSU.PsuRead();
    return ack[0];
    // return 0x06;
}

uint8_t WriteVI(DXKDP_PSU &PSU, float targetV, float targetI, uint8_t addr){
    std::vector<uint8_t> input_vector = Encoder23(targetV, targetI, addr);
    for(auto i: input_vector) printf("%02X ", i);
    PSU.PsuWrite(input_vector);
    std::vector<uint8_t> ack = PSU.PsuRead();
    return ack[0];
}