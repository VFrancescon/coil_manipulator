#include <HCoilMiddlewareLib/HCoilMiddlewareLib.hpp>

MiddlewareLayer::MiddlewareLayer(){
    /*
    3x PSUs
    1x Teslameter
    1x Linear Actuator
    */
    std::unique_ptr<DXKDP_PSU> PSU_X = std::make_unique<DXKDP_PSU>("/dev/ttyUSB0", 0.01, 0.01);
    std::unique_ptr<DXKDP_PSU> PSU_Y = std::make_unique<DXKDP_PSU>("/dev/ttyUSB1", 0.01, 0.01);
    std::unique_ptr<DXKDP_PSU> PSU_Z = std::make_unique<DXKDP_PSU>("/dev/ttyUSB2", 0.1, 0.1);

    std::unique_ptr<Teslameter> T_Meter = std::make_unique<Teslameter>("/dev/ttyUSB3");
    std::unique_ptr<LinearActuator> LinAct = std::make_unique<LinearActuator>("/dev/ttyUSB4");

    this->initialSetup();
    
}

MiddlewareLayer::MiddlewareLayer(std::string PSUX_PORT, std::string PSUY_PORT, std::string PSUZ_PORT, std::string TMETER_PORT, std::string LINACT_PORT ){
    
    std::unique_ptr<DXKDP_PSU> PSU_X = std::make_unique<DXKDP_PSU>(PSUX_PORT, 0.01, 0.01);
    std::unique_ptr<DXKDP_PSU> PSU_Y = std::make_unique<DXKDP_PSU>(PSUY_PORT, 0.01, 0.01);
    std::unique_ptr<DXKDP_PSU> PSU_Z = std::make_unique<DXKDP_PSU>(PSUZ_PORT, 0.1, 0.1);

    std::unique_ptr<Teslameter> T_Meter = std::make_unique<Teslameter>(TMETER_PORT);
    std::unique_ptr<LinearActuator> LinAct = std::make_unique<LinearActuator>(LINACT_PORT);
    
}

void MiddlewareLayer::TurnOnSupply(){
    std::thread thread_x(&DXKDP_PSU::PoCtrl, *PSU_X, 0x01);
    std::thread thread_y(&DXKDP_PSU::PoCtrl, *PSU_Y, 0x01);
    std::thread thread_z(&DXKDP_PSU::PoCtrl, *PSU_Z, 0x01);
    thread_x.join();
    thread_y.join();
    thread_z.join();
}

void MiddlewareLayer::TurnOffSupply(){
    std::thread thread_x(&DXKDP_PSU::PoCtrl, *PSU_X, 0x00);
    std::thread thread_y(&DXKDP_PSU::PoCtrl, *PSU_Y, 0x00);
    std::thread thread_z(&DXKDP_PSU::PoCtrl, *PSU_Z, 0x00);
    thread_x.join();
    thread_y.join();
    thread_z.join();
}

void MiddlewareLayer::initialSetup(){
    std::thread thread_x(&DXKDP_PSU::WriteVI, *PSU_X, 60, 0.00, 0x01);
    std::thread thread_y(&DXKDP_PSU::WriteVI, *PSU_Y, 60, 0.00, 0x01);
    std::thread thread_z(&DXKDP_PSU::WriteVI, *PSU_Z, 60, 0.00, 0x01);
    thread_x.join();
    thread_y.join();
    thread_z.join();

    this->TurnOnSupply();
}

void MiddlewareLayer::set3DVector(std::vector<float> I_X, std::vector<float> I_Y, std::vector<float> I_Z){
    for(int i = 0; i < I_X.size(); i++){
        std::thread thread_x(&DXKDP_PSU::WriteCurrent, *PSU_X, I_X[i], 0x01);
        std::thread thread_y(&DXKDP_PSU::WriteCurrent, *PSU_Y, I_Y[i], 0x01);
        std::thread thread_z(&DXKDP_PSU::WriteCurrent, *PSU_Z, I_Z[i], 0x01);
        std::thread thread_i(&LinearActuator::LinearExtend, *LinAct);
        thread_x.join();
        thread_y.join();
        thread_z.join();
        // sleep(1);
        std::cin.get();
    }
}

float MiddlewareLayer::getXField(){
    return T_Meter->SingleAxisReading(Teslameter::AXIS::X);
}

void MiddlewareLayer::Introducer1mm(){
    this->LinAct->LinearExtend();
}

MiddlewareLayer::~MiddlewareLayer(){
    this->TurnOffSupply();
    this->LinAct->LinearStop();
}