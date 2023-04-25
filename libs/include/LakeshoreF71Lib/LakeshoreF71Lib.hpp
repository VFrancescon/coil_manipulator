/**
 * @file LakeshoreF71Lib.hpp
 * @author Vittorio Francescon <vittorio.francescon@gmail.com>
 * @brief Contains library for communication with the Lakeshore F71 Teslameter
 * @version 1.0
 * @date 2022-04-02
 *
 */

#include <string.h>

#include <CppLinuxSerial/SerialPort.hpp>
using namespace mn::CppLinuxSerial;

/**
 * @class Teslameter
 * @brief Uses SCPI and RS232 to communicate with the Teslameter
 *
 * We use SCPI to talk to the Teslameter (Lakeshore F71).
 * as SCPI commands can be chained in a line, we set each command as a string
 * And the member functions combine them through string concatenation
 * given a = "hello" and b = " world", c = a + b = "hello world"
 */
class Teslameter {
   private:
    /**
     * @brief Sets up timeout, opens COM port and sets up Teslameter.
     *
     * Sets sensing range to Auto and units to Tesla. Call this before
     * attempting any reading.
     */
    void TeslameterSetup();

    std::string autoRange =
        "SENS:FIEL:RANG:AUTO 1";  //!< Command to set the range to automatic

    std::string fieldTesla =
        "UNIT:FIEL TESL";  //!< Command to set the field to tesla

    std::string fetchField =
        "FETC:FIEL:DC? ";  //!< Command to fetch the field in a direction. MUST
                           //!< ADD X/Y/Z/ALL to complete command

    /**
     * @brief Allows command to send an ack response
     *
     * Format: "response;1;"
     * Where "1;" is the ACK bit
     */
    std::string confirmed = "*OPC?";

    std::string lineFeed = "\n\0";  //!< Need to attach a line feed to each
                                    //!< command to complete them

   public:
    SerialPort serialPort;  //!< serialPort object for communication

    /**
     * @brief Default constructor for the class.
     *
     * Defaults to COM Port ttyUSB0
     */
    Teslameter();
    /*
    Overloaded constructor. Lets us specify the COM port */

    /**
     * @brief Overloaded constructor. Lets us specify the COM port
     *
     * @param COM String containing COM Port
     */
    Teslameter(std::string COM);

    /**
     * @brief Destroy the Teslameter object. Closes Serial Port.
     *
     */
    ~Teslameter();

    /*Enum class to differentiate axis
    More of an exercise for me to get familiar with the practice*/

    /**
     * @enum AXIS
     * @brief Enum class to decide which Teslameter Axis to read from
     *
     */
    enum class AXIS {
        X,  //!< X axis
        Y,  //!< y axis
        Z   //!< Z axis
    };

    /**/

    /**
     * @brief Returns field reading in axis Axis. Look at enum class AXIS for
     * details
     *
     * @param Axis AXIS enum member
     * @return float returns reading to 6dp in specified direction
     */
    float SingleAxisReading(Teslameter::AXIS Axis);
    /*Returns field reading in all directions in a vector*/

    /**
     * @brief Returns field reading in all directions in a vector
     *
     * @return std::vector<float> Vector containing X, Y and Z wise readings, in
     * that order
     */
    std::vector<float> AllAxisReading();
};