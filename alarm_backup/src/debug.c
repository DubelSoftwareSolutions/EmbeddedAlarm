/*
 * debug.c
 *
 *  Created on: 25 maj 2017
 *      Author: flisu
 */

#include "debug.h"

int _write(int file, char *ptr, int len)
{
	HAL_UART_Transmit(&huart4, ptr, len, 50);
	return len;
}
