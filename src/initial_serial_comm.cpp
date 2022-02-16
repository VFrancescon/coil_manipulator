//!
//! @file 			initial_serial_comm.cpp
//! @author 		Vittorio Francescon <vittorio.francescon@gmail.com> 
//! @created		07/12/2021
//! @last-modified 	16/02/2022
//! @brief			Initial testing file for serial comms.
//! @details
//!					SerialPort class is taken from another repo.

#include <initial_serial_comm.h>
using namespace mn::CppLinuxSerial;
int main(void){

	std::cout << "Programme started successfully. Press Enter to continue";
	std::cin.get();

    SerialPort serialPort("/dev/ttyUSB0", BaudRate::B_9600, NumDataBits::EIGHT, Parity::NONE, NumStopBits::ONE);
    serialPort.SetTimeout(5000); // Block when reading until any data is received
	serialPort.Open();
	std::cout << "Serial Port Class instantiated successfully. Press Enter to continue";
	std::cin.get();

	
	input_message SYS_INFO;
	SYS_INFO.ADDR = 0x01;
	SYS_INFO.CODE = 0x2B;
	SYS_INFO.LENGTH = 0x00;
	//SYS_INFO.CHECK = SYS_INFO.Check_Bit_Calc(SYS_INFO);
	SYS_INFO.instruction = SYS_INFO.InstructionAssembler(SYS_INFO);
	printf("Full command: \n");
	for(auto i:SYS_INFO.instruction) printf("%02X ", i);
	
	// uint8_t a = 0x00;
	// SYS_INFO.instruction.push_back(a);
	serialPort.WriteBinary(SYS_INFO.instruction);
	// SYS_INFO.instruction.push_back(a);
	// 	for(auto i:SYS_INFO.instruction){
	// 		printf("%02X ", i);
	// }
	// usleep(1);

	// for(int i = 0; i < 255; i++){
	// 	std::cout << "\n";
	// 	a++;
	// 	SYS_INFO.instruction.pop_back();
	// 	SYS_INFO.instruction.push_back(a);
	// 	for(auto i:SYS_INFO.instruction){
	// 		printf("%02X ", i);
	// 	}
	// 	serialPort.WriteBinary(SYS_INFO.instruction);
	// 	sleep(1);
	// }

	// printf("Check bit %02X\nRest of message ", SYS_INFO.CHECK);
	// for(auto i:SYS_INFO.instruction){
	// 	printf("%02X ", i);
	// }

	// serialPort.WriteBinary(SYS_INFO.instruction);
	// std::cout << "\nMessage has been sent.\n";

	// // Read some data back (will block until at least 1 byte is received due to the SetTimeout(-1) call above)
	std::vector<uint8_t> readData;
	serialPort.ReadBinary(readData);
	//for(int i = 0; i < 10; i++) serialPort.ReadBinary(readData);
	// std::string readString;
	// serialPort.Read(readString);
	// std::cout << readString << "\n";

	std::cout << "\nSize of readData: " << readData.size();
	printf("\nRead data: " );

	for(auto i:readData){
		printf("%02X ", i);
	}

	// Close the serial port
	serialPort.Close();
    std::cout << "\nProgramme has finished running\n";
    return 0;
}
