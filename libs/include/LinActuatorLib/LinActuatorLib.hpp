/**
 * @file LinActuatorLib.hpp
 * @author Vittorio Francescon <vittorio.francescon@gmail.com>""
 * @brief Library for usage of the Introducer.
 * @version 0.9
 * @date 2022-04-02
 * 
 * 
 */

#include <CppLinuxSerial/SerialPort.hpp>
#include <string.h>


using namespace mn::CppLinuxSerial;


/**
 * @class LinearActuator
 * @brief Low level functions to control Linear Actuators through RS232
 * 
 */
class LinearActuator{

private:
    /**
     * @brief Set timeout and open COM Port
     * 
     */
    void ActuatorSetup();

   
    uint8_t Ext1mm = 49; //!< Value to extend by 1mm .
    uint8_t Ctr1mm = 50; //!< Value to contract by 1mm.
    uint8_t Shtdwn = 51; //!< Value to shut down the system.


    /**
     * @brief 
     * Because of how CppLinuxSerial is built, we need a vector for each instruction.
     * The introducer instructions are simple enough we might as well build them once
     * and let them be.
     */
    std::vector<uint8_t> Ext1mm_vect = {Ext1mm};

    /**
     * @brief 
     * Look at Ext1mm_vect.
     */
    std::vector<uint8_t> Ctr1mm_vect = {Ctr1mm};
    
    /**
     * @brief 
     * Look at Ext1mm_vect.
     */
    std::vector<uint8_t> Shtdwn_vect = {Shtdwn};

public:
    SerialPort serialPort; //!< serial Port object for serial communication

    /**
     * @brief Default Constructor, takes standard COM Port ttyUSB0, 1 DOF.
     * 
     */
    LinearActuator();

    /**
     * @brief COM Port Overload Constructor. Lets you choose port, 1 DOF.
     * 
     * @param COM Desired COM Port
     */
    LinearActuator(std::string COM);

    /*Destructor*/
    /**
     * @brief Destroy the Linear Actuator object.
     * 
     */
    ~LinearActuator();
    
    /**
     * @brief 1D extension, 1mm.
     * 
     */
    void LinearExtend();

    /**
     * @brief 1D contraction, 1mm.
     * 
     */
    void LinearContract();
    
    /**
     * @brief Object shutdown.
     * 
     * Call this in any relevant destructor.
     */
    void LinearStop();

};