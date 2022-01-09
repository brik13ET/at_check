#include <main.h>

int main(int argc, char* argv[])
{
	SIM800C_Init();
	uint8_t data[17] = "Hello from STM32!";

  	SIM800C_SendSMS(&data[0], 17, (uint8_t*)"89397186225", 1000);
	
	return 0;
}