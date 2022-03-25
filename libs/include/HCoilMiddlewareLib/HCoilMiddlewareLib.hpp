#include <DxkdpLib/DxkdpLib.hpp>
#include <LakeshoreF71Lib/LakeshoreF71Lib.hpp>
#include <LinActuatorLib/LinActuatorLib.hpp>
#include <thread>



class MiddlewareLayer{

private:

public:
    /*
    3x PSUs
    1x Teslameter
    1x Linear Actuator
    */
    // std::shared_ptr<Device> device;
    // std::unique_ptr<DXKDP_PSU> PSU_X;
    // std::unique_ptr<DXKDP_PSU> PSU_Y;
    // std::unique_ptr<DXKDP_PSU> PSU_Z;

    // std::unique_ptr<Teslameter> T_Meter;
    // std::unique_ptr<LinearActuator> LinAct; 
    DXKDP_PSU PSU_X;
    DXKDP_PSU PSU_Y;
    DXKDP_PSU PSU_Z;

    Teslameter T_Meter;
    LinearActuator LinAct;

    /*
    Default constructor.
    Assumes the following COM Ports:
    0 -> PSUX
    1 -> PSUY
    2 -> PSUZ
    3 -> Teslameter
    4 -> Introducer
    */
    MiddlewareLayer();

    MiddlewareLayer(std::string PSUX_PORT, std::string PSUY_PORT, std::string PSUZ_PORT, std::string TMETER_PORT, std::string LINACT_PORT );
    ~MiddlewareLayer();

    void TurnOnSupply();
    void TurnOffSupply();
    void initialSetup();
    void set3DVector(std::vector<float> I_X, std::vector<float> I_Y, std::vector<float> I_Z);
    float getXField();

};