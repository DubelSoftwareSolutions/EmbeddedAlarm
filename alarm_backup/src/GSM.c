#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"

#include "stm32f4xx_hal.h"
#include "usart.h"
#include <stdlib.h>
#include <string.h>
#include "GSM.h"

void GSM_Parse()
{
	if((char)gsm_Received == '\r')
	{
		gsm_isCR = 1;
	}
	else if((char)gsm_Received == '\n' && gsm_isCR==1){

		char newBuff[gsm_currSize];
		memcpy(newBuff, gsm_buffer, gsm_currSize);
		//printf("[DBG BUF]: %s\r\n",newBuff);

		if (strstr(newBuff, "OK\r\n") != NULL)
		{
			GSM_Status = HAL_OK;
			printf("[DBG] RECEIVED OK\r\n");
		}
		else if(strstr(newBuff, "ERROR\r\n") != NULL)
		{
			GSM_Status = HAL_ERROR;
			printf("[DBG] RECEIVED ERROR\r\n");
		}
		gsm_currSize = 0; //clear buffer
	}
	else
	{
		gsm_isCR=0;
	}
}

void GSM_SendSMS()
{
	if(!sending)
	{
		osDelay(100);
		printf("[DBG] confsms()\r\n");
		GSM_ConfigureSMS();
		osDelay(2000);
		printf("[DBG] setnum()\r\n");
		GSM_SetNumber();
		osDelay(4000);
	}

	if(sending)
	{
		printf("[DBG] sendsms()\r\n");
		GSM_SendTestMessage();
		sending = 0;
	}
}

void GSM_ConfigureSMS()
{
	uint8_t data[GSM_MAX_MESSAGE_SIZE];
	uint16_t MessageSize;
	MessageSize=sprintf(data,"AT+CMGF=1\r\n");
	HAL_UART_Transmit_IT(&GSM_huart,data,MessageSize);
}

void GSM_SetNumber()
{
	MessageSize=sprintf(data,"AT+CMGS=\"48792770832\"\r\n");
	HAL_UART_Transmit_IT(&GSM_huart,data,MessageSize);
	printf("[DBG] Send buffer: %s",data);
}

void GSM_SendTestMessage()
{
	HAL_Delay(100);
	MessageSize=sprintf(data,msg);
	while(HAL_UART_Transmit(&GSM_huart,data,MessageSize,100)!=HAL_OK);

	printf("[DBG] Text transmitted\r\n");
	MessageSize=sprintf(data,"\x1A\r\n");
	while(HAL_UART_Transmit(&GSM_huart,data,MessageSize,100)!=HAL_OK);

	printf("[DBG] End sign transmitted\r\n");
}

void GSM_Init()
{
	sending = 0;
	HAL_UART_Receive_IT(&GSM_huart, &gsm_Received, 1);

	MessageSize=sprintf(data,"AT\r\n");
	HAL_UART_Transmit_IT(&GSM_huart,data,MessageSize);
	osDelay(300);
	HAL_UART_Transmit_IT(&GSM_huart,data,MessageSize);
	osDelay(300);
	HAL_UART_Transmit_IT(&GSM_huart,data,MessageSize);
}
