#include "usart.h"

#ifndef GPS_H_
#define GPS_H_

uint8_t Received;
char buffer[500];
char gps_latitude[20];
char gps_longitude[20];
char gps_time[20];

size_t currSize;
int isCR;

uint8_t result_u[100];
uint16_t size; // Rozmiar wysylanej wiadomosci

/*!
 * \brief Funkcja dodajaca do siebie dwa stringi, zwraca string
 * \@param[out] result Dodane do siebie stringi
 * \@param[in] s1 Pierwszy string
 * \@param[in] s2 Drugi string
 * Prosta funkcja pomocnicza wykorzystywana przy operacji na buforze.
 */
char* concat(const char *s1, const char *s2);


/*!
 * \brief Funkcja parsowania informacji z GPS *
 * Glowna funkcja modulu GPS. W otrzymanej wiadomosci zmiennej globalnej Received szuka linijki posiadaj�cej fraz� $GPRMC.
 * Gdy linijka ta jest znaleziona, zostaje znak po znaku parsowana do globalnych zmiennych gps_time, gps_latitude i gps_longitude.
 *
 */
void searchCRLF();

/*
 * \brief Funkcja obslugujaca przerwanie.
 * @param[in] huart Handle dla uart.
 * Gdy zosta�o wykryte przerwanie, wywo�ane zostaje funkcja obs�uguj�ca wiadomosc od GPS.
 */

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) ;

/*
 * \brief Funkcja inicjalizacyjna GPS
 * @param[out] status Zwr�cony status po poprawnej inicjalizacji
 * Funkcja inicjalizuje niekt�re zmienne globalne.
 */
HAL_StatusTypeDef GPSInit();



#endif /* GPS_H_ */
