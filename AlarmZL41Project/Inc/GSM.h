/*
 * GSM.h
 *
 *  Created on: 10.04.2017
 *      Author: Krzysztof
 */

#ifndef GSM_H_
#define GSM_H_

#define GSM_huart huart6

#define GSM_ATREADY_MESSAGE_SIZE 19 //bytes
#define GSM_ATREADY_TIMEOUT 3000 //milliseconds
#define GSM_ATREADY_MESSAGE "\0AT command ready\r\n"
#define GSM_RETURN_MESSAGE_SIZE 4 //bytes
#define GSM_AUTOBAUDRATE_TIMEOUT 1000 //milliseconds
#define GSM_TRANSMISSION_TIMEOUT 100 //milliseconds
#define GSM_AUTOBAUDRATE_MESSAGE_SIZE 4 //bytes
#define GSM_AUTOBAUDRATE_ATTEMPTS 8

void GSM_WaitForATReady();
void GSM_VerifyATReady();
uint8_t GSM_isATReady();
void GSM_AutoBaudrate_Synchronize();
void GSM_VerifyAutoBaudrate();
uint8_t GSM_isBaudrateSet();

#endif /* GSM_H_ */
