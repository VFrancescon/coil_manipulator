#include <HCoilMiddlewareLib/HCoilMiddlewareLib.hpp>

MiddlewareLayer::MiddlewareLayer() : PSU_X("/dev/ttyUSB3", 0.1, 0.01), PSU_Y("/dev/ttyUSB4", 0.01, 0.01), PSU_Z("/dev/ttyUSB2", 0.01, 0.01),
T_Meter("/dev/ttyUSB0"), LinAct("/dev/ttyUSB1")
{
    /*
    3x PSUs
    1x Teslameter
    1x Linear Actuator
    */

   /**
    * @brief 
    * Research how to bring back unique_ptrs at some point
    * 
    */
    // std::unique_ptr<DXKDP_PSU> PSU_X = std::make_unique<DXKDP_PSU>("/dev/ttyUSB3", 0.01, 0.01);
    // std::unique_ptr<DXKDP_PSU> PSU_Y = std::make_unique<DXKDP_PSU>("/dev/ttyUSB4", 0.01, 0.01);
    // std::unique_ptr<DXKDP_PSU> PSU_Z = std::make_unique<DXKDP_PSU>("/dev/ttyUSB2", 0.01, 0.01);

    // std::unique_ptr<Teslameter> T_Meter = std::make_unique<Teslameter>("/dev/ttyUSB3");
    // std::unique_ptr<LinearActuator> LinAct = std::make_unique<LinearActuator>("/dev/ttyUSB4");
    
    this->initialSetup();
    
}

MiddlewareLayer::MiddlewareLayer(std::string PSUX_PORT, std::string PSUY_PORT, std::string PSUZ_PORT, std::string TMETER_PORT, std::string LINACT_PORT ): 
PSU_X(PSUX_PORT, 0.1, 0.01), PSU_Y(PSUY_PORT, 0.01, 0.01), PSU_Z(PSUZ_PORT, 0.01, 0.01),
T_Meter(TMETER_PORT), LinAct(LINACT_PORT)
{
    
    // std::unique_ptr<DXKDP_PSU> PSU_X = std::make_unique<DXKDP_PSU>(PSUX_PORT, 0.01, 0.01);
    // std::unique_ptr<DXKDP_PSU> PSU_Y = std::make_unique<DXKDP_PSU>(PSUY_PORT, 0.01, 0.01);
    // std::unique_ptr<DXKDP_PSU> PSU_Z = std::make_unique<DXKDP_PSU>(PSUZ_PORT, 0.1, 0.1);

    // std::unique_ptr<Teslameter> T_Meter = std::make_unique<Teslameter>(TMETER_PORT);
    // std::unique_ptr<LinearActuator> LinAct = std::make_unique<LinearActuator>(LINACT_PORT);
    this->initialSetup();
    
}

void MiddlewareLayer::TurnOnSupply(){
    std::thread thread_x(&DXKDP_PSU::PoCtrl, &PSU_X, 0x01);
    std::thread thread_y(&DXKDP_PSU::PoCtrl, &PSU_Y, 0x01);
    std::thread thread_z(&DXKDP_PSU::PoCtrl, &PSU_Z, 0x01);
    thread_x.join();
    thread_y.join();
    thread_z.join();
}

void MiddlewareLayer::TurnOffSupply(){
    std::thread th_x(&DXKDP_PSU::WriteVI, &PSU_X, 0, 0.00, 0x01);
    std::thread th_y(&DXKDP_PSU::WriteVI, &PSU_Y, 0, 0.00, 0x01);
    std::thread th_z(&DXKDP_PSU::WriteVI, &PSU_Z, 0, 0.00, 0x01);
    th_x.join();
    th_y.join();
    th_z.join();


    std::thread thread_x(&DXKDP_PSU::PoCtrl, &PSU_X, 0x00);
    std::thread thread_y(&DXKDP_PSU::PoCtrl, &PSU_Y, 0x00);
    std::thread thread_z(&DXKDP_PSU::PoCtrl, &PSU_Z, 0x00);
    thread_x.join();
    thread_y.join();
    thread_z.join();
}

void MiddlewareLayer::initialSetup(){
    std::thread thread_x(&DXKDP_PSU::WriteVI, &PSU_X, 60, 0.00, 0x01);
    std::thread thread_y(&DXKDP_PSU::WriteVI, &PSU_Y, 60, 0.00, 0x01);
    std::thread thread_z(&DXKDP_PSU::WriteVI, &PSU_Z, 60, 0.00, 0x01);
    thread_x.join();
    thread_y.join();
    thread_z.join();

    this->TurnOnSupply();
}

void MiddlewareLayer::set3DVector(std::vector<float> I_X, std::vector<float> I_Y, std::vector<float> I_Z){
    this->stepper_count = I_X.size();
    for(int i = 0; i < I_X.size(); i++){

        std::thread th_x(&MiddlewareLayer::PolarityCheck, this, I_X[i], 0);
        std::thread th_y(&MiddlewareLayer::PolarityCheck, this, I_Y[i], 1);
        std::thread th_z(&MiddlewareLayer::PolarityCheck, this, I_Z[i], 2);
        th_x.join();
        th_y.join();
        th_z.join();

        std::thread thread_x(&DXKDP_PSU::WriteCurrent, &PSU_X, abs(I_X[i]), 0x01);
        std::thread thread_y(&DXKDP_PSU::WriteCurrent, &PSU_Y, abs(I_Y[i]), 0x01);
        std::thread thread_z(&DXKDP_PSU::WriteCurrent, &PSU_Z, abs(I_Z[i]), 0x01);
        // std::thread thread_i(&LinearActuator::LinearExtend, &LinAct);
        thread_x.join();
        thread_y.join();
        thread_z.join();
        // thread_i.join();

        sleep(1);
    }
}

void MiddlewareLayer::PolarityCheck(float input, int PSU_CHOSER){
    switch(PSU_CHOSER){
        case 0:
            if(input < 0) {PSU_X.setPolarity(0x1); printf("Flipped polarity\n");}
            else PSU_X.setPolarity(0x0);
        break;
        case 1:
            if(input < 0) {PSU_Y.setPolarity(0x1); printf("Flipped polarity\n");}
            else PSU_Y.setPolarity(0x0);
        break;
        case 2:
            if(input < 0) {PSU_Z.setPolarity(0x1); printf("Flipped polarity\n");}
            else PSU_Z.setPolarity(0x0);
        break;
    }
    
}

float MiddlewareLayer::getXField(){
    return T_Meter.SingleAxisReading(Teslameter::AXIS::X);
}

MiddlewareLayer::~MiddlewareLayer(){
    this->TurnOffSupply();
    // for(int i = stepper_count; i = 0; i--){
    //     this->LinAct.LinearContract();
    // }
    // this->LinAct.LinearStop();
}