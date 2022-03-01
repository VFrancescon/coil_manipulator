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

/*Scrapped because we do not need that info*/
// std::vector<uint8_t> Encoder2B(uint8_t addr){
//     input_message msgIn(0x2B, addr);
//     msgIn.InstructionAssembler();
//     return msgIn.instruction;
// }

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

/*Scrapped because we do not need that info*/
// void Decoder2B(output_message &msgOut){
//     /*Next 2 lines combine the vectors into something usable*/
//     msgOut.output3.insert(msgOut.output3.end(), msgOut.output1.begin(), msgOut.output1.end());
//     msgOut.output3.insert(msgOut.output3.end(), msgOut.output2.begin(), msgOut.output2.end());
//     msgOut.ADDR = msgOut.output3[1];
//     msgOut.CODE = msgOut.output3[2];
//     msgOut.LENGTH = msgOut.output3[3];
//     msgOut.V_STEP = msgOut.output3[4];
//     msgOut.I_STEP = msgOut.output3[5];
//     V_conv = pow(10, -int(msgOut.V_STEP));
//     I_conv = pow(10, -int(msgOut.I_STEP));
// }

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
    float intermediate = value/Conv;
    uint16_t hexConverted = int(intermediate);
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

/*Scrapped because we do not need that info*/
// void GetSysInfo(DXKDP_PSU &PSU, output_message &msgOut, uint8_t addr){
//     std::vector<uint8_t> input_vector = Encoder2B(addr);
//     PSU.PsuWrite(input_vector);
//     PSU.PsuRead(msgOut);
//     Decoder2B(msgOut);
// }

int main(int argc, char *argv[]){
    std::cout << "Press enter to begin";
    std::cin.get();
    std::string str = "/dev/ttyUSB3";
    DXKDP_PSU PSU(str, 0.01, 0.01);
    //DXKDP_PSU PSU();
    long cmdIn1;
    float cmdIn2, cmdIn3;

    //uint8_t result;
    // std::cout << "argc is: " << argc << "\n";
    
    if(argc > 1) cmdIn1 = strtol(argv[1], NULL, 16);
    if(argc > 2) cmdIn2 = atof(argv[2]);
    if(argc > 3) cmdIn3 = atof(argv[3]);

    std::cout << "in1: " << argv[1] << " in2: " << argv[2] << "\n";
    std::cout << "in1: " << cmdIn1 << " in2: " << cmdIn2 << "\n";
    

    
    
    V_conv = PSU.Vconv;
    I_conv = PSU.Iconv;
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
                PoCtrl(PSU, 0x01);
            }
            else PoCtrl(PSU, 0x00);
        }
        else if(cmdIn1 == 0x21){
            WriteVoltage(PSU, cmdIn2);
        }
        else if(cmdIn1 == 0x22){
            WriteCurrent(PSU, cmdIn2);
        }

        else if(cmdIn1 == 0x24){
            if((int)cmdIn2 == 0x01){
                PolarityBruteforce(PSU);
            }
            else{
                PolarityBruteforce_Mixed(PSU);
            }
        }


        break;
    case 4:
        if(cmdIn1 == 0x23){
            /*If this line gives you an error, please ignore it.
            Intellisense is really dumb it turns out
            */
            WriteVI(PSU, cmdIn2, cmdIn3);
        }
        break;

    default:
            std::cout << "No arguments given\n";
        break;
    }
    
    std::cout << "\nEnd of program.\n";

}




void PSU_ON_OFF(DXKDP_PSU &PSU){
    output_message msgOut;
    std::vector<uint8_t> input_vector = Encoder20(0x01);
    PSU.PsuWrite(input_vector);
    //std::vector<uint8_t> ack = PSU.PsuRead();
    //for(auto i: ack) printf("PO=1 returned: %02X\n", i);

    std::cout << "Press enter to continue";
    std::cin.get();

    //input_vector.clear();
    
    msgOut.output1.clear();
    input_vector = Encoder20(0x00);
    PSU.PsuWrite(input_vector);
    //ack = PSU.PsuRead();
    // for(auto i: ack) printf("PO=0 returned: %02X\n", i);

}

void PoCtrl(DXKDP_PSU &PSU, uint8_t po_state){
    std::vector<uint8_t> input_vector = Encoder20(po_state);
    for(auto i: input_vector) printf("%02X ", i);
    PSU.PsuWrite(input_vector);
    output_message msgOut;
    PSU.PsuRead(msgOut);
    for(auto i: msgOut.output1) printf("\nResult: %02X ", i);
    

    //std::vector<uint8_t> ack = PSU.PsuRead();

}

void WriteVoltage(DXKDP_PSU &PSU, float targetV, uint8_t addr){
    std::vector<uint8_t> input_vector = Encoder21(targetV, addr);
    std::cout << "input vector is: ";
    for(auto i: input_vector) printf("%02X ", i);
    PSU.PsuWrite(input_vector);
    // std::vector<uint8_t> ack = PSU.PsuRead();
    //output_message msgOut;
    //PSU.PsuRead(msgOut);
    //for(auto i: msgOut.output1) printf("%02X ", i);
}

void WriteCurrent(DXKDP_PSU &PSU, float targetI, uint8_t addr){
    std::vector<uint8_t> input_vector = Encoder22(targetI, addr);
    for(auto i: input_vector) printf("%02X ", i);
    PSU.PsuWrite(input_vector);
    // std::vector<uint8_t> ack = PSU.PsuRead();
    
}

void WriteVI(DXKDP_PSU &PSU, float targetV, float targetI, uint8_t addr){
    std::vector<uint8_t> input_vector = Encoder23(targetV, targetI, addr);
    for(auto i: input_vector) printf("%02X ", i);
    PSU.PsuWrite(input_vector);
    // std::vector<uint8_t> ack = PSU.PsuRead();
    
}


void PolarityBruteforce_Mixed(DXKDP_PSU &PSU){
    std::vector<uint8_t> input_vector = Encoder24(0x01, 0x01);
    PSU.PsuWrite(input_vector);
    output_message msgOut;
    PSU.PsuRead(msgOut);
    std::cout << "01 01, ACK: ";
    for(auto i: msgOut.output1) printf("%02X ", i);

    std::cout << "Press enter to continue";
    std::cin.get();

    input_vector.clear();
    
    input_vector = Encoder24(0x00, 0x00);
    PSU.PsuWrite(input_vector);
    PSU.PsuRead(msgOut);
    std::cout << "00 00, ACK: ";
    for(auto i: msgOut.output1) printf("%02X ", i);

    std::cout << "Press enter to continue";
    std::cin.get();

    input_vector.clear();
    input_vector = Encoder24(0x01, 0x00);
    PSU.PsuWrite(input_vector);
    PSU.PsuRead(msgOut);

    std::cout << "01 00, ACK: ";
    for(auto i: msgOut.output1) printf("%02X ", i);
    
    std::cout << "Press enter to continue";
    std::cin.get();

    input_vector.clear();
    
    input_vector = Encoder24(0x00, 0x01);
    PSU.PsuWrite(input_vector);
    PSU.PsuRead(msgOut);
    std::cout << "00 01, ACK: ";
    for(auto i: msgOut.output1) printf("%02X ", i);
}

void PolarityBruteforce(DXKDP_PSU &PSU){
    std::vector<uint8_t> input_vector = Encoder24(0x00, 0x00);
    PSU.PsuWrite(input_vector);
    output_message msgOut;
    PSU.PsuRead(msgOut);
    std::cout << "\n00 00, ACK: ";
    for(auto i: msgOut.output1) printf("%02X ", i);

    std::cout << "Press enter to continue";
    std::cin.get();

    input_vector.clear();
    
    input_vector = Encoder24(0x01, 0x01);
    PSU.PsuWrite(input_vector);
    PSU.PsuRead(msgOut);
    std::cout << "\n01 01, ACK: ";
    for(auto i: msgOut.output1) printf("%02X ", i);

    std::cout << "\nPress enter to continue";
    std::cin.get();

    input_vector.clear();
    input_vector = Encoder24(0x02, 0x02);
    PSU.PsuWrite(input_vector);
    PSU.PsuRead(msgOut);

    std::cout << "02 02, ACK: ";
    for(auto i: msgOut.output1) printf("%02X ", i);
    
    std::cout << "\nPress enter to continue";
    std::cin.get();

    input_vector.clear();
    
    input_vector = Encoder24(0x03, 0x03);
    PSU.PsuWrite(input_vector);
    PSU.PsuRead(msgOut);
    std::cout << "03 03, ACK: ";
    for(auto i: msgOut.output1) printf("%02X ", i);
}

void square_wave(DXKDP_PSU &PSU){
    std::vector<uint8_t> input_vector1;
    std::vector<uint8_t> input_vector2;

    input_vector1 = Encoder23(15.0, 15.0);
    input_vector2 = Encoder23(0, 0);

    std::cout << "ready to go. Press enter";
    std::cin.get();    

    for(int i = 0; i < 50; i++){
        PSU.PsuWrite(input_vector1);
        usleep(500000);
        PSU.PsuWrite(input_vector2);
        usleep(500000);
        
    }
}