#include <DxkdpLib/DxkdpLib.hpp>

DXKDP_PSU::DXKDP_PSU()
    : serialPort("/dev/ttyUSB0", BaudRate::B_9600, NumDataBits::EIGHT,
                 Parity::NONE, NumStopBits::ONE) {
    // default constructor, here for debugging mainly
    // will instantiate a power supply at ttyUSB0, addr 1

    this->DXKDP_Setup();
    std::cout << "Serial port has been opened";
}

DXKDP_PSU::DXKDP_PSU(std::string COM_PORT)
    : serialPort(COM_PORT, BaudRate::B_9600, NumDataBits::EIGHT, Parity::NONE,
                 NumStopBits::ONE) {
    this->PsuID = COM_PORT;
    this->DXKDP_Setup();
    std::cout << "Serial port has been opened";
}

DXKDP_PSU::DXKDP_PSU(std::string COM_PORT, float V_conv, float I_conv)
    : serialPort(COM_PORT, BaudRate::B_9600, NumDataBits::EIGHT, Parity::NONE,
                 NumStopBits::ONE) {
    this->PsuID = COM_PORT;
    this->Vconv = V_conv;
    this->Iconv = I_conv;
    std::cout << "PSUID: " << this->PsuID << ". Serial port has been opened\n";
    this->DXKDP_Setup();
}

void DXKDP_PSU::DXKDP_Setup() {
    this->serialPort.SetTimeout(200);
    this->serialPort.Open();
}

void DXKDP_PSU::PsuWrite(input_message msgIn) {
    this->serialPort.WriteBinary(msgIn.instruction);
}

void DXKDP_PSU::PsuWrite(std::vector<uint8_t> input) {
    // std::cout << "Started PSUWrite on " << this->PsuID << " ";
    // for(auto i: input){
    //     printf("%02X ", i);
    // }
    // std::cout << "\n";
    this->serialPort.WriteBinary(input);
    // std::cout << "Finished PSUWrite on " << this->PsuID << " \n";
}

void DXKDP_PSU::PsuRead(output_message &msgOut) {
    // std::cout << "Started PSUread on " << this->PsuID << " \n";
    this->serialPort.ReadBinary(msgOut.output1);
    // std::cout << "From psuread. size of returned values: " <<
    // msgOut.output1.size() << "\n"; std::cout << "Finished psuread on " <<
    // this->PsuID << " \n";
}

DXKDP_PSU::~DXKDP_PSU() {
    std::cout << "Shutting down PSUID: " << this->PsuID << "\n";
    this->WriteVI(0, 0);
    usleep(50e3);
    this->PoCtrl(0x00);
    this->serialPort.Close();
}

std::vector<uint8_t> DXKDP_PSU::Encoder20(uint8_t PO_STATE, uint8_t addr) {
    input_message msgIn(0x20, addr);
    msgIn.cont1_set = 1;
    msgIn.set_contents(PO_STATE);

    return msgIn.instruction;
}

std::vector<uint8_t> DXKDP_PSU::Encoder21(float Voltage, uint8_t addr) {
    // std::cout << "Voltage is: " << Voltage << "\n";
    input_message msgIn(0x21, addr);
    this->DecToHex(Voltage, Vconv, msgIn);
    msgIn.InstructionAssembler();
    return msgIn.instruction;
}

std::vector<uint8_t> DXKDP_PSU::Encoder22(float Current, uint8_t addr) {
    // std::cout << "Current is: " << Current << "\n";
    input_message msgIn(0x22, addr);
    this->DecToHex(Current, Iconv, msgIn);
    msgIn.InstructionAssembler();
    return msgIn.instruction;
}

std::vector<uint8_t> DXKDP_PSU::Encoder22Gen2(float Current, uint8_t addr) {
    // std::cout << "Current is: " << Current << "\n";
    Current = abs(Current);
    input_message msgIn(0x22, addr);
    this->DecToHexSigned(Current, Iconv, msgIn);
    msgIn.InstructionAssembler();
    return msgIn.instruction;
}

std::vector<uint8_t> DXKDP_PSU::Encoder23(float Voltage, float Current,
                                          uint8_t addr) {
    // std::cout << "Current is: " << Current << "\n";
    input_message msgIn(0x23, addr);
    this->DecToHex(Voltage, Vconv, msgIn, 1);
    this->DecToHex(Current, Iconv, msgIn, 2);
    msgIn.InstructionAssembler();
    return msgIn.instruction;
}

std::vector<uint8_t> DXKDP_PSU::Encoder23Gen2(float Voltage, float Current,
                                              uint8_t addr) {
    // std::cout << "Current is: " << Current << "\n";
    Current = abs(Current);
    input_message msgIn(0x23, addr);
    this->DecToHex(Voltage, Vconv, msgIn, 1);
    this->DecToHexSigned(Current, Iconv, msgIn, 2);
    msgIn.InstructionAssembler();
    return msgIn.instruction;
}

std::vector<uint8_t> DXKDP_PSU::Encoder24(uint8_t VoltageP, uint8_t CurrentP,
                                          uint8_t addr) {
    input_message msgIn(0x24, addr);
    msgIn.cont1_set = 1;
    msgIn.cont2_set = 2;
    msgIn.set_contents(VoltageP, CurrentP);
    // msgIn.InstructionAssembler();
    return msgIn.instruction;
}

std::vector<uint8_t> DXKDP_PSU::Encoder26(uint8_t addr) {
    input_message msgIn(0x26, addr);
    msgIn.InstructionAssembler();
    return msgIn.instruction;
}

std::vector<uint8_t> DXKDP_PSU::Encoder28(uint8_t addr) {
    input_message msgIn(0x28, addr);
    msgIn.InstructionAssembler();
    return msgIn.instruction;
}

void DXKDP_PSU::Decoder26(output_message &msgOut) {
    msgOut.output3 = msgOut.output1;
    msgOut.output3.insert(msgOut.output3.end(), msgOut.output2.begin(),
                          msgOut.output2.end());
    // std::cout << "\n----------------\n Concatenation\n\n";
    // std::cout << "\nSize of concatenated vector: " << msgOut.output3.size();
    // std::cout << "\nContents: ";
    // for(auto i : msgOut.output3) printf("%02X ", i);

    msgOut.ADDR = msgOut.output3[1];
    msgOut.CODE = msgOut.output3[2];
    msgOut.LENGTH = msgOut.output3[3];
    msgOut.V_LOW = msgOut.output3[4];
    msgOut.V_HIGH = msgOut.output3[5];
    msgOut.I_LOW = msgOut.output3[6];
    msgOut.I_HIGH = msgOut.output3[7];
    msgOut.CC_OP = msgOut.output3[8];

    this->ReadVoltage = HexToValue(msgOut.V_HIGH, msgOut.V_LOW, this->Vconv);
    this->ReadCurrent = HexToValue(msgOut.I_HIGH, msgOut.I_LOW, this->Iconv);
    POstate = (bool)msgOut.PO_STATE;
}

void DXKDP_PSU::Decoder28(output_message &msgOut) {
    msgOut.ADDR = msgOut.output3[1];
    msgOut.CODE = msgOut.output3[2];
    msgOut.LENGTH = msgOut.output3[3];
    msgOut.PO_STATE = msgOut.output3[4];
    msgOut.V_LOW = msgOut.output3[5];
    msgOut.V_HIGH = msgOut.output3[6];
    msgOut.I_LOW = msgOut.output3[7];
    msgOut.I_HIGH = msgOut.output3[8];

    ReadVoltage = HexToValue(msgOut.V_HIGH, msgOut.V_LOW, Vconv);
    // std::cout << "\nCalculated in func, V float is: " << ReadVoltage;
    ReadCurrent = HexToValue(msgOut.I_HIGH, msgOut.I_LOW, Iconv);
    // std::cout << "\nCalculated in func, I float is: " << ReadCurrent;
    POstate = (bool)msgOut.PO_STATE;
}

/*Takes high and low bit, combines them into an int*/
int DXKDP_PSU::HexToDec(uint8_t MSB, uint8_t LSB) {
    uint16_t combinedHex = (MSB << 8) + LSB;
    return (int)combinedHex;
}

float DXKDP_PSU::HexToValue(uint8_t MSB, uint8_t LSB, float Conv) {
    uint16_t combinedHex = (MSB << 8) + LSB;
    return (float)combinedHex * Conv;
}

void DXKDP_PSU::DecToHex(float value, float Conv, input_message &msgIn,
                         int entry) {
    float intermediate = value / Conv;
    uint16_t hexConverted = int(intermediate);
    switch (entry) {
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
}

void DXKDP_PSU::DecToHexSigned(float value, float Conv, input_message &msgIn,
                               int entry) {
    value = abs(value);
    float intermediate = value / Conv;
    int intermediate_INT = (int)intermediate;
    int negativeConvert = 65536;
    int intermediate_FLIP = negativeConvert - intermediate_INT;
    uint16_t hexConverted = (uint16_t)intermediate_FLIP;

    switch (entry) {
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
}

void DXKDP_PSU::PoCtrl(uint8_t po_state) {
    std::vector<uint8_t> input_vector = this->Encoder20(po_state);
    // for(auto i: input_vector) printf("%02X ", i);
    this->PsuWrite(input_vector);
    usleep(200e3);
    output_message msgOut;
    this->PsuRead(msgOut);
    // std::cout << "PoCtrl. size of returned values: " << msgOut.output1.size()
    // << "\n";
    this->PsuRead(msgOut);
    // if(msgOut.output1.size() == 0){
    //     std::cout << "PoCtrl. PsuID: " << this->PsuID << "\n";
    //     THROW_EXCEPT("Poctrl did not return.");
    // }
    if (msgOut.output1[0] != 0x06) {
        std::cout << "PoCtrl. PsuID: " << this->PsuID << "\n";
        THROW_EXCEPT("PowerOut setting did not return 0x06. Aborting");
    } else
        return;
}

void DXKDP_PSU::WriteVoltage(float targetV, uint8_t addr) {
    std::vector<uint8_t> input_vector = this->Encoder21(targetV, addr);
    // std::cout << "input vector is: ";
    // for (auto i : input_vector)
    //     printf("%02X ", i);
    this->PsuWrite(input_vector);
    usleep(200e3);
    output_message msgOut;
    this->PsuRead(msgOut);
    // for(auto i: msgOut.output1) printf("\nResult: %02X ", i);
    this->PsuRead(msgOut);
    if (msgOut.output1.size() == 0) {
        std::cout << "WriteV. PsuID: " << this->PsuID << "\n";
        THROW_EXCEPT("Write V did not return.");
    }
    if (msgOut.output1[0] != 0x06) {
        std::cout << "WriteV .PsuID: " << this->PsuID << "\n";
        THROW_EXCEPT("WriteVoltage setting did not return 0x06. Aborting");
    } else
        return;
}

void DXKDP_PSU::WriteCurrent(float targetI, uint8_t addr) {
    std::vector<uint8_t> input_vector = this->Encoder22(targetI, addr);

    // for(auto i: input_vector) printf("%02X ", i);
    this->PsuWrite(input_vector);
    usleep(200e3);
    output_message msgOut;
    this->PsuRead(msgOut);
    this->PsuRead(msgOut);
    //print input vector
    for(auto i: input_vector) printf("Input: %02X ", i);
    if (msgOut.output1.size() == 0) {
        std::cout << "WriteI. PsuID: " << this->PsuID << "\n";
        THROW_EXCEPT("Write I did not return.");
    }
    // for(auto i: msgOut.output1) printf("\nResult: %02X ", i);
    if (msgOut.output1[0] != 0x06) {
        std::cout << "WriteI. PsuID: " << this->PsuID << "\n";
        THROW_EXCEPT("WriteCurrent setting did not return 0x06. Aborting");
    } else
        return;
}

void DXKDP_PSU::WriteCurrentGen2(float targetI, uint8_t addr) {
    std::vector<uint8_t> input_vector;
    if (targetI >= 0) {
        input_vector = this->Encoder22(targetI, addr);
    } else {
        input_vector = this->Encoder22Gen2(targetI, addr);
    }
    // for(auto i: input_vector) printf("%02X ", i);
    this->PsuWrite(input_vector);
    usleep(200e3);
    output_message msgOut;
    this->PsuRead(msgOut);
    if (msgOut.output1.size() == 0) {
        std::cout << "WriteI. PsuID: " << this->PsuID << "\n";
        THROW_EXCEPT("Write I did not return.");
    }
    if (msgOut.output1[0] != 0x06) {
        std::cout << "WriteI. PsuID: " << this->PsuID << "\n";
        THROW_EXCEPT("WriteCurrent setting did not return 0x06. Aborting");
    } else
        return;
}

void DXKDP_PSU::WriteVI(float targetV, float targetI, uint8_t addr) {
    std::vector<uint8_t> input_vector = this->Encoder23(targetV, targetI, addr);
    // std::cout << "Printing input_vector, size: "<< input_vector.size() <<
    // "\n"; for(auto i: input_vector) printf("%02X ", i); for(int i = 0; i <
    // input_vector.size(); i++){
    //     printf("%02X ", input_vector[i]);
    // }
    this->PsuWrite(input_vector);
    usleep(200e3);
    output_message msgOut;
    this->PsuRead(msgOut);
    // std::cout << "WriteVI. size of returned values: " <<
    // msgOut.output1.size() << "\n";

    //print psuID
    // std::cout << "WriteVI. PsuID: " << this->PsuID << "";

    // std::cout << "Input: ";
    // //print input_vector
    // for(auto i: input_vector) printf("%02X ", i);
    

    if (msgOut.output1.size() == 0) {
        std::cout << "WriteVI. PsuID: " << this->PsuID << ".\n";
        for (auto i : input_vector) printf("%02X ", i);
        std::cout << "\n";
        // return;
        THROW_EXCEPT("WriteVI did not return.\n");
    }
    //print output vector
    // std::cout << "Result: ";
    // for(auto i: msgOut.output1) printf("%02X ", i);
    // std::cout << "\n";
    if (msgOut.output1[0] != 0x06) {
        std::cout << "WriteVI. PsuID: " << this->PsuID << "\n";
        THROW_EXCEPT("Write VI setting did not return 0x06. Aborting");
    } else {
        return;
    }
}

void DXKDP_PSU::WriteVIGen2(float targetV, float targetI, uint8_t addr) {
    std::vector<uint8_t> input_vector;
    if (targetI >= 0) {
        input_vector = this->Encoder23(targetV, targetI, addr);
    } else {
        input_vector = this->Encoder23Gen2(targetV, targetI, addr);
    }  // std::cout << "Printing input_vector, size: "<< input_vector.size() <<
       // "\n";
    // for(auto i: input_vector) printf("%02X ", i);
    // for(int i = 0; i < input_vector.size(); i++){
    //     printf("%02X ", input_vector[i]);
    // }
    this->PsuWrite(input_vector);
    usleep(200e3);
    output_message msgOut;
    this->PsuRead(msgOut);

    // //print psuID
    // std::cout << "WriteVI. PsuID: " << this->PsuID << "";

    // std::cout << "Input: ";
    // //print input_vector
    // for(auto i: input_vector) printf("%02X ", i);

    if (msgOut.output1.size() == 0) {
        std::cout << "WriteVI. PsuID: " << this->PsuID << "\n";
        for (auto i : input_vector) printf("%02X ", i);
        std::cout << "\n";
        THROW_EXCEPT("WriteVI did not return.\n");
        // this->WriteVIGen2(targetV, targetI);
    }
    //print output vector
    // std::cout << "Result: ";
    // for(auto i: msgOut.output1) printf("%02X ", i);
    // std::cout << "\n";

    if (msgOut.output1[0] != 0x06) {
        std::cout << "WriteVI. PsuID: " << this->PsuID << "\n";
        THROW_EXCEPT("Write VI setting did not return 0x06. Aborting");
    } else {
        return;
    }
}

void DXKDP_PSU::ReadVI(uint8_t addr) {
    std::vector<uint8_t> input_vector = this->Encoder26();
    this->PsuWrite(input_vector);
    usleep(200e3);
    output_message msgOut;
    this->PsuRead(msgOut);
    this->serialPort.ReadBinary(msgOut.output1);
    this->serialPort.ReadBinary(msgOut.output2);

    // for(auto i: msgOut.output1){
    //     printf(" %02X", i);
    // }
    // for(auto i: msgOut.output2){
    //     printf(" %02X", i);
    // }

    this->Decoder26(msgOut);

    if (msgOut.output1[0] == 0x15) {
        std::cout << "PsuID: " << this->PsuID << "\n";
        THROW_EXCEPT("Reading VI did not return 0x06. Aborting");
    } else
        return;
}

void DXKDP_PSU::setPolarity(uint8_t polarity, uint8_t addr) {
    // if (polarity > 0x01)
    // {
    //     std::cout << "PsuID: " << this->PsuID << " ";
    //     THROW_EXCEPT("Polarity setting called with polarity > 0x01. If you do
    //     require such value, please use GEN2 version of the function");
    // }
    std::vector<uint8_t> input_vector =
        this->Encoder24(polarity, polarity, addr);
    // for(auto i: input_vector) printf("%02X ", i);
    // std::cout << "\n\n";
    this->PsuWrite(input_vector);
    usleep(200e3);
    output_message msgOut;
    this->PsuRead(msgOut);
    // std::cout << "Gen2 polarity. size of returned values: " <<
    // msgOut.output1.size() << "\n";
    if (msgOut.output1.size() == 0) {
        std::cout << "PolarityGen1. PsuID: " << this->PsuID << ".\n";
        for (auto i : input_vector) printf("%02X ", i);
        std::cout << "\n";
        THROW_EXCEPT("WriteVI did not return.\n");
        // THROW_EXCEPT("PolarityGen1 setting did not return anything.
        // Aborting");
    }
    if (msgOut.output1[0] != 0x06) {
        std::cout << "Polarity. PsuID: " << this->PsuID << "\n";
        THROW_EXCEPT("Polarity setting did not return 0x06. Aborting");
    } else {
        // std::cout << "-------------------SET
        // POLARITY--------------------\n\n\n";
        return;
    }
}


uint8_t DXKDP_PSU::debugWriteVI(float targetV, float targetI, uint8_t addr){
    std::vector<uint8_t> input_vector = this->Encoder23(targetV, targetI, addr);
    // std::cout << "Printing input_vector, size: "<< input_vector.size() <<
    // "\n"; for(auto i: input_vector) printf("%02X ", i); for(int i = 0; i <
    // input_vector.size(); i++){
    //     printf("%02X ", input_vector[i]);
    // }
    this->PsuWrite(input_vector);
    usleep(200e3);
    output_message msgOut;
    this->PsuRead(msgOut);
    // std::cout << "WriteVI. size of returned values: " <<
    // msgOut.output1.size() << "\n";

    //print psuID
    std::cout << "WriteVI. PsuID: " << this->PsuID << "";

    std::cout << "Input: ";
    //print input_vector
    for(auto i: input_vector) printf("%02X ", i);
    

    if (msgOut.output1.size() == 0) {
        std::cout << "No return value. PsuID: " << this->PsuID << ".\n";
        // for (auto i : input_vector) printf("%02X ", i);
        // std::cout << "\n";
        // return;
        // THROW_EXCEPT("WriteVI did not return.\n");
        return 0x99;
    } else {
        std::cout << "Result: ";
        for(auto i: msgOut.output1) printf("%02X ", i);
        return msgOut.output1.at(0);
    }
}