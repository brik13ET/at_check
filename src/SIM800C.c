#include <SIM800C.h>
#include "SIM800C_port.h"
#include <string.h>


uint8_t strequ(char* s1, char* s2)
{
	uint32_t s1_l = strlen(s1);
	if (s1_l == strlen(s2))
	{
		for (int i = 0; i < s1_l; ++i)
		{
			if (s1[i] != s2[i])
				return 0;
		}
		return 1;
	}
	else
		return 0;
}

uint8_t SIM800C_Init()
{
	uint8_t state = 0;
	for (int i = 0; i < 5 && !state; ++i)
	{
		__SIM800C_USER_POWER_Write(0);
		SIM_delay(1200);
		__SIM800C_USER_POWER_Write(1);
		state = __SIM800C_USER_STATUS_Read();
	}
	if (!state)
		return SIM800C_ERROR;
	char* init[] =
	{
		"AT+CNMI=2,1,0,1,0\r\n\0",
		"AT+CSMP=49,167,0,0\r\n\0",
		"AT+CMGF=1\r\n\0"
	};

	for (int i = 0; i < sizeof(init) / sizeof(init[0]); ++i)
	{
		__SIM800C_USER_UartTX(init[i], strlen(init[i]));
	}

	return SIM800C_OK;
}

uint8_t SIM800C_SendSMS(uint8_t* data, uint16_t length, uint8_t num[12], uint32_t timeout)
{

	/*
	 * 1) AT check ✅ (Init)
	 * 2) проверка правильности загрузки данных
	 * 3) Удалось ли отправить?
	 */
	char* template[] =
	{
		"AT+CMGS=\"\0",
		"\",145\r\n\0",
		"\032\0",
	};
	__SIM800C_USER_UartTX(template[0], strlen(template[0]));
	__SIM800C_USER_UartTX(num, 12);
	__SIM800C_USER_UartTX(template[1], strlen(template[1]));
	__SIM800C_USER_UartTX(data, length);
	__SIM800C_USER_UartTX(template[2], strlen(template[2]));

	return SIM800C_OK;
}
