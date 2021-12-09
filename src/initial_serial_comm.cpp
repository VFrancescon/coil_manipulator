//!
//! @file 			initial_serial_comm.cpp
//! @author 		Vittorio Francescon <vittorio.francescon@gmail.com> 
//! @created		07/12/2021
//! @last-modified 	08/12/2021
//! @brief			Initial testing file for serial comms.
//! @details
//!					SerialPort class is taken from another repo.

#include <initial_serial_comm.h>

int main(void){

	std::cout << "Programme started successfully. Press Enter to continue\n";
	std::cin.get();

    SerialPort serialPort("/dev/ttyUSB1", BaudRate::B_9600);
    serialPort.SetTimeout(-1); // Block when reading until any data is received
	serialPort.Open();

	std::cout << "Serial Port Class instantiated successfully. Press Enter to continue\n";
	std::cin.get();

	/*Convert to struct in next implementation*/
	uint8_t sys_info_command_SYNCH = 0xAA;
	uint8_t sys_info_command_ADDR = 0xFF;
	uint8_t sys_info_command_CODE = 0x30;
	uint8_t sys_info_command_LENGTH = 0x00;
	uint8_t sys_info_command_CHECK = sys_info_command_ADDR + sys_info_command_CODE + sys_info_command_LENGTH;

	/*
	AAFF30002F
	*/

	// printf("Bits to write are:%02X %02X %02X %02X %02X", sys_info_command_SYNCH, sys_info_command_ADDR, sys_info_command_CODE,
	// sys_info_command_LENGTH, sys_info_command_CHECK);


	char input_msg [50];
	sprintf(input_msg, "%02X%02X%02X%02X%02X", sys_info_command_SYNCH, sys_info_command_ADDR, sys_info_command_CODE,
	sys_info_command_LENGTH, sys_info_command_CHECK);

	std::cout << "Sending command " << input_msg << " over. Press Enter to continue\n";
	std::cin.get();

    // Write some ASCII data
	serialPort.Write(input_msg);
	std::cout << "Message has been sent.\n";

	// Read some data back (will block until at least 1 byte is received due to the SetTimeout(-1) call above)
	std::string readData;
	serialPort.Read(readData);
	std::cout << "Read data is: " << readData << "\n";

	// Close the serial port
	serialPort.Close();
    std::cout << "Programme has finished running\n";
    return 0;
}
