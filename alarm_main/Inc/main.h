/**
  ******************************************************************************
  * File Name          : main.h
  * Description        : This file contains the common defines of the application
  ******************************************************************************
  *
  * COPYRIGHT(c) 2017 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H
  /* Includes ------------------------------------------------------------------*/

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private define ------------------------------------------------------------*/

#define ACC_SS_Pin GPIO_PIN_4
#define ACC_SS_GPIO_Port GPIOE
#define ACC_MISO_Pin GPIO_PIN_5
#define ACC_MISO_GPIO_Port GPIOE
#define ACC_MOSI_Pin GPIO_PIN_6
#define ACC_MOSI_GPIO_Port GPIOE
#define ACC_INT1_Pin GPIO_PIN_0
#define ACC_INT1_GPIO_Port GPIOA
#define GPS_RX_Pin GPIO_PIN_7
#define GPS_RX_GPIO_Port GPIOE
#define GPS_TX_Pin GPIO_PIN_8
#define GPS_TX_GPIO_Port GPIOE
#define GPS_TIME_Pin GPIO_PIN_9
#define GPS_TIME_GPIO_Port GPIOE
#define GPS_INT_Pin GPIO_PIN_10
#define GPS_INT_GPIO_Port GPIOE
#define ACC_INT2_Pin GPIO_PIN_11
#define ACC_INT2_GPIO_Port GPIOE
#define GSM_PWRKEY_Pin GPIO_PIN_12
#define GSM_PWRKEY_GPIO_Port GPIOE
#define GSM_ANT_ENABLE_Pin GPIO_PIN_13
#define GSM_ANT_ENABLE_GPIO_Port GPIOE
#define LED1_Pin GPIO_PIN_11
#define LED1_GPIO_Port GPIOD
#define LED2_Pin GPIO_PIN_12
#define LED2_GPIO_Port GPIOD
#define LED3_Pin GPIO_PIN_13
#define LED3_GPIO_Port GPIOD
#define LED4_Pin GPIO_PIN_14
#define LED4_GPIO_Port GPIOD
#define LED5_Pin GPIO_PIN_15
#define LED5_GPIO_Port GPIOD
#define GSM_RX_Pin GPIO_PIN_0
#define GSM_RX_GPIO_Port GPIOE
#define GSM_TX_Pin GPIO_PIN_1
#define GSM_TX_GPIO_Port GPIOE
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

/**
  * @}
  */ 

/**
  * @}
*/ 

#endif /* __MAIN_H */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
