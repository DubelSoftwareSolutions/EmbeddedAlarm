/*
 * gps.c
 *
 *  Created on: 7 cze 2017
 *      Author: Tom
 */

#include <stdlib.h>
#include <string.h>
#include "gps.h"
#include "debug.h"

char* concat(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1)+strlen(s2)+1);//+1 for the zero-terminator
    //in real code you would check for errors in malloc here
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}


void searchCRLF(){
	 //uint8_t Data[500]; // Tablica przechowujaca wysylana wiadomosc.
	 //uint16_t size = 0; // Rozmiar wysylanej wiadomosci

	if((char)Received == '\r'){
		 isCR = 1;
	 } else if ((char)Received == '\n' && isCR==1){

		 char newBuff[currSize];
		 memcpy(newBuff, buffer, currSize);

		 if (strstr(newBuff, "$GPRMC") != NULL) {
		     // contains
			 //size = sprintf(result_u, buffer);
			 //HAL_UART_Transmit(&huart4, result_u, size, 1000);

			 //PARSE TIME
			 if(newBuff[8]!='V'){
				 for(int i=0; i<9;i++){
					 gps_time[i] = newBuff[7+i];
				 }
				 gps_time[9] = '\0';
			 }
			 else
			 {
				 sprintf(gps_time, "NotValid");
			 }

			 if(newBuff[17]=='A'){ // je�li nie ma ostrzezenia V
				 //PARSE LATITUDE
				 gps_latitude[0]=newBuff[19];
				 gps_latitude[1]=newBuff[20];
				 gps_latitude[2]='.';
				 gps_latitude[3]=newBuff[21];
				 gps_latitude[4]=newBuff[22];
				 gps_latitude[5]=39;
				 gps_latitude[6]=newBuff[24];
				 gps_latitude[7]=newBuff[25];
				 gps_latitude[8]='.';
				 gps_latitude[9]=newBuff[26];
				 gps_latitude[10]=newBuff[27];
				 gps_latitude[11]=newBuff[28];
				 gps_latitude[12]=34;
				 gps_latitude[13]=newBuff[30];
				 gps_latitude[14]='\0';


				 //PARSE LONGITUDE
				 gps_longitude[0]=newBuff[33];
				 gps_longitude[1]=newBuff[34];
				 gps_longitude[2]='.';
				 gps_longitude[3]=newBuff[35];
				 gps_longitude[4]=newBuff[36];
				 gps_longitude[5]=39;
				 gps_longitude[6]=newBuff[38];
				 gps_longitude[7]=newBuff[39];
				 gps_longitude[8]='.';
				 gps_longitude[9]=newBuff[40];
				 gps_longitude[10]=newBuff[41];
				 gps_longitude[11]=newBuff[42];
				 gps_longitude[12]=34;
				 gps_longitude[13]=newBuff[44];
				 gps_longitude[14]='\0';
			 }
			 else
			 { // display buffer if is not valid
				 sprintf(gps_latitude, "NotValid");
				 sprintf(gps_longitude, "NotValid");
			 }
			 //size = sprintf(result_u, gps_longitude);
			 //HAL_UART_Transmit_IT(&huart4, result_u, size);

			 //sprintf(gps_latitude, "NotValid");
			 //sprintf(gps_longitude, "NotValid");
			 //printf("gps_time: %s\n\r", gps_time);
			 //printf("lati: %s \n\r", gps_latitude);
			 //printf("longi: %s \n\r", gps_longitude);
		 }

		 //size = sprintf(result_u, newBuff);
		 //HAL_UART_Transmit_IT(&huart4, result_u, size);
		 //clear buffer
		 currSize = 0;
	 } else{
		 isCR=0;
	 }
}

HAL_StatusTypeDef GPSInit(){
	currSize=0;
	isCR =0;

	sprintf(gps_time, "TimInit");
	sprintf(gps_latitude, "LatInit");
	sprintf(gps_longitude, "LonInit");

	HAL_UART_Receive_IT(&huart2, &Received, 1);
	/*
	HAL_Delay(3000);
	printf("GPSLat: %s , GPSLon: %s \n\r", gps_latitude, gps_longitude);
	*/

	return HAL_OK;

}


