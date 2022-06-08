#include <HCoilMiddlewareLib/HCoilMiddlewareLib.hpp>

MiddlewareLayer::MiddlewareLayer() : PSU_X1("/dev/ttyUSB3", 0.1, 0.01), PSU_Y1("/dev/ttyUSB4", 0.01, 0.01), PSU_Z1("/dev/ttyUSB2", 0.01, 0.01),
T_Meter("/dev/ttyUSB0"), LinAct("/dev/ttyUSB1")
{
    /*
    3x PSUs
    1x Teslameter
    1x Linear Actuator
    */

   /**
    * @todo
    * Research how to bring back unique_ptrs at some point
    * 
    */
    // std::unique_ptr<DXKDP_PSU> PSU_X1 = std::make_unique<DXKDP_PSU>("/dev/ttyUSB3", 0.01, 0.01);
    // std::unique_ptr<DXKDP_PSU> PSU_Y1 = std::make_unique<DXKDP_PSU>("/dev/ttyUSB4", 0.01, 0.01);
    // std::unique_ptr<DXKDP_PSU> PSU_Z1 = std::make_unique<DXKDP_PSU>("/dev/ttyUSB2", 0.01, 0.01);

    // std::unique_ptr<Teslameter> T_Meter = std::make_unique<Teslameter>("/dev/ttyUSB3");
    // std::unique_ptr<LinearActuator> LinAct = std::make_unique<LinearActuator>("/dev/ttyUSB4");
    
    this->initialSetup();
    
}

MiddlewareLayer::MiddlewareLayer(std::string PSUX_PORT, std::string PSUY_PORT, std::string PSUZ_PORT, std::string TMETER_PORT, std::string LINACT_PORT ): 
PSU_X1(PSUX_PORT, 0.1, 0.01), PSU_Y1(PSUY_PORT, 0.01, 0.01), PSU_Z1(PSUZ_PORT, 0.01, 0.01),
T_Meter(TMETER_PORT), LinAct(LINACT_PORT)
{
    
    // std::unique_ptr<DXKDP_PSU> PSU_X1 = std::make_unique<DXKDP_PSU>(PSUX_PORT, 0.01, 0.01);
    // std::unique_ptr<DXKDP_PSU> PSU_Y1 = std::make_unique<DXKDP_PSU>(PSUY_PORT, 0.01, 0.01);
    // std::unique_ptr<DXKDP_PSU> PSU_Z1 = std::make_unique<DXKDP_PSU>(PSUZ_PORT, 0.1, 0.1);

    // std::unique_ptr<Teslameter> T_Meter = std::make_unique<Teslameter>(TMETER_PORT);
    // std::unique_ptr<LinearActuator> LinAct = std::make_unique<LinearActuator>(LINACT_PORT);
    this->initialSetup();
    
}

void MiddlewareLayer::TurnOnSupply(){
    std::thread thread_x1(&DXKDP_PSU::PoCtrl, &PSU_X1, 0x01);
    std::thread thread_y1(&DXKDP_PSU::PoCtrl, &PSU_Y1, 0x01);
    std::thread thread_z1(&DXKDP_PSU::PoCtrl, &PSU_Z1, 0x01);
    thread_x1.join();
    thread_y1.join();
    thread_z1.join();
}

void MiddlewareLayer::TurnOffSupply(){
    std::thread th_x(&DXKDP_PSU::WriteVI, &PSU_X1, 0, 0.00, 0x01);
    std::thread th_y(&DXKDP_PSU::WriteVI, &PSU_Y1, 0, 0.00, 0x01);
    std::thread th_z(&DXKDP_PSU::WriteVI, &PSU_Z1, 0, 0.00, 0x01);
    th_x.join();
    th_y.join();
    th_z.join();


    std::thread thread_x1(&DXKDP_PSU::PoCtrl, &PSU_X1, 0x00);
    std::thread thread_y1(&DXKDP_PSU::PoCtrl, &PSU_Y1, 0x00);
    std::thread thread_z1(&DXKDP_PSU::PoCtrl, &PSU_Z1, 0x00);
    thread_x1.join();
    thread_y1.join();
    thread_z1.join();
}

void MiddlewareLayer::initialSetup(){
    std::thread thread_x1(&DXKDP_PSU::WriteVI, &PSU_X1, 60, 0.00, 0x01);
    std::thread thread_y1(&DXKDP_PSU::WriteVI, &PSU_Y1, 60, 0.00, 0x01);
    std::thread thread_z1(&DXKDP_PSU::WriteVI, &PSU_Z1, 60, 0.00, 0x01);
    thread_x1.join();
    thread_y1.join();
    thread_z1.join();
    this->outputFile.open(filename, std::ios::out);
    this->outputFile << "Reading, Bx\n";

    this->leftoverTimeFile.open("../leftovertime.csv", std::ios::out);
    this->leftoverTimeFile << "Reading, Leftover time(us), Frequency\n";

    this->TurnOnSupply();

}

void MiddlewareLayer::set3DVector(std::vector<float> I_X, std::vector<float> I_Y, std::vector<float> I_Z){
    
    //setting how much the stepper motor will be extended by at the end of the function.
    //this is used in the destructor to retract the tentacle back.
    this->stepper_count = I_X.size();
    for(int i = 0; i < I_X.size(); i++){

        /*
        Single threaded polarity check below

        this->PolarityCheck(I_X[i], 0);
        this->PolarityCheck(I_Y[i], 1);
        this->PolarityCheck(I_Z[i], 2);

        */

        std::thread th_x(&MiddlewareLayer::PolarityCheck, this, I_X[i], MiddlewareLayer::PSU_ENUM::X1);
        std::thread th_y(&MiddlewareLayer::PolarityCheck, this, I_Y[i], MiddlewareLayer::PSU_ENUM::Y1);
        std::thread th_z(&MiddlewareLayer::PolarityCheck, this, I_Z[i], MiddlewareLayer::PSU_ENUM::Z1);
        th_x.join();
        th_y.join();
        th_z.join();
        // this->PolarityCheck(I_X[i], 0);
        // this->PolarityCheck(I_Y[i], 1);
        // this->PolarityCheck(I_Z[i], 2);

        /*
        Single threaded Write Current Below
        this->PSU_X1.WriteCurrent(abs(I_X[i]));
        this->PSU_Y1.WriteCurrent(abs(I_Y[i]));
        this->PSU_Z1.WriteCurrent(abs(I_Z[i]));
        this->writeXField();
        this->LinAct.LinearExtend();
        */
        

        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        std::thread thread_x1(&DXKDP_PSU::WriteCurrent, &PSU_X1, abs(I_X[i])*cal_x, 0x01);
        std::thread thread_y1(&DXKDP_PSU::WriteCurrent, &PSU_Y1, abs(I_Y[i])*cal_y, 0x01);
        std::thread thread_z1(&DXKDP_PSU::WriteCurrent, &PSU_Z1, abs(I_Z[i])*cal_z, 0x01);
        std::thread thread_te(&MiddlewareLayer::writeXField, this);
        std::thread thread_i(&LinearActuator::LinearExtend, &LinAct);
        thread_x1.join();
        thread_y1.join();
        thread_z1.join();
        thread_te.join();
        thread_i.join();

        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        int duration_us = int(std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count());
        int sleep_us = period_us = duration_us;
        
        std::cout << "going to sleep for: " << sleep_us/1000 << "ms\n";
        leftoverTimeFile << leftoverTime_count << "," << sleep_us << "," << 1/float(sleep_us)*1000000 << "\n";
        usleep(sleep_us);
    }
}


void MiddlewareLayer::setX1Vector(std::vector<float> current_){
    this->stepper_count =current_.size();

    for (size_t i = 0; i < current_.size(); i++)
    {
        this->PolarityCheck(current_[i], MiddlewareLayer::PSU_ENUM::X1);
        std::thread thread_PSU(&DXKDP_PSU::WriteCurrent, &PSU_X1, abs(current_[i])*cal_x, 0x01);
        std::thread thread_te(&MiddlewareLayer::writeXField, this);
        std::thread thread_i(&LinearActuator::LinearExtend, &LinAct);
        thread_PSU.join();
        thread_te.join();
        thread_i.join();
    }
}
void MiddlewareLayer::setY1Vector(std::vector<float> current_){
    this->stepper_count =current_.size();

    for (size_t i = 0; i < current_.size(); i++)
    {
        this->PolarityCheck(current_[i], MiddlewareLayer::PSU_ENUM::X1);
        std::thread thread_PSU(&DXKDP_PSU::WriteCurrent, &PSU_Y1, abs(current_[i])*cal_y, 0x01);
        // std::thread thread_te(&MiddlewareLayer::writeXField, this);
        std::thread thread_i(&LinearActuator::LinearExtend, &LinAct);
        thread_PSU.join();
        // thread_te.join();
        thread_i.join();
    }
}

void MiddlewareLayer::setZ1Vector(std::vector<float> current_){
    this->stepper_count =current_.size();

    for (size_t i = 0; i < current_.size(); i++)
    {
        this->PolarityCheck(current_[i], MiddlewareLayer::PSU_ENUM::X1);
        std::thread thread_PSU(&DXKDP_PSU::WriteCurrent, &PSU_Z1, abs(current_[i])*cal_z, 0x01);
        // std::thread thread_te(&MiddlewareLayer::writeYField, this);
        std::thread thread_i(&LinearActuator::LinearExtend, &LinAct);
        thread_PSU.join();
        // thread_te.join();
        thread_i.join();
    }
}

void MiddlewareLayer::setX2Vector(std::vector<float> current_){
    this->stepper_count =current_.size();

    for (size_t i = 0; i < current_.size(); i++)
    {
        this->PolarityCheck(current_[i], MiddlewareLayer::PSU_ENUM::X1);
        std::thread thread_PSU(&DXKDP_PSU::WriteCurrent, &PSU_X2, abs(current_[i])*cal_x, 0x01);
        std::thread thread_te(&MiddlewareLayer::writeXField, this);
        std::thread thread_i(&LinearActuator::LinearExtend, &LinAct);
        thread_PSU.join();
        thread_te.join();
        thread_i.join();
    }
}


void MiddlewareLayer::setY2Vector(std::vector<float> current_){
    this->stepper_count =current_.size();

    for (size_t i = 0; i < current_.size(); i++)
    {
        this->PolarityCheck(current_[i], MiddlewareLayer::PSU_ENUM::X1);
        std::thread thread_PSU(&DXKDP_PSU::WriteCurrent, &PSU_Y2, abs(current_[i])*cal_y, 0x01);
        // std::thread thread_te(&MiddlewareLayer::writeXField, this);
        std::thread thread_i(&LinearActuator::LinearExtend, &LinAct);
        thread_PSU.join();
        // thread_te.join();
        thread_i.join();
    }
}

void MiddlewareLayer::setZ2Vector(std::vector<float> current_){
    this->stepper_count =current_.size();

    for (size_t i = 0; i < current_.size(); i++)
    {
        this->PolarityCheck(current_[i], MiddlewareLayer::PSU_ENUM::X1);
        std::thread thread_PSU(&DXKDP_PSU::WriteCurrent, &PSU_Z2, abs(current_[i])*cal_z, 0x01);
        // std::thread thread_te(&MiddlewareLayer::writeXField, this);
        std::thread thread_i(&LinearActuator::LinearExtend, &LinAct);
        thread_PSU.join();
        // thread_te.join();
        thread_i.join();
    }
}

void MiddlewareLayer::PolarityCheck(float input, MiddlewareLayer::PSU_ENUM psu_){
    switch(psu_){
        case MiddlewareLayer::PSU_ENUM::X1:
            if(input < 0) {PSU_X1.setPolarity(0x1); printf("Flipped polarity, X1\n");}
            else PSU_X1.setPolarity(0x0);
        break;
        case MiddlewareLayer::PSU_ENUM::Y1:
            if(input < 0) {PSU_Y1.setPolarity(0x1); printf("Flipped polarity, Y1\n");}
            else PSU_Y1.setPolarity(0x0);
        break;
        case MiddlewareLayer::PSU_ENUM::Z1:
            if(input < 0) {PSU_Z1.setPolarity(0x1); printf("Flipped polarity, Z1\n");}
            else PSU_Z1.setPolarity(0x0);
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
    this->leftoverTimeFile.close();
    // std::cout << "Row count: " << this->row_count;
    for(int i = 0; i < this->row_count; i++){
        this->LinAct.LinearContract();
        std::cout << "i= " << i << "\n";
    }
    this->LinAct.LinearStop();
    std::cout << "Shutting down\n";
}