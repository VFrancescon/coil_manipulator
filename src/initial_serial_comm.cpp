//!
//! @file 			initial_serial_comm.cpp
//! @author 		Vittorio Francescon <vittorio.francescon@gmail.com> 
//! @created		07/12/2021
//! @last-modified 	09/12/2021
//! @brief			Initial testing file for serial comms.
//! @details
//!					SerialPort class is taken from another repo.

#include <initial_serial_comm.h>

int main(void){

	std::cout << "Programme started successfully. Press Enter to continue";
	std::cin.get();

    SerialPort serialPort("/dev/ttyUSB0", BaudRate::B_9600);
    serialPort.SetTimeout(500); // Block when reading until any data is received
	serialPort.Open();

	std::cout << "Serial Port Class instantiated successfully. Press Enter to continue";
	std::cin.get();

	/*Convert to struct in next implementation*/
	// uint8_t sys_info_command_SYNCH = 0xAA;
	// uint8_t sys_info_command_ADDR = 0x01;
	// uint8_t sys_info_command_CODE = 0x2B;
	// uint8_t sys_info_command_LENGTH = 0x00;
	// uint8_t sys_info_command_CHECK = sys_info_command_ADDR + sys_info_command_CODE + sys_info_command_LENGTH;

	// /*
	// AAFF30002F
	// */

	// printf("Bits to write are: %02X %02X %02X %02X %02X", sys_info_command_SYNCH, sys_info_command_ADDR, sys_info_command_CODE,
	// sys_info_command_LENGTH, sys_info_command_CHECK);

	/*WIP START Struct implementation here*/
	input_message SYS_INFO;
	SYS_INFO.ADDR = 0x01;
	SYS_INFO.CODE = 0x2B;
	SYS_INFO.LENGTH = 0x00;
	SYS_INFO.CHECK = SYS_INFO.Check_Bit_Calc(SYS_INFO);
	SYS_INFO.instruction = SYS_INFO.InstructionAssembler(SYS_INFO);
	//SYS_INFO.instruction.push_back(0x01);

	printf("Check bit %02X\nRest of message ", SYS_INFO.CHECK);
	for(auto i:SYS_INFO.instruction){
		printf("%02X ", i);
	}

	// char input_msg [50];
	// sprintf(input_msg, "%02X%02X%02X%02X%02X", sys_info_command_SYNCH, sys_info_command_ADDR, sys_info_command_CODE,
	// sys_info_command_LENGTH, sys_info_command_CHECK);

	// std::cout << "\nSending command " << input_msg << " over. \nPress Enter to continue";
	// std::cin.get();

    // Write some ASCII data

	serialPort.WriteBinary(SYS_INFO.instruction);
	std::cout << "\nMessage has been sent.\n";

	// // Read some data back (will block until at least 1 byte is received due to the SetTimeout(-1) call above)
	std::vector<uint8_t> readData;
	serialPort.ReadBinary(readData);
	printf("Read data: ");
	for(auto i:readData){
		printf("%02X", i);
	}

	// Close the serial port
	serialPort.Close();
    std::cout << "\nProgramme has finished running\n";
    return 0;
}
