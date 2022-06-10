/**
 * @file HCoilMiddlewareLib.hpp
 * @author Vittorio Francescon (vittorio.francescon@gmail.com)
 * @brief Middleware Library. Abstracts usage of other Low-Level libraries as much as possible.
 * @version 1.0
 * @date 10-04-2022
 * 
 */

#include <DxkdpLib/DxkdpLib.hpp>
#include <LakeshoreF71Lib/LakeshoreF71Lib.hpp>
#include <LinActuatorLib/LinActuatorLib.hpp>
#include <thread>
#include <fstream>
#include <chrono>
/**
 * @class MiddlewareLayer
 * @brief Middleware for Low-Level Control
 * 
 * Best efforts have been made to keep this all void-returner so Multithreading is easy.
 * 
 * Note: CSV parsing is not included here. Currently it's contained in the driver code, it will probably get a class of its own eventually.
 * 
 * @todo Fix calibration factor. I believe the data being read is in mT, but we treat it as T. 
 */
class MiddlewareLayer{

private:


    int stepper_count = 0; //!< keeps track of how many extensions/retractions happened to the stepper motor.
    
    std::ofstream outputFile; //!< Output file object
    std::ofstream leftoverTimeFile; //!< Leftover time file object
    
    int row_count = 1; //!< keeps track of how many rows have been printed to outputFile.
    int leftoverTime_count = 1; //!< keeps track of how many rows have been printed to outputFile
    float frequency = 1.75; //!< frequency of the system.

    int period_us = 1/frequency*1000000; //!< period in microseconds, derived from the frequency.
    
    float cal_x = 0.54; //!< Bx calibration factor
    float cal_y = 1.135; //!< By calibration factor
    float cal_z = 0.65; //!< Bz calibration factor

public:

    /**
     * @brief Enum class allowing to choose which PSU to operate on.
     * 
     */
    enum class PSU_ENUM{
        X1, //!< First X axis PSU
        X2, //!< Second X axis PSU
        Y1, //!< First Y axis PSU
        Y2, //!< Second Y axis PSU 
        Z1, //!< First Z axis PSU
        Z2  //!< Second Z axis PSU
        };
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
    // DXKDP_PSU PSU_X1; //!< X1-axis instance of DXKDP_PSU
    // DXKDP_PSU PSU_Y1; //!< Y1-axis instance of DXKDP_PSU
    // DXKDP_PSU PSU_Z1; //!< Z1-axis instance of DXKDP_PSU
    // DXKDP_PSU PSU_X2; //!< X2-axis instance of DXKDP_PSU
    // DXKDP_PSU PSU_Y2; //!< Y2-axis instance of DXKDP_PSU
    // DXKDP_PSU PSU_Z2; //!< Z2-axis instance of DXKDP_PSU

    std::unique_ptr<DXKDP_PSU> uniquePSU_X1; //!< uniquePtr for X1 PSU obj.  
    std::unique_ptr<DXKDP_PSU> uniquePSU_Y1; //!< uniquePtr for Y1 PSU obj.  
    std::unique_ptr<DXKDP_PSU> uniquePSU_Z1; //!< uniquePtr for Z1 PSU obj.  

    std::unique_ptr<DXKDP_PSU> uniquePSU_X2; //!< uniquePtr for X2 PSU obj.  
    std::unique_ptr<DXKDP_PSU> uniquePSU_Y2; //!< uniquePtr for Y2 PSU obj.  
    std::unique_ptr<DXKDP_PSU> uniquePSU_Z2; //!< uniquePtr for Z2 PSU obj.  

    // Teslameter T_Meter; //!< Instance of Teslameter
    // LinearActuator LinAct; //!< Instance of LinearActuator

    std::unique_ptr<LinearActuator> uniqueLinAct; //!< uniquePtr to Linear Actuator obj.  
    std::unique_ptr<Teslameter>uniqueT_Meter; //!< uniquePtr for Teslameter obj.  
    /**
    @brief Default constructor. Calls TurnOnSupply.
    
    Assumes the following COM Ports:
    0 -> PSUX
    1 -> PSUY
    2 -> PSUZ
    3 -> Teslameter
    4 -> Introducer
    */
    MiddlewareLayer();

    /**
     * @brief Construct a new Middleware Layer object. Allows to pick the COM Port for each device. Calls TurnOnSupply.
     * 
     * @param PSUX_PORT X-axis PSU port.
     * @param PSUY_PORT Y-axis PSU port.
     * @param PSUZ_PORT Z-axis PSU port.
     * @param TMETER_PORT Teslamter port.
     * @param LINACT_PORT Introducer port.
     */
    MiddlewareLayer(std::string PSUX1_PORT, std::string PSUY1_PORT, std::string PSUZ1_PORT, 
        std::string PSUX2_PORT, std::string PSUY2_PORT, std::string PSUZ2_PORT,
        std::string TMETER_PORT, std::string LINACT_PORT 
    );
    
    /**
     * @brief Destroy the Middleware Layer object
     * 
     * Calls TurnOffSupply. Closes outputFile.
     */
    ~MiddlewareLayer();

    /**
     * @brief Turns on Supplies.
     * 
     */
    void TurnOnSupply();

    /**
     * @brief Sets output V to 0, Turns off Supplies. 
     * 
     * Notes: Serial objects all destroy themselves from their own constructors, so it should all be taken care of implicitly.
     * 
     * Unwinding of the Linear Actuator should go here, if the device worked.
     * 
     */
    void TurnOffSupply();
    
    /**
     * @brief Sets output V to 60. Opens and sets up outputFile csv. Calls TurnOnSupply.
     * 
     */
    void initialSetup();

    /**
     * @brief Checks polarity required for each input. Sets current accordingly. 
     * 
     * See cal_x , cal_y and cal_z for the respective factors. The voltage is locked at 60V and we set the current only to be faster.
     * 
     * Also times execution and displays how much time was left for the given frequency.
     * 
     * 
     * @param I_X Vector containing all desired X fields
     * @param I_Y Vector containing all desired Y fields
     * @param I_Z Vector containing all desired Z fields
     */
    void set3DVector(std::vector<float> I_X, std::vector<float> I_Y, std::vector<float> I_Z);
    
    /**
     * @brief Sets output current to X1
     * 
     * 
     * 
     * @note the set<X/Y/Z><1/2>Vector functions step through a vector of floats, writing the currents accordingly.\n 
     * The X variants also write the field read to a CSV file.\n 
     * Introducer stepping should be handled separately through the StepIntroducer functions. 
     * 
     * @param current_ vector of floats containing all desired X fields.
     * @param psu_ PSU_ENUM containing the chosen power supply.
     */
    void setX1Vector(std::vector<float> current_);

    /**
     * @brief Sets output current to Y1 PSU
     * 
     * @param current_ vector of floats containing all desired X fields.
     * @param psu_ PSU_ENUM containing the chosen power supply.
     */
    void setY1Vector(std::vector<float> current_);


    /**
     * @brief Sets output current to Z1 PSU
     * 
     * @param current_ vector of floats containing all desired X fields.
     * @param psu_ PSU_ENUM containing the chosen power supply.
     */
    void setZ1Vector(std::vector<float> current_);

        /**
     * @brief Sets output current to X2 PSU
     * 
     * @param current_ vector of floats containing all desired X fields.
     * @param psu_ PSU_ENUM containing the chosen power supply.
     */
    void setX2Vector(std::vector<float> current_);

    /**
     * @brief Sets output current to Y2 PSU
     * 
     * @param current_ vector of floats containing all desired X fields.
     * @param psu_ PSU_ENUM containing the chosen power supply.
     */
    void setY2Vector(std::vector<float> current_);


    /**
     * @brief Sets output current to Z2 PSU
     * 
     * @param current_ vector of floats containing all desired X fields.
     * @param psu_ PSU_ENUM containing the chosen power supply.
     */
    void setZ2Vector(std::vector<float> current_);

    /**
     * @brief Wrapper for the Introducer Functions. Extends by 1mm.
     * 
     * Use alongside the 1D field functions to step the introducer along.
     */
    void stepIntroducer(void);
    

    /**
     * @brief Wrapper for Introducer Functions. Extends by stepCount_ mms
     * 
     * @param stepCount_ count of how many extensions to be made.
     */
    void stepIntroducer(int stepCount_);

    /**
     * @brief Checks the Polarity required for a given input and sets it as required.
     * 
     * Eventually we will be able to flip the polarity only when required, but that requires some info off the manufacturer we do not have yet.
     * 
     * @param input input value, read from wherever.
     * @param PSU_CHOSER determins which PSU to work on. 0->X, 1->Y, 2->Z
     */
    void PolarityCheck(float input, MiddlewareLayer::PSU_ENUM psu_);

    /**
     * @brief Reads Field in X direction.
     * 
     * Once the tri-axis probe arrives, we will need to expand (or duplicate) this method.
     * 
     * @return read field in whatever Units are set in the Teslamter constructor.
     */
    float getXField();

    /**
     * @brief Writes X field to csv file.
     * 
     */
    void writeXField();

    std::string filename = "../output.csv"; //!< default file name.
};