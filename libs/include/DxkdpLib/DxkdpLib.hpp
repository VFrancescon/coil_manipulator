/**
 * @file DxkdpLib.hpp
 * @author Vittorio Francescon <vittorio.francescon@gmail.com>
 * @brief Contains library for PSU Usage. Instantiates input_message and
 * output_message as required.
 * @version 1.0
 * @date 2022-04-02
 *
 */

#include <errno.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <system_error>

#include "CppLinuxSerial/SerialPort.hpp"
#include "instructions.hpp"

/**
 * @class DXKDP_PSU
 * @brief Class containing low-level functions to control the PSUs
 *
 * Uses input_message and output_message structs to construct messages based on
 * function parameters. Uses CppLinuxSerial to communicate with the PSU through
 * RS232 Serial.
 *
 * Note: Exceptions are thrown using the THROW_EXCEPT macro, which is in the
 * CppLinuxSerial Repo.
 */

using namespace mn::CppLinuxSerial;

class DXKDP_PSU {
   private:
    /**
     * @brief Sets up Serial Port for usage. Call before any write/read
     * operation.
     *
     */
    void DXKDP_Setup();

    /**
     * @brief Constructs the input_message to set the Power out state.
     *
     * @param PO_STATE 1 == On, 0 == Off
     * @param addr PSU address to write to
     * @return std::vector<uint8_t> vector containing the relevant instruction
     */
    std::vector<uint8_t> Encoder20(uint8_t PO_STATE = 0x00,
                                   uint8_t addr = 0x01);

    /**
     * @brief Constructs the input_message to set the Voltage.
     *
     * Voltage can be any float to 2dp. Defaults to 0V for safety
     *
     * @param Voltage float to 2dp. Max 60V
     * @param addr PSU address
     * @return std::vector<uint8_t> vector containing the relevant instruction
     */
    std::vector<uint8_t> Encoder21(float Voltage = 0, uint8_t addr = 0x01);

    /**
     * @brief Constructs the input_message to set the Current.
     *
     * @param Current can be any float to 2dp
     * @param addr PSU address
     * @return std::vector<uint8_t> vector containing the relevant instruction
     */
    std::vector<uint8_t> Encoder22(float Current = 0, uint8_t addr = 0x01);

    std::vector<uint8_t> Encoder22Gen2(float Current = 0, uint8_t addr = 0x01);

    /*
    Constructs the input msg to set the Current.
    Current can be any float to 2dp
    defaults to 0 for safety
    addr is the address of the PSU
    Defaults to 1
    */

    /**
     * @brief Constructs the input_message to set the Voltage and Current.
     *
     * @param Voltage 2dp float
     * @param Current 2dp float
     * @param addr PSU address
     * @return std::vector<uint8_t> vector containing the relevant instruction
     */
    std::vector<uint8_t> Encoder23(float Voltage = 0, float Current = 0,
                                   uint8_t addr = 0x01);

    std::vector<uint8_t> Encoder23Gen2(float Voltage = 0, float Current = 0,
                                       uint8_t addr = 0x01);

    /*
    Constructs the input_message to set the Polarity.
    Set Voltage or Current to 1 for positive, 0 for negative
    Defaults to Positive
    */

    /**
     * @brief Constructs the input_message to set the Polarity.
     *
     * NOTE: This method assumes that you can control Voltage and Current
     * polarity separately. That is not the case apparently and the setPolarity
     * method takes care of that.
     *
     * @param VoltageP Voltage Polarity
     * @param CurrentP Current Polarity
     * @param addr PSU Address
     * @return std::vector<uint8_t> vector containing the relevant instruction
     */
    std::vector<uint8_t> Encoder24(uint8_t VoltageP = 0x01,
                                   uint8_t CurrentP = 0x01,
                                   uint8_t addr = 0x01);
    /**
     * @brief Constructs the input_message to set the Polarity.
     *
     * NOTE: This method assumes that you can control Voltage and Current
     * polarity separately. That is not the case apparently and the setPolarity
     * method takes care of that.
     *
     * @param VoltageP Voltage Polarity
     * @param CurrentP Current Polarity
     * @param addr PSU Address
     * @return std::vector<uint8_t> vector containing the relevant instruction
     */
    std::vector<uint8_t> Encoder24Gen2(uint8_t VoltageP = 0x01,
                                       uint8_t CurrentP = 0x01,
                                       uint8_t addr = 0x01);

    /**
     * @brief Constructs the input_message to view actual VI values.
     *
     * @param addr PSU Address
     * @return std::vector<uint8_t> vector containing the relevant instruction
     */
    std::vector<uint8_t> Encoder26(uint8_t addr = 0x01);

    /**
     * @brief Constructs the input_message to view set VI values.
     *
     * @param addr PSU Address
     * @return std::vector<uint8_t> vector containing the relevant instruction
     */
    std::vector<uint8_t> Encoder28(uint8_t addr = 0x01);

    /*
    Takes Actual current V & I
    Plus says if we are in constant current or voltage operation
    */

    /**
     * @brief Decodes info from Code 26 Input
     *
     * @param msgOut reference to the output_message struct
     */
    void Decoder26(output_message &msgOut);

    /**
     * @brief Takes Power Out State, Voltage and Current
     *
     * @param msgOut reference to the output_message struct
     */
    void Decoder28(output_message &msgOut);

    /*
    Hex to Int, no conversion
    MSB = MSB read
    LSB = LSB read
    */

    /**
     * @brief Converts MSB and LSB bytes into an int
     *
     * @param MSB read MSB
     * @param LSB read LSB
     * @return int combined values into int
     */
    int HexToDec(uint8_t MSB, uint8_t LSB);

    /**
     * @brief Converts MSB and LSB bytes into a float
     *
     * @param MSB read MSB
     * @param LSB read LSB
     * @param Conv Conversion factor (10^-value_read)
     * @return float converted value, 2dp
     */
    float HexToValue(uint8_t MSB, uint8_t LSB, float Conv);

    /**
     * @brief float to 16bit Hex, writes Low and High bit in the input_msg
     * struct direclty.
     *
     * @param value value to convert
     * @param Conv conversion factor
     * @param msgIn reference to input_message
     * @param entry 1 writes to CONT1, CONT2. 2 writes to CONT3, CONT4
     */
    void DecToHex(float value, float Conv, input_message &msgIn, int entry = 1);

    void DecToHexSigned(float value, float Conv, input_message &msgIn,
                        int entry = 2);

   public:
    /*default constructor, here for debugging mainly
    will instantiate a power supply at ttyUSB0, addr 1*/

    /**
     * @brief Default Constructor. Instantiates supply at /dev/ttyUSB0,
     * addr=0x01
     *
     */
    DXKDP_PSU();

    /**
     * @brief Overloaded Constructor, allows to choose COM PORT
     *
     * @param COM_PORT string containing COM Port Address
     */
    DXKDP_PSU(std::string COM_PORT);

    /**
     * @brief Overloaded Constructor, allows to choose COM PORT and Conversion
     * Factors
     *
     * @param COM_PORT string containing COM Port Address
     * @param V_conv Voltage minimum step
     * @param I_conv Current minimum step
     */
    DXKDP_PSU(std::string COM_PORT, float V_conv, float I_conv);

    /**
     * @brief Class Destructor. Closes serial port.
     *
     */
    ~DXKDP_PSU();
    SerialPort serialPort;  //!< serial Port object. See CppLinuxSerial.

    float Vconv = 0.01;  //!< Minimum voltage increment
    float Iconv = 0.01;  //!< Minimum current increment

    /**
     * @brief Writes instruction to serialPort.
     *
     * Accesses msgIn.instruction to do the writing. Set it through the Encoder
     * functions.
     *
     * @param msgIn instance of input_message struct.
     */
    void PsuWrite(input_message msgIn);

    /**
     * @brief Reads data from serialPort.
     *
     * Writes the read data onto the output1 member of the output_message
     * struct.
     *
     * @param msgOut reference to the output_message struct.
     */
    void PsuRead(output_message &msgOut);

    /**
     * @brief Overloaded version of PSUWrite. Broken, do not use.
     *
     * @param input vector containing the instruction.
     */
    void PsuWrite(std::vector<uint8_t> input);

    /**
     * @brief Set the Polarity of the PSU.
     *
     * Mixed polarities are unachievable as of now, so this function does not
     * allow them.
     *
     * @param polarity 0x00 for Positive, 0x01 for Negative.
     * @param addr PSU address
     */
    void setPolarity(uint8_t polarity, uint8_t addr = 0x01);

    /**
     * @brief Set the Polarity of the PSU for Gen2 PSUs only.
     *
     * Requires testing. According to the manual, commands go as follows:
     *
     * 0x00: closed
     * 0x01: positive
     * 0x02: negative
     * 0x03: LDI (no idea what it meas)
     *
     * @param polarity Input polarity
     * @param addr PSU address
     */
    void setPolarityGen2(uint8_t polarity, uint8_t addr = 0x01);

    /**
     * @brief Sets PO State of the PSU.
     *
     * @param po_state 0x01 == ON, 0x00 == OFF
     */
    void PoCtrl(uint8_t po_state);

    /**
     * @brief Writes Voltage to Power Supply
     *
     * @param targetV target Voltage float to 2dp
     * @param addr PSU Address
     */
    void WriteVoltage(float targetV, uint8_t addr = 0x01);

    /**
     * @brief Writes Current to Power Supply
     *
     * @param targetI target Current float to 2dp
     * @param addr PSU Address
     */
    void WriteCurrent(float targetI, uint8_t addr = 0x01);

    void WriteCurrentGen2(float targetI, uint8_t addr = 0x01);

    /**
     * @brief Writes VI to Power Supply
     *
     * @param targetV target Voltage float to 2dp
     * @param targetI target Current float to 2dp
     * @param addr PSU Address
     */
    void WriteVI(float targetV, float targetI, uint8_t addr = 0x01);

    void WriteVIGen2(float targetV, float targetI, uint8_t addr = 0x01);

	uint8_t debugWriteVI(float targetV, float targetI, uint8_t addr = 0x01);

    /**
     * @brief reads the VI currently output by the PSU. Writes the minto msg
     *
     * @param msg reference to an output_message struct instance
     * @param addr psu address. defautls to 0x01
     */
    void ReadVI(uint8_t addr = 0x01);

    bool POstate;       //!< Current PO state.
    float ReadVoltage;  //!< Read Voltages and Currents. Only assigned
                        //!< internally. Needs implementing
    float ReadCurrent;  //!< Read Voltages and Currents. Only assigned
                        //!< internally. Needs implementing
    std::string PsuID;  //!< UniqueID for the PSU. Will correspond to COMPORT at
                        //!< runtime.
};