#include <main.h>

int main(int argc, char* argv[])
{
	SIM800C_Init();
	uint8_t data[] = "Hello from STM32!\0";

  	SIM800C_SendSMS(&data[0], strlen(data), (uint8_t*)"+79397186225", 1000);
	
	return 0;
}