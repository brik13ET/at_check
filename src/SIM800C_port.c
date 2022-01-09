#include <stdint.h>
#include <stdlib.h>

#include <string.h>
#include <windows.h>
#include <stdio.h>
#include <ctype.h>

#include <SIM800C.h>
#include "main.h"

uint8_t need_eol = 1;

void __SIM800C_USER_UartTX(uint8_t* data, uint8_t lth)
{
	if (need_eol)
	{
		need_eol = 0;
		printf(">");
	}
	for (int i = 0; i < lth; ++i)
	{
		if (!isprint(data[i]) && !isspace(data[i]) )
			printf("%02xh", data[i]);
		printf("%c", data[i]);

		if (data[i] == '\n')
			need_eol = 1;

	}
}

uint8_t __SIM800C_USER_UartRX(uint8_t* data, uint16_t lth, uint32_t timeout)
{
	printf("< ");
	if (lth > 2)
		scanf("%.*s", lth-2, data);
	else
		memcpy("\r\n", data, lth);
	return SIM800C_OK;
}

uint8_t __status = 0;

uint8_t __SIM800C_USER_STATUS_Read()
{
	printf("status_READ: %02x\n", __status);
	return __status;
}
void __SIM800C_USER_POWER_Write(uint8_t state)
{
	__status = state;
	printf("status_set: %02x\n", __status);
}

void SIM_delay(uint16_t ms)
{
	Sleep(ms);
}
