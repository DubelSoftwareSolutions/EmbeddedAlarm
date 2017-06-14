/*
 * GSM.h
 *
 *  Created on: 10.04.2017
 *      Author: Krzysztof
 */

#ifndef GSM_H_
#define GSM_H_

#define TIM7_POSTSCALER 60 //seconds

#define GSM_huart huart1

#define GSM_ATREADY_MESSAGE_SIZE 19 //bytes
#define GSM_ATREADY_TIMEOUT 3000 //milliseconds
#define GSM_RETURN_MESSAGE_SIZE 4 //bytes
#define GSM_AUTOBAUDRATE_TIMEOUT 1000 //milliseconds
#define GSM_TRANSMISSION_TIMEOUT 100 //milliseconds
#define GSM_AUTOBAUDRATE_MESSAGE_SIZE 4 //bytes
#define GSM_AUTOBAUDRATE_ATTEMPTS 8
#define GSM_RECEIVER_PHONE_NUMBER "48792770832"
#define GSM_MAX_MESSAGE_SIZE 300

HAL_StatusTypeDef GSM_Status;

size_t gsm_currSize;
int gsm_isCR;
uint8_t gsm_Received;
char gsm_buffer[500];

int sending;

uint8_t msg[GSM_MAX_MESSAGE_SIZE];
uint16_t msg_size;
uint8_t data[GSM_MAX_MESSAGE_SIZE];
uint16_t MessageSize;

void GSM_Init();
void GSM_Parse();
void GSM_SendSMS();
void GSM_SetNumber();
void GSM_ConfigureSMS();
void GSM_SendTestMessage();

#endif /* GSM_H_ */
