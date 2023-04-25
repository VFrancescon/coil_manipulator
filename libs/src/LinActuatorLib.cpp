#include <LinActuatorLib/LinActuatorLib.hpp>

LinearActuator::LinearActuator()
    : serialPort("/dev/ttyUSB0", BaudRate::B_9600, NumDataBits::EIGHT,
                 Parity::NONE, NumStopBits::ONE) {
    this->ActuatorSetup();
}

LinearActuator::LinearActuator(std::string COM)
    : serialPort(COM, BaudRate::B_9600, NumDataBits::EIGHT, Parity::NONE,
                 NumStopBits::ONE) {
    this->ActuatorSetup();
}

void LinearActuator::LinearExtend() { this->serialPort.Write(Ext1mm); }

void LinearActuator::LinearContract() { this->serialPort.Write(Ctr1mm); }

void LinearActuator::LinearStop() { this->serialPort.Write(Shtdwn); }

void LinearActuator::ActuatorSetup() {
    this->serialPort.SetTimeout(-1);
    this->serialPort.Open();
}

LinearActuator::~LinearActuator() {
    this->LinearStop();
    this->serialPort.Close();
}