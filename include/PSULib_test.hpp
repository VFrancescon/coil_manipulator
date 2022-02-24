#include <DxkdpLib/DxkdpLib.hpp>
#include <DxkdpLib/instructions.h>

#include <cstdlib>
#include <cmath>
#include <stdint.h>

/*
Constructs the input msg to set the Power out state.
PO VALUES
1 = PO is on
0 = PO is off
defaults to off for safety
addr is the address of the PSU
Defaults to 1
*/
std::vector<uint8_t> Encoder20(uint8_t PO_STATE = 0x00, uint8_t addr = 0x01);

/*
Constructs the input msg to set the Voltage.
Voltage
Any float to 2dp
defaults to 0 for safety
addr is the address of the PSU
Defaults to 1
*/
std::vector<uint8_t> Encoder21(float Voltage=0, uint8_t addr=0x01);

/*
Takes Actual current V & I
Plus says if we are in constant current or voltage operation
*/
void Decoder26(output_message &msgOut);

/*
Takes Power Out State, Voltage and Current 
*/
void Decoder28(output_message &msgOut);

/*
Takes Voltage, Current and Step Size from the PSUs.
A bit unsure what the voltage actually represents as of now.
*/
void Decoder2B(output_message &msgOut);

/*Conversion functions*/

/*
Hex to Int, no conversion
MSB = MSB read
LSB = LSB read
*/
int HexToDec(uint8_t MSB, uint8_t LSB);

/*Hex to Float, with conversion factor 
MSB = MSB read
LSB = LSB read
Conv = Conversion factor (10^-value_read)
*/
float HexToValue(uint8_t MSB, uint8_t LSB, float Conv);

/*Float to 16bit Hex, writes Low and High bit in the input_msg struct direclty.
value = value to convert
Conv = conversion factor
entry = 1 writes to CONT1, CONT2
entry = 2 writes to CONT3, CONT4 */
void DecToHex(float value, float Conv, input_message &msgIn, int entry = 1);


//Variables here, will becoem public members of the class
/*
Conversion values
AKA 10^-value_read
Multiply ints by this to get the floats of actual values
*/
float V_conv, I_conv;

/*
Voltage of the PSU, to 2dp
*/
float ReadVoltage, DesiredVoltage;


/*
Current of the PSU, to 2dp
*/
float ReadCurrent, DesiredCurrent;

/*
Power output state
1 = Enabled
0 = Disabled
*/
bool POState;

/*
Power output state
1 = Constant voltage
0 = Constant Current
*/
bool CCState;

int main(int argc, char *argv[]);

