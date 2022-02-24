#include <DxkdpLib/DxkdpLib.hpp>
#include <DxkdpLib/instructions.h>

#include <cstdlib>
#include <cmath>
#include <stdint.h>

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

/*Conversion values
AKA 10^-value_read
Multiply ints by this to get the floats of actual values*/
float V_conv, I_conv;

int main(int argc, char *argv[]);

