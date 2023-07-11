/**
 * @file HCoilMiddlewareLib.hpp
 * @author Vittorio Francescon (vittorio.francescon@gmail.com)
 * @brief Middleware Library. Abstracts usage of other Low-Level libraries as
 * much as possible.
 * @version 1.0
 * @date 10-04-2022
 *
 */

#include <DxkdpLib/DxkdpLib.hpp>
#include <LakeshoreF71Lib/LakeshoreF71Lib.hpp>
#include <LinActuatorLib/LinActuatorLib.hpp>
#include <chrono>
#include <fstream>
#include <thread>

#include "eigen3/Eigen/Core"

/**
 * @class MiddlewareLayer
 * @brief Middleware for Low-Level Control
 *
 * Best efforts have been made to keep this all void-returner so Multithreading
 * is easy.
 *
 * Note: CSV parsing is not included here. Currently it's contained in the
 * driver code, it will probably get a class of its own eventually.
 */
class MiddlewareLayer {
   private:
    bool PositivePolarity;


    std::ofstream outputFile;        //!< Output file object
    std::ofstream leftoverTimeFile;  //!< Leftover time file object

    int row_count =
        1;  //!< keeps track of how many rows have been printed to outputFile.
    int leftoverTime_count =
        1;  //!< keeps track of how many rows have been printed to outputFile
    float frequency = 1;  //!< frequency of the system.

    int period_us =
        1 / frequency *
        1000000;  //!< period in microseconds, derived from the frequency.

    float cal_x = 0.53;  //!< Bx calibration factor. Units are mT/A
    float cal_y = 1.07;  //!< By calibration factor. Units are mT/A
    float cal_z = 0.65;  //!< Bz calibration factor. Units are mT/A

    float xLimit = 50;  //!< current limit in the x supply
    float zLimit = 50;  //!< current limit in the y supply
    float yLimit = 30;  //!< current limit in the z supply

    bool PSU_MODE = false;

    /**
     * @brief Calculates the voltage required to hold given current I (approx)
     * while staying in CV mode.
     *
     * X1-PSU specific, coefficients obtained experimentally
     *
     * @param I current to hold
     * @return float required V that will maintain the system in CV mode.
     */
    float x1Voltage(float I);

    /**
     * @brief Calculates the voltage required to hold given current I (approx)
     * while staying in CV mode.
     *
     * X2-PSU specific, coefficients obtained experimentally
     *
     * @param I current to hold
     * @return float required V that will maintain the system in CV mode.
     */
    float x2Voltage(float I);

    /**
     * @brief Calculates the voltage required to hold given current I (approx)
     * while staying in CV mode.
     *
     * Y1-PSU specific, coefficients obtained experimentally
     *
     * @param I current to hold
     * @return float required V that will maintain the system in CV mode.
     */
    float y1Voltage(float I);

    /**
     * @brief Calculates the voltage required to hold given current I (approx)
     * while staying in CV mode.
     *
     * Y2-PSU specific, coefficients obtained experimentally
     *
     * @param I current to hold
     * @return float required V that will maintain the system in CV mode.
     */
    float y2Voltage(float I);

    /**
     * @brief Calculates the voltage required to hold given current I (approx)
     * while staying in CV mode.
     *
     * Z-PSU specific, coefficients obtained experimentally
     *
     * @param I current to hold
     * @return float required V that will maintain the system in CV mode.
     */
    float z1Voltage(float I);

    /**
     * @brief Calculates the voltage required to hold given current I (approx)
     * while staying in CV mode.
     *
     * Z-PSU specific, coefficients obtained experimentally
     *
     * @param I current to hold
     * @return float required V that will maintain the system in CV mode.
     */
    float z2Voltage(float I);

   public:
    int stepper_count = 0;  //!< keeps track of how many extensions/retractions
                        //!< happened to the stepper motor.
    
    /**
     * @brief Enum class allowing to choose which PSU to operate on.
     *
     */
    enum class PSU_ENUM {
        X1,  //!< First X axis PSU
        X2,  //!< Second X axis PSU
        Y1,  //!< First Y axis PSU
        Y2,  //!< Second Y axis PSU
        Z1,  //!< First Z axis PSU
        Z2   //!< Second Z axis PSU
    };

    std::unique_ptr<DXKDP_PSU> uniquePSU_X1;  //!< uniquePtr for X1 PSU obj.
    std::unique_ptr<DXKDP_PSU> uniquePSU_Y1;  //!< uniquePtr for Y1 PSU obj.
    std::unique_ptr<DXKDP_PSU> uniquePSU_Z1;  //!< uniquePtr for Z1 PSU obj.

    std::unique_ptr<DXKDP_PSU> uniquePSU_X2;  //!< uniquePtr for X2 PSU obj.
    std::unique_ptr<DXKDP_PSU> uniquePSU_Y2;  //!< uniquePtr for Y2 PSU obj.
    std::unique_ptr<DXKDP_PSU> uniquePSU_Z2;  //!< uniquePtr for Z2 PSU obj.

    std::unique_ptr<LinearActuator>
        uniqueLinAct;  //!< uniquePtr to Linear Actuator obj.
    std::unique_ptr<Teslameter>
        uniqueT_Meter;  //!< uniquePtr for Teslameter obj.
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
     * @brief Construct a new Middleware Layer object. Allows to pick the COM
     * Port for each device. Calls TurnOnSupply.
     *
     * @param PSUX_PORT X-axis PSU port.
     * @param PSUY_PORT Y-axis PSU port.
     * @param PSUZ_PORT Z-axis PSU port.
     * @param TMETER_PORT Teslamter port.
     * @param LINACT_PORT Introducer port.
     */
    MiddlewareLayer(std::string PSUX1_PORT, std::string PSUY1_PORT,
                    std::string PSUZ1_PORT, std::string PSUX2_PORT,
                    std::string PSUY2_PORT, std::string PSUZ2_PORT,
                    std::string TMETER_PORT, std::string LINACT_PORT);

    /**
     * @brief Middleware constructor, allows for middleware to use the PSUs only
     * with no additional devices
     *
     * @param PSU_ONLY if true, only functions using the PSUs only will work.
     */
    MiddlewareLayer(bool PSU_ONLY);

    /**
     * @brief Middleware constructor, allows for middleware to use the PSUs only
     * with no additional devices
     *
     * @param OP_MODE 0 for PSU only. 1 for PSU+Introducer. 2 for
     * PSU+Introducer+Teslameter. Any other inputs defaults to 0.
     */
    MiddlewareLayer(int OP_MODE);

    /**
     * @brief Destroy the Middleware Layer object
     *
     * Calls TurnOffSupply. Closes outputFile.
     */
    ~MiddlewareLayer();

    /**
     * @brief Set the Unique pointers for the PSUs
     *
     */
    void setUniquePSUS();

    /**
     * @brief Turns on Supplies.
     *
     */
    void TurnOnSupply();

    /**
     * @brief Sets output V to 60. Opens and sets up outputFile csv. Calls
     * TurnOnSupply.
     *
     */
    void initialSetup();

    /**
     * @brief Checks polarity required for each input. Sets current accordingly.
     *
     * See cal_x , cal_y and cal_z for the respective factors. The voltage is
     * locked at 60V and we set the current only to be faster.
     *
     * Also times execution and displays how much time was left for the given
     * frequency.
     *
     *
     * @param I_X Vector containing all desired X fields
     * @param I_Y Vector containing all desired Y fields
     * @param I_Z Vector containing all desired Z fields
     */
    void set3DVector(std::vector<float> I_X, std::vector<float> I_Y,
                     std::vector<float> I_Z);

    /**
     * @brief Checks polarity required for each input. Sets current accordingly.
     * Stepper Motor extending
     *
     * @param I_X Vector containing all desired X fields
     * @param I_Y Vector containing all desired Y fields
     * @param I_Z Vector containing all desired Z fields
     */
    void set3DVectorIN(std::vector<float> I_X, std::vector<float> I_Y,
                       std::vector<float> I_Z);

    /**
     * @brief Checks polarity required for each input. Sets current accordingly.
     * Stepper Motor retracting
     *
     * @param I_X Vector containing all desired X fields
     * @param I_Y Vector containing all desired Y fields
     * @param I_Z Vector containing all desired Z fields
     */
    void set3DVectorOUT(std::vector<float> I_X, std::vector<float> I_Y,
                        std::vector<float> I_Z);

    /**
     * @brief Sets X, Y and Z fields by altering corresponding currents.
     *
     * @param I_X desired X field
     * @param I_Y desired Y field
     * @param I_Z desired Z field
     */
    void set3DField(float I_X, float I_Y, float I_Z);

    /**
     * @brief Sets X, Y and Z fields by altering corresponding currents.
     *
     * @param I_X desired X field
     * @param I_Y desired Y field
     * @param I_Z desired Z field
     */
    void set3DField(Eigen::Vector3d field);

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
     * @brief Wrapper for the Introducer Functions. Retracts by 1mm.
     *
     * Use alongside the 1D field functions to step the introducer along.
     */
    void retractIntroducer(void);

    /**
     * @brief Wrapper for Introducer Functions. Rectrats by stepCount_ mms
     *
     * @param stepCount_ count of how many extensions to be made.
     */
    void retractIntroducer(int stepCount_);

    /**
     * @brief Checks input and sets PSU polarity accordingly.
     *
     * @param input input current, both +ve and -ve allowed
     * @param psu_ enum covering all PSUs. see PSU_ENUM for details
     */
    void PolarityCheck(float input, MiddlewareLayer::PSU_ENUM psu_);

    /**
     * @brief unwinds the introducer by this->step_count steps.
     * 
     */
    void unwindIntroducer(void);

    /**
     * @brief Reads Field in X direction.
     *
     * Once the tri-axis probe arrives, we will need to expand (or duplicate)
     * this method.
     *
     * @return read field in whatever Units are set in the Teslamter
     * constructor.
     */
    float getXField();

    /**
     * @brief Writes X field to csv file.
     *
     */
    void writeXField();

    /**
     * @brief Set the Frequency parameter in the class
     *
     * @param fHz
     */
    void setFrequency(float fHz = 1);

    std::string filename = "../output.csv";  //!< default file name.
};