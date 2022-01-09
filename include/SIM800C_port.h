#ifndef SIM800C_SIM800C_PORT_H_
#define SIM800C_SIM800C_PORT_H_

#include <stdint.h>
#include <time.h>

void __SIM800C_USER_UartTX
(
		uint8_t* data,
		uint8_t lth
);



uint8_t	__SIM800C_USER_UartRX
(
		uint8_t* data,
		uint16_t lth,
		uint32_t timeout
);


uint8_t __SIM800C_USER_STATUS_Read();
void __SIM800C_USER_POWER_Write(uint8_t state);

void SIM_delay(uint16_t);
#endif /* SIM800C_SIM800C_PORT_H_ */
