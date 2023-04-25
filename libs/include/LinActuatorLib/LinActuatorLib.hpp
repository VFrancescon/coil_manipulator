/**
 * @file LinActuatorLib.hpp
 * @author Vittorio Francescon <vittorio.francescon@gmail.com>""
 * @brief Library for usage of the Introducer.
 * @version 0.9
 * @date 2022-04-02
 *
 *
 */

#include <string.h>

#include <CppLinuxSerial/SerialPort.hpp>

using namespace mn::CppLinuxSerial;

/**
 * @class LinearActuator
 * @brief Low level functions to control Linear Actuators through RS232
 *
 */
class LinearActuator {
   private:
    /**
     * @brief Set timeout and open COM Port
     *
     */
    void ActuatorSetup();

    std::string Ext1mm = "2\0";  //!< Value to extend by 1mm .
    std::string Ctr1mm = "1\0";  //!< Value to contract by 1mm.
    std::string Shtdwn = "3\0";  //!< Value to shut down the system.

   public:
    SerialPort serialPort;  //!< serial Port object for serial communication

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