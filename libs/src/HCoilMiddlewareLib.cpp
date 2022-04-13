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
    this->outputFile.open(filename, std::ios::out);
    this->outputFile << "Reading, Bx\n";

    this->leftoverTimeFile.open("../leftovertime.csv", std::ios::out);
    this->leftoverTimeFile << "Reading, Leftover time(us), Frequency\n";

    this->TurnOnSupply();

}

void MiddlewareLayer::set3DVector(std::vector<float> I_X, std::vector<float> I_Y, std::vector<float> I_Z){
    this->stepper_count = I_X.size();
    for(int i = 0; i < I_X.size(); i++){

        /*
        Single threaded polarity check below

        this->PolarityCheck(I_X[i], 0);
        this->PolarityCheck(I_Y[i], 1);
        this->PolarityCheck(I_Z[i], 2);

        */

        std::thread th_x(&MiddlewareLayer::PolarityCheck, this, I_X[i], 0);
        std::thread th_y(&MiddlewareLayer::PolarityCheck, this, I_Y[i], 1);
        std::thread th_z(&MiddlewareLayer::PolarityCheck, this, I_Z[i], 2);
        th_x.join();
        th_y.join();
        th_z.join();


        /*
        Single threaded Write Current Below
        this->PSU_X.WriteCurrent(abs(I_X[i]));
        this->PSU_Y.WriteCurrent(abs(I_Y[i]));
        this->PSU_Z.WriteCurrent(abs(I_Z[i]));
        this->writeXField();
        */
        

        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        std::thread thread_x(&DXKDP_PSU::WriteCurrent, &PSU_X, abs(I_X[i])*cal_x, 0x01);
        std::thread thread_y(&DXKDP_PSU::WriteCurrent, &PSU_Y, abs(I_Y[i])*cal_y, 0x01);
        std::thread thread_z(&DXKDP_PSU::WriteCurrent, &PSU_Z, abs(I_Z[i])*cal_z, 0x01);
        std::thread thread_te(&MiddlewareLayer::writeXField, this);
        // std::thread thread_i(&LinearActuator::LinearExtend, &LinAct);
        thread_x.join();
        thread_y.join();
        thread_z.join();
        thread_te.join();
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        int duration_us = int(std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count());
        int sleep_us = period_us = duration_us;
        // thread_i.join();
        std::cout << "going to sleep for: " << sleep_us*1000 << "ms\n";
        leftoverTimeFile << leftoverTime_count << "," << sleep_us << "," << 1/sleep_us << "\n";
        usleep(sleep_us);
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

void MiddlewareLayer::writeXField(){
    this->outputFile << row_count++ << "," << this->getXField() << "\n";
}

MiddlewareLayer::~MiddlewareLayer(){
    this->TurnOffSupply();
    this->outputFile.close();
    // for(int i = stepper_count; i = 0; i--){
    //     this->LinAct.LinearContract();
    // }
    // this->LinAct.LinearStop();
}