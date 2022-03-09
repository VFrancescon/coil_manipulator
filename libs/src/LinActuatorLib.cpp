#include <LinActuatorLib/LinActuatorLib.hpp>

LinearActuator::LinearActuator() : serialPort("/dev/ttyUSB0", BaudRate::B_9600, NumDataBits::EIGHT, Parity::NONE, NumStopBits::ONE){
    this->ActuatorSetup();
}

LinearActuator::LinearActuator(std::string COM) : serialPort(COM, BaudRate::B_9600, NumDataBits::EIGHT, Parity::NONE, NumStopBits::ONE){
    this->ActuatorSetup();
}

void LinearActuator::LinearExtend(){
    this->serialPort.WriteBinary(Ext1mm_vect);
}

void LinearActuator::LinearContract(){
    this->serialPort.WriteBinary(Ctr1mm_vect);
}

void LinearActuator::LinearStop(){
    this->serialPort.WriteBinary(Shtdwn_vect);
}

void LinearActuator::ActuatorSetup(){
    this->serialPort.SetTimeout(-1);
    this->serialPort.Open();
}

LinearActuator::~LinearActuator(){
    this->LinearStop();
    this->serialPort.Close();
}