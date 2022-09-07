#include <HCoilMiddlewareLib/HCoilMiddlewareLib.hpp>

MiddlewareLayer::MiddlewareLayer(){

    
    this->setUniquePSUS();

    //sensors and actuators
    this->uniqueLinAct = std::make_unique<LinearActuator>("/dev/ttyUSB6");
    // this->uniqueT_Meter = std::make_unique<Teslameter>("/dev/ttyUSB7");

    this->initialSetup();
}

MiddlewareLayer::MiddlewareLayer(std::string PSUX1_PORT, std::string PSUY1_PORT, std::string PSUZ1_PORT, 
    std::string PSUX2_PORT, std::string PSUY2_PORT, std::string PSUZ2_PORT, 
    std::string TMETER_PORT, std::string LINACT_PORT )
{
    
    // <X/Y/Z>1 PSUs
    // this->uniquePSU_X1 = std::make_unique<DXKDP_PSU>(PSUX1_PORT, 0.1, 0.01);
    // this->uniquePSU_Y1 = std::make_unique<DXKDP_PSU>(PSUY1_PORT, 0.1, 0.01);
    this->uniquePSU_Z1 = std::make_unique<DXKDP_PSU>(PSUZ1_PORT, 0.1, 0.01);
    
    // <X/Y/Z>1 PSUs
    this->uniquePSU_X2 = std::make_unique<DXKDP_PSU>(PSUX2_PORT, 0.1, 0.01);
    this->uniquePSU_Y2 = std::make_unique<DXKDP_PSU>(PSUY2_PORT, 0.1, 0.01);
    this->uniquePSU_Z2 = std::make_unique<DXKDP_PSU>(PSUZ2_PORT, 0.1, 0.01);

    //sensors and actuators
    // this->uniqueLinAct = std::make_unique<LinearActuator>(LINACT_PORT);
    // this->uniqueT_Meter = std::make_unique<Teslameter>(LINACT_PORT);

    this->initialSetup();
    
}


MiddlewareLayer::MiddlewareLayer(bool PSU_ONLY){
    this->PSU_MODE = PSU_ONLY;
    if(this->PSU_MODE){

        this->setUniquePSUS();
        
        this->initialSetup();
    }
    else{
        this->setUniquePSUS();
        this->uniqueLinAct = std::make_unique<LinearActuator>("/dev/ttyUSB6");
        this->uniqueT_Meter = std::make_unique<Teslameter>("/dev/ttyUSB7");
        this->initialSetup();
    }
}

void MiddlewareLayer::setUniquePSUS(){
        // <X/Y/Z>1 PSUs
    this->uniquePSU_X1 = std::make_unique<DXKDP_PSU>("/dev/ttyUSB2", 0.01, 0.01);
    // this->uniquePSU_Y1 = std::make_unique<DXKDP_PSU>("/dev/ttyUSB1", 0.01, 0.01);
    this->uniquePSU_Z1 = std::make_unique<DXKDP_PSU>("/dev/ttyUSB4", 0.01, 0.01);
    
    // <X/Y/Z>2 PSUs
    this->uniquePSU_X2 = std::make_unique<DXKDP_PSU>("/dev/ttyUSB3", 0.01, 0.01);
    // this->uniquePSU_Y2 = std::make_unique<DXKDP_PSU>("/dev/ttyUSB5", 0.01, 0.01);
    this->uniquePSU_Z2 = std::make_unique<DXKDP_PSU>("/dev/ttyUSB5", 0.01, 0.01);

    return;
}

void MiddlewareLayer::TurnOnSupply(){
    std::thread thread_x1(&DXKDP_PSU::PoCtrl, uniquePSU_X1.get(), 0x01);
    std::thread thread_x2(&DXKDP_PSU::PoCtrl, uniquePSU_X2.get(), 0x01);
    std::thread thread_z1(&DXKDP_PSU::PoCtrl, uniquePSU_Z1.get(), 0x01);
    std::thread thread_z2(&DXKDP_PSU::PoCtrl, uniquePSU_Z2.get(), 0x01);

    thread_x1.join();
    thread_x2.join();
    thread_z1.join();
    thread_z2.join();
}

void MiddlewareLayer::TurnOffSupply(){
    std::thread th_x1(&DXKDP_PSU::WriteVI, uniquePSU_X1.get(), 0, 0.00, 0x01);
    std::thread th_x2(&DXKDP_PSU::WriteVI, uniquePSU_X2.get(), 0, 0.00, 0x01);
    std::thread th_z1(&DXKDP_PSU::WriteVI, uniquePSU_Z1.get(), 0, 0.00, 0x01);
    std::thread th_z2(&DXKDP_PSU::WriteVI, uniquePSU_Z2.get(), 0, 0.00, 0x01);
    th_x1.join();
    th_x2.join();
    th_z1.join();
    th_z2.join();

    std::thread thread_x1(&DXKDP_PSU::PoCtrl, uniquePSU_X1.get(), 0x00);
    std::thread thread_x2(&DXKDP_PSU::PoCtrl, uniquePSU_X2.get(), 0x00);
    std::thread thread_z1(&DXKDP_PSU::PoCtrl, uniquePSU_Z1.get(), 0x00);
    std::thread thread_z2(&DXKDP_PSU::PoCtrl, uniquePSU_Z2.get(), 0x00);
    thread_x1.join();
    thread_x2.join();
    thread_z1.join();
    thread_z2.join();
}

void MiddlewareLayer::initialSetup(){
    // std::cout <<" Error in initial setup"
    std::thread thread_x1(&DXKDP_PSU::WriteVI, uniquePSU_X1.get(), 60, 0.00, 0x01);
    std::thread thread_x2(&DXKDP_PSU::WriteVI, uniquePSU_X2.get(), 60, 0.00, 0x01);
    std::thread thread_z1(&DXKDP_PSU::WriteVI, uniquePSU_Z1.get(), 60, 0.00, 0x01);
    std::thread thread_z2(&DXKDP_PSU::WriteVI, uniquePSU_Z2.get(), 60, 0.00, 0x01);
    thread_x1.join();
    thread_x2.join();
    thread_z1.join();
    thread_z2.join();
    PositivePolarity = true;
    this->TurnOnSupply();
}

void MiddlewareLayer::set3DVector(std::vector<float> I_X, std::vector<float> I_Y, std::vector<float> I_Z){
    
    // this->stepper_count += I_X.size();
    for(int i = 0; i < I_X.size(); i++){

        std::thread th_x1(&MiddlewareLayer::PolarityCheck, this, I_X[i], MiddlewareLayer::PSU_ENUM::X1);
        std::thread th_x2(&MiddlewareLayer::PolarityCheck, this, I_X[i], MiddlewareLayer::PSU_ENUM::X2);
        std::thread th_z1(&MiddlewareLayer::PolarityCheck, this, I_Z[i], MiddlewareLayer::PSU_ENUM::Z1);
        std::thread th_z2(&MiddlewareLayer::PolarityCheck, this, I_Z[i], MiddlewareLayer::PSU_ENUM::Z2);
        th_x1.join();
        th_x2.join();
        th_z1.join();
        th_z2.join();

        //starting timing here
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        std::thread thread_x1(&DXKDP_PSU::WriteCurrent, uniquePSU_X1.get(), abs(I_X[i])*cal_x, 0x01);
        std::thread thread_x2(&DXKDP_PSU::WriteCurrent, uniquePSU_X2.get(), abs(I_X[i])*cal_x, 0x01);
        std::thread thread_z1(&DXKDP_PSU::WriteCurrent, uniquePSU_Z1.get(), abs(I_Z[i])*cal_z, 0x01);
        std::thread thread_z2(&DXKDP_PSU::WriteCurrent, uniquePSU_Z2.get(), abs(I_Z[i])*cal_z, 0x01);
        // std::thread thread_te(&MiddlewareLayer::writeXField, this);
        // std::thread introducer_thread(&LinearActuator::LinearExtend, uniqueLinAct.get());
        thread_x1.join();
        thread_x2.join();
        thread_z1.join();
        thread_z2.join();
        // thread_te.join();
        // introducer_thread.join();

        //ending timing here. Then calculating diffs and printing.
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        int duration_us = int(std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count());
        int sleep_us = period_us - duration_us;
        
        if(sleep_us > 0 ){
            // std::cout << "going to sleep for: " << sleep_us/1000 << "ms\n";
            // leftoverTimeFile << leftoverTime_count << "," << sleep_us << "," << 1/float(sleep_us)*1000000 << "\n";
            usleep(sleep_us);
        }
    }
}

void MiddlewareLayer::set3DVectorIN(std::vector<float> I_X, std::vector<float> I_Y, std::vector<float> I_Z){
    
    //setting how much the stepper motor will be extended by at the end of the function.
    //this is used in the destructor to retract the tentacle back.
    
    if(PSU_MODE){
        std::cout << "ERROR: Function " << __func__ << " was called, but middleware was initialised in PSU only mode. Exiting.\n";
        return;
    }   
    this->stepper_count += I_X.size();
    for(int i = 0; i < I_X.size(); i++){

        std::thread th_x1(&MiddlewareLayer::PolarityCheck, this, I_X[i], MiddlewareLayer::PSU_ENUM::X1);
        std::thread th_x2(&MiddlewareLayer::PolarityCheck, this, I_X[i], MiddlewareLayer::PSU_ENUM::X2);
        std::thread th_z1(&MiddlewareLayer::PolarityCheck, this, I_Z[i], MiddlewareLayer::PSU_ENUM::Z1);
        std::thread th_z2(&MiddlewareLayer::PolarityCheck, this, I_Z[i], MiddlewareLayer::PSU_ENUM::Z2);
        th_x1.join();
        th_x2.join();
        th_z1.join();
        th_z2.join();

        //starting timing here
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        std::thread thread_x1(&DXKDP_PSU::WriteCurrent, uniquePSU_X1.get(), abs(I_X[i])*cal_x, 0x01);
        std::thread thread_x2(&DXKDP_PSU::WriteCurrent, uniquePSU_X2.get(), abs(I_X[i])*cal_x, 0x01);
        std::thread thread_z1(&DXKDP_PSU::WriteCurrent, uniquePSU_Z1.get(), abs(I_Z[i])*cal_z, 0x01);
        std::thread thread_z2(&DXKDP_PSU::WriteCurrent, uniquePSU_Z2.get(), abs(I_Z[i])*cal_z, 0x01);
        std::thread introducer_thread(&LinearActuator::LinearExtend, uniqueLinAct.get());
        // std::thread thread_te(&MiddlewareLayer::writeXField, this);
        thread_x1.join();
        thread_x2.join();
        thread_z1.join();
        thread_z2.join();        
                
        // thread_te.join();
        introducer_thread.join();

        //ending timing here. Then calculating diffs and printing.
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        int duration_us = int(std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count());
        int sleep_us = period_us - duration_us;
        
        if(sleep_us > 0 ){
            // std::cout << "IN.going to sleep for: " << sleep_us/1000 << "ms\n";
            // leftoverTimeFile << leftoverTime_count << "," << sleep_us << "," << 1/float(sleep_us)*1000000 << "\n";
            usleep(sleep_us);

        }
    }
    std::cout << "IN. Reached the end of CSV\n";
}

void MiddlewareLayer::set3DVectorOUT(std::vector<float> I_X, std::vector<float> I_Y, std::vector<float> I_Z){
    
    //setting how much the stepper motor will be extended by at the end of the function.
    //this is used in the destructor to retract the tentacle back.
    this->stepper_count -= I_X.size();
    
    if(PSU_MODE){
        std::cout << "ERROR: Function " << __func__ << " was called, but middleware was initialised in PSU only mode. Exiting.\n";
        return;
    }

    for(int i = 0; i < I_X.size(); i++){

        std::thread th_x1(&MiddlewareLayer::PolarityCheck, this, I_X[i], MiddlewareLayer::PSU_ENUM::X1);
        std::thread th_x2(&MiddlewareLayer::PolarityCheck, this, I_X[i], MiddlewareLayer::PSU_ENUM::X2);
        std::thread th_z1(&MiddlewareLayer::PolarityCheck, this, I_Z[i], MiddlewareLayer::PSU_ENUM::Z1);
        std::thread th_z2(&MiddlewareLayer::PolarityCheck, this, I_Z[i], MiddlewareLayer::PSU_ENUM::Z2);
        th_x1.join();
        th_x2.join();
        th_z1.join();
        th_z2.join();

        //starting timing here
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        // std::thread thread_x1(&DXKDP_PSU::WriteCurrent, uniquePSU_X1.get(), abs(I_X[i])*cal_x, 0x01);
        std::thread thread_x1(&DXKDP_PSU::WriteCurrent, uniquePSU_X1.get(), abs(I_X[i])*cal_x, 0x01);
        std::thread thread_x2(&DXKDP_PSU::WriteCurrent, uniquePSU_X2.get(), abs(I_X[i])*cal_x, 0x01);
        std::thread thread_z1(&DXKDP_PSU::WriteCurrent, uniquePSU_Z1.get(), abs(I_Z[i])*cal_z, 0x01);
        std::thread thread_z2(&DXKDP_PSU::WriteCurrent, uniquePSU_Z2.get(), abs(I_Z[i])*cal_z, 0x01);
        // std::thread thread_te(&MiddlewareLayer::writeXField, this);
        
        std::thread introducer_thread(&LinearActuator::LinearContract, uniqueLinAct.get());
        thread_x1.join();
        thread_x2.join();
        thread_z1.join();
        thread_z2.join();        
                
        // thread_te.join();
        introducer_thread.join();

        //ending timing here. Then calculating diffs and printing.
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        int duration_us = int(std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count());
        int sleep_us = period_us - duration_us;
        
        if(sleep_us > 0 ){
            // std::cout << "OUT.going to sleep for: " << sleep_us/1000 << "ms\n";
            // leftoverTimeFile << leftoverTime_count << "," << sleep_us << "," << 1/float(sleep_us)*1000000 << "\n";
            usleep(sleep_us);
        }
    }
    std::cout << "OUT. Reached the end of CSV\n";
}

void MiddlewareLayer::set3DField(float I_X, float I_Y, float I_Z){
    std::thread th_x1(&MiddlewareLayer::PolarityCheck, this, I_X, MiddlewareLayer::PSU_ENUM::X1);
    std::thread th_x2(&MiddlewareLayer::PolarityCheck, this, I_X, MiddlewareLayer::PSU_ENUM::X2);
    std::thread th_z1(&MiddlewareLayer::PolarityCheck, this, I_Z, MiddlewareLayer::PSU_ENUM::Z1);
    std::thread th_z2(&MiddlewareLayer::PolarityCheck, this, I_Z, MiddlewareLayer::PSU_ENUM::Z2);
    th_x1.join();
    th_x2.join();
    th_z1.join();
    th_z2.join();

    std::thread thread_x1(&DXKDP_PSU::WriteCurrent, uniquePSU_X1.get(), abs(I_X)*cal_x, 0x01);
    std::thread thread_x2(&DXKDP_PSU::WriteCurrent, uniquePSU_X2.get(), abs(I_X)*cal_x, 0x01);
    std::thread thread_z1(&DXKDP_PSU::WriteCurrent, uniquePSU_Z1.get(), abs(I_Z)*cal_z, 0x01);
    std::thread thread_z2(&DXKDP_PSU::WriteCurrent, uniquePSU_Z2.get(), abs(I_Z)*cal_z, 0x01);
    thread_x1.join();
    thread_x2.join();
    thread_z1.join();
    thread_z2.join();

}

void MiddlewareLayer::stepIntroducer(){
    this->stepper_count++;
    this->uniqueLinAct->LinearExtend();    
}

void MiddlewareLayer::stepIntroducer(int stepCount_){
    this->stepper_count += stepCount_;
    for(int i = 0; i < stepCount_; i++){
        this->uniqueLinAct->LinearExtend();
    }
}

void MiddlewareLayer::PolarityCheck(float input, MiddlewareLayer::PSU_ENUM psu_){
    
    /**
     * @note Big note regarding polarities in the PSUs.\n
     * The set polarity command given in the PSU manual is not very clear, 
     * so the following has been found through trial and error.\n
     * The polarity command takes either 0x00 or 0x01 as an argument and does something with it.\n
     * Find here a table explaining what each case does to each PSU.\n
     * 
     * 
     * Input | PSU | Result
     * ------|-----|--------
     * 0x00  |  X2 | -ve  
     * 0x01  |  X2 | +ve
     * 0x00  |  Z1 | -ve  
     * 0x01  |  Z1 | +ve
     * 0x00  |  Z2 | -ve  
     * 0x01  |  Z2 | +ve
     * 0x00  |  Y1 | -ve  
     * 0x01  |  Y1 | +ve
     * 0x00  |  Y2 | +ve  
     * 0x01  |  Y2 | -ve
     * 
     * @note Because of the last 2 rows (Y2), the switch case handling Y2 polarity is accordingly reversed.
     
     * @note THIS DOES NOT HOLD UP IN THE CURRENT BARREL ROLL ARRANGEMENT
     */

    
    
    switch(psu_){
        //block of X related cases
        case MiddlewareLayer::PSU_ENUM::X1:
            if(input > 0) {
                uniquePSU_X1->setPolarity(0x1); }
                // printf("Flipped polarity, X1\n");}
            else uniquePSU_X1->setPolarity(0x0);
        break;
        case MiddlewareLayer::PSU_ENUM::X2:
            if(input > 0) {
                uniquePSU_X2->setPolarity(0x0); }
                // printf("Flipped polarity, X1\n");}
            else uniquePSU_X2->setPolarity(0x1);
        break;
        
        //block of Y related cases
        case MiddlewareLayer::PSU_ENUM::Y1:
            if(input > 0) {uniquePSU_Y1->setPolarity(0x1); 
            // printf("Flipped polarity, Y1\n");
            }
            else uniquePSU_Y1->setPolarity(0x0);
        break;
        
        case MiddlewareLayer::PSU_ENUM::Y2:
            if(input > 0) {uniquePSU_Y2->setPolarity(0x1); 
            // printf("Flipped polarity, Y2\n");
            }
            else uniquePSU_Y2->setPolarity(0x0);
        break;


        //block of Z related cases
        case MiddlewareLayer::PSU_ENUM::Z1:
            if(input > 0) {
                uniquePSU_Z1->setPolarity(0x1); 
                // printf("Flipped polarity, Z1\n");
            }
            else uniquePSU_Z1->setPolarity(0x0);
        break;
        case MiddlewareLayer::PSU_ENUM::Z2:
            if(input > 0) {
                uniquePSU_Z2->setPolarity(0x0); 
                // printf("Flipped polarity, Z2\n");
            }
            else uniquePSU_Z2->setPolarity(0x1);
        break;
    }
    
}

float MiddlewareLayer::getXField(){
    return uniqueT_Meter->SingleAxisReading(Teslameter::AXIS::X);
}

void MiddlewareLayer::writeXField(){
    this->outputFile << row_count++ << "," << this->getXField() << "\n";
}

MiddlewareLayer::~MiddlewareLayer(){
    this->TurnOffSupply();
    this->leftoverTimeFile.close();
    if(!PSU_MODE) this->uniqueLinAct->LinearStop();
    std::cout << "Shutting down\n";
}