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
		"AT+CSMP=49,167,0,0\r\n\0"
	};

	for (int i = 0; i < sizeof(init) / sizeof(init[0]); ++i)
	{
		__SIM800C_USER_UartTX(init[i], strlen(init[i]));
	}

	return SIM800C_OK;
}

uint8_t SIM800C_SendSMS(uint8_t* data, uint16_t length, uint8_t num[11], uint32_t timeout)
{

	/*
	 * 1) AT check ✅ (Init)
	 * 2) проверка правильности загрузки данных
	 * 3) Удалось ли отправить?
	 */

	char buf[255];
	char buf2[7];
	char* template[] =
	{
			"AT+CMGW=\"\0",
			"\"\r\n\0",
			"\26\0",
			"AT+CMSS=\0"
	};
	uint16_t i = 0;
	strcpy(&buf[0], template[0]);
	i = strlen(template[0]);
	strcpy((char*)&buf[i], (char*)&num[0]);
	i += 11;
	strcpy(&buf[i], template[1]);
	i += strlen(template[1]);
	length = length > 255 - 1? 255 - i - 1: length;
	memcpy(&buf[i], data, length);
	i += length;
	strcpy(&buf[i], template[2]);
	__SIM800C_USER_UartTX((uint8_t*)buf, 255);
	__SIM800C_USER_UartRX((uint8_t*)buf, 255, 200);
	uint8_t cb = 0;
	uint8_t found_ok = 0;
	while ( cb < 255 && buf[cb] != 0 && !found_ok)
	{
		found_ok = cb < 254 && strequ(&buf[cb], "OK");
		cb++;
	}
	if (!found_ok)
		return SIM800C_ERROR;
	// больше костылей, богу костылей
	// копирование строки-числа из участка в начало
	cb = 0;
	while (buf[7+cb] != '\r')
	{
		buf2[cb] = buf[7+cb];
		cb++;
	}
	buf2[cb] = 0;
	strcpy(&buf[0], template[3]);
	strcpy(&buf[strlen(template[3])], &buf2[0]);
	__SIM800C_USER_UartTX((uint8_t*)buf,  strlen(buf));
	return SIM800C_OK;
}
