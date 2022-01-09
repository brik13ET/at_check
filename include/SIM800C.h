#ifndef SIM800C_SIM800C_H_
#define SIM800C_SIM800C_H_

#include <stdint.h>


extern struct SIM800* current;

uint8_t SIM800C_Init();
uint8_t SIM800C_SendSMS
(
		uint8_t* data,
		uint16_t length,
		uint8_t num[11],
		uint32_t timeout
);


#define SIM800C_OK 		0
#define SIM800C_ERROR 	1


#endif /* SIM800C_SIM800C_H_ */
