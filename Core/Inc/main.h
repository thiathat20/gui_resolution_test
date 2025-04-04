/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32u5xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "cmsis_os2.h"
#include "rtc.h"

#include "eHG4_api.h"

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

//Annotation processing is required during initial upload of nRF9160

//#define nRF9160_initial_upload
//#define nRF9160_nRFCLOUD_Init
//#define nRF9160_no_auto_gps
#define nRF9160_KT
//#define nRF9160_cell_location
//#define nRF9160_Fall_Difference_Value_Send

#define PRINT_INFO(format, arg...)      printf(format , ## arg)

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */
typedef struct
{
  uint16_t msgID;
  uint16_t msgType;
  uint8_t param[8];
} message_t;

void delay_us(uint16_t time);

extern osMessageQueueId_t msgQueueHandle;
extern osMessageQueueId_t guiQueueHandle;
extern osMessageQueueId_t intQueueHandle;
extern osMessageQueueId_t ppgQueueHandle;
extern osMessageQueueId_t catm1QueueHandle;
extern osMessageQueueId_t timerQueueHandle;

extern message_t msgData_s;


extern uint32_t sys_timer_cnt;
extern bool sec_tick;

extern bool read_rtc_time;
extern bool read_mems;
extern bool read_measPPG;
extern bool haptic_check;

extern uint8_t ssRunFlag;
extern uint8_t initFlag;
extern uint8_t pmicInitFlag;
extern uint8_t wpmInitializationFlag;
extern uint8_t lcdInitFlag;
extern uint8_t pmicBusyFlag;

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define BT_WKUP_B_Pin GPIO_PIN_2
#define BT_WKUP_B_GPIO_Port GPIOE
#define DEBUG_RX_Pin GPIO_PIN_11
#define DEBUG_RX_GPIO_Port GPIOC
#define LCD_BL_PWM_Pin GPIO_PIN_5
#define LCD_BL_PWM_GPIO_Port GPIOI
#define LCD_PWR_Pin GPIO_PIN_0
#define LCD_PWR_GPIO_Port GPIOD
#define SPEAKER_EN_Pin GPIO_PIN_4
#define SPEAKER_EN_GPIO_Port GPIOE
#define LCD_DC_Pin GPIO_PIN_1
#define LCD_DC_GPIO_Port GPIOE
#define PMIC_PFN2_Pin GPIO_PIN_5
#define PMIC_PFN2_GPIO_Port GPIOB
#define PMIC_PFN2_EXTI_IRQn EXTI5_IRQn
#define TEMP_INT_Pin GPIO_PIN_10
#define TEMP_INT_GPIO_Port GPIOG
#define SS_MFIO_Pin GPIO_PIN_4
#define SS_MFIO_GPIO_Port GPIOD
#define DEBUG_TX_Pin GPIO_PIN_10
#define DEBUG_TX_GPIO_Port GPIOC
#define SW_CLK_Pin GPIO_PIN_14
#define SW_CLK_GPIO_Port GPIOA
#define LTE_COEX1_Pin GPIO_PIN_5
#define LTE_COEX1_GPIO_Port GPIOE
#define LCD_TE_Pin GPIO_PIN_0
#define LCD_TE_GPIO_Port GPIOE
#define LS_EN_1_Pin GPIO_PIN_0
#define LS_EN_1_GPIO_Port GPIOF
#define TOUCH_INT_Pin GPIO_PIN_13
#define TOUCH_INT_GPIO_Port GPIOC
#define TOUCH_INT_EXTI_IRQn EXTI13_IRQn
#define IMU_INT1_Pin GPIO_PIN_6
#define IMU_INT1_GPIO_Port GPIOE
#define SS_RSTN_Pin GPIO_PIN_5
#define SS_RSTN_GPIO_Port GPIOD
#define LS_EN_2_Pin GPIO_PIN_1
#define LS_EN_2_GPIO_Port GPIOF
#define LS_EN_3_Pin GPIO_PIN_2
#define LS_EN_3_GPIO_Port GPIOF
#define LCD_RESET_Pin GPIO_PIN_1
#define LCD_RESET_GPIO_Port GPIOD
#define TP_RESET_Pin GPIO_PIN_2
#define TP_RESET_GPIO_Port GPIOD
#define LTE_UART_RX_Pin GPIO_PIN_10
#define LTE_UART_RX_GPIO_Port GPIOA
#define SW_DIO_Pin GPIO_PIN_13
#define SW_DIO_GPIO_Port GPIOA
#define LTE_UART_RTS_Pin GPIO_PIN_12
#define LTE_UART_RTS_GPIO_Port GPIOA
#define LS_EN_3_new_Pin GPIO_PIN_3
#define LS_EN_3_new_GPIO_Port GPIOF
#define PMIC_INT_new_Pin GPIO_PIN_7
#define PMIC_INT_new_GPIO_Port GPIOG
#define PRESS_INT_Pin GPIO_PIN_9
#define PRESS_INT_GPIO_Port GPIOC
#define PRESS_INT_EXTI_IRQn EXTI9_IRQn
#define MAG_INT_Pin GPIO_PIN_8
#define MAG_INT_GPIO_Port GPIOC
#define MAG_INT_EXTI_IRQn EXTI8_IRQn
#define LTE_UART_TX_Pin GPIO_PIN_9
#define LTE_UART_TX_GPIO_Port GPIOA
#define LTE_UART_CTS_Pin GPIO_PIN_11
#define LTE_UART_CTS_GPIO_Port GPIOA
#define MIC_SDIN_Pin GPIO_PIN_10
#define MIC_SDIN_GPIO_Port GPIOE
#define CATM1_GPIO_EN_Pin GPIO_PIN_4
#define CATM1_GPIO_EN_GPIO_Port GPIOG
#define CATM1_VBAT_ON_Pin GPIO_PIN_6
#define CATM1_VBAT_ON_GPIO_Port GPIOC
#define Themistor_Pin GPIO_PIN_7
#define Themistor_GPIO_Port GPIOA
#define MIC_CCK0_Pin GPIO_PIN_9
#define MIC_CCK0_GPIO_Port GPIOE
#define LTE_GNSS_WKUP_Pin GPIO_PIN_3
#define LTE_GNSS_WKUP_GPIO_Port GPIOG
#define PMIC_INT_Pin GPIO_PIN_15
#define PMIC_INT_GPIO_Port GPIOD
#define PMIC_AIN1_Pin GPIO_PIN_3
#define PMIC_AIN1_GPIO_Port GPIOC
#define PMIC_PFN2_new_Pin GPIO_PIN_0
#define PMIC_PFN2_new_GPIO_Port GPIOA
#define PMIC_ALRT_Pin GPIO_PIN_0
#define PMIC_ALRT_GPIO_Port GPIOB
#define BLE_RESET_Pin GPIO_PIN_12
#define BLE_RESET_GPIO_Port GPIOD
#define PMIC_MPC0_Pin GPIO_PIN_2
#define PMIC_MPC0_GPIO_Port GPIOB
#define LTE_COEX2_Pin GPIO_PIN_7
#define LTE_COEX2_GPIO_Port GPIOE
#define IMU_INT2_1_Pin GPIO_PIN_12
#define IMU_INT2_1_GPIO_Port GPIOB
#define LTE_RESET_Pin GPIO_PIN_15
#define LTE_RESET_GPIO_Port GPIOB
#define BLE_TX_Pin GPIO_PIN_2
#define BLE_TX_GPIO_Port GPIOA
#define SENSOR_PWR_EN_1V8_Pin GPIO_PIN_11
#define SENSOR_PWR_EN_1V8_GPIO_Port GPIOF
#define CPU_FUNC_SW_Pin GPIO_PIN_14
#define CPU_FUNC_SW_GPIO_Port GPIOB
#define CPU_FUNC_SW_EXTI_IRQn EXTI14_IRQn
#define BLE_RX_Pin GPIO_PIN_3
#define BLE_RX_GPIO_Port GPIOA
#define TP1_Pin GPIO_PIN_1
#define TP1_GPIO_Port GPIOB
#define SPI_CS_Pin GPIO_PIN_12
#define SPI_CS_GPIO_Port GPIOE

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
