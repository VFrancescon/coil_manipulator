#include <LakeshoreF71Lib/LakeshoreF71Lib.hpp>

Teslameter::Teslameter() : serialPort("/dev/ttyUSB0", BaudRate::B_115200, NumDataBits::EIGHT, Parity::NONE, NumStopBits::ONE, FlowControl::HARDWARE) {
    this->TeslameterSetup();
}

Teslameter::Teslameter(std::string COM) : serialPort(COM, BaudRate::B_115200, NumDataBits::EIGHT, Parity::NONE, NumStopBits::ONE, FlowControl::HARDWARE) {
    this->TeslameterSetup();
}


float Teslameter::SingleAxisReading(int AXIS){
    std::string AxisReading, readValue;
    switch(AXIS){
        case 0:
            std::cout << "X axis reading\n";
            AxisReading = fetchField + " X;" + confirmed;
        break;
        
        case 1:
            std::cout << "Y axis reading\n";
            AxisReading = fetchField + " Y;" + confirmed;
        break;

        case 2:
            std::cout << "Z axis reading\n";
            AxisReading = fetchField + " Z;" + confirmed;
        break;

        default:
            std::cout <<"No reading\n";
            return 0.0;
        break;
    }

    this->serialPort.Write(AxisReading);
    this->serialPort.Read(readValue);

    int index = readValue.find(";");
    if(std::stoi(readValue.substr(index+1,1)) != 1) return 0.0;

    return std::stof(readValue.substr(0, index));

}

std::vector<float> Teslameter::AllAxisReading(){
    std::string AllAxis = fetchField + " ALL;" + confirmed;
    std::string readValue;

    this->serialPort.Write(AllAxis);
    this->serialPort.Read(readValue);

    std::cout << "Read value: " << readValue;

    std::vector<float> returned_value;
    return returned_value;
}


void Teslameter::TeslameterSetup(){
    this->serialPort.SetTimeout(-1);
    this->serialPort.Open();

    // std::string setupCmd = autoRange + ";:" + fieldTesla + ";" + confirmed;
    // std::string readValue;

    // this->serialPort.Write(setupCmd);
    // this->serialPort.Read(readValue);
    // if(std::stoi(readValue) != 1) std::cout << "Error. Could not set up range and units\n";
    

}

std::string Teslameter::SimpleSingleAxis(){
    std::string input, output;

    input = "SENS:FIEL:RANG:AUTO 1;:UNIT:FIEL TESLA;:FETC:FIEL:DC? X;*OPC?";
    this->serialPort.Write(input);
    this->serialPort.Read(output);

    return output;
}

Teslameter::~Teslameter(){
    this->serialPort.Close();
}