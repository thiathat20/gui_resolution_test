/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : app_freertos.c
  * Description        : Code for freertos applications
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

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os2.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "mems.h"


/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define PRESSURE_VAL_LEN 10

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
uint8_t haptic_check_temp = 0;
uint8_t backlightTurnONCheck = 0;
unsigned char batterylevel;

#define fall_Check_cycle 60 // falling event occure => after N sec => MQTT // 60
int fallCheckTime = 0;
uint8_t fallCheckFlag = 0;

#define SOS_Check_cycle 60 // SOS event occure => after N sec => MQTT // 60
uint8_t SOSCheckTime = 0;
uint8_t SOSCheckFlag = 0;
uint8_t sendSOSFlag = 0;

int pressCheckTime = 0;
uint8_t pressCheckFlag = 0;

int pressCheckStartTime = 0;
uint8_t pressCheckStartFlag = 0;

uint8_t catM1MqttDangerMessage = 0;

int gpsTime = 0;
#define gps_offCheck_cycle (60*5)+10

bool gpsCheckFlag = false;
uint8_t time_check = 0;
uint8_t lteRSSI_0_4 = 0; // CATM1 signal RSSI 0 to 4 value
int previousRSSIstate = -1;

#define cat_m1_rssi_cycle 40
uint8_t cat_m1_rssi_cycleTime = 0;
bool cat_m1_rssi_cycleFlag = false;

#define mqtt_operation_cycle 60*1
int mqttTime = 0;
bool mqttFlag = false;

//stm32wb_at_BLE_ADV_DATA_t param_BLE_DATA;

/* USER CODE END Variables */
/* Definitions for initTask */
osThreadId_t initTaskHandle;
const osThreadAttr_t initTask_attributes = {
  .name = "initTask",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 1024 * 4
};
/* Definitions for lcdTask */
osThreadId_t lcdTaskHandle;
const osThreadAttr_t lcdTask_attributes = {
  .name = "lcdTask",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 4096 * 4
};
/* Definitions for ppmTask */
osThreadId_t ppmTaskHandle;
const osThreadAttr_t ppmTask_attributes = {
  .name = "ppmTask",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 1024 * 4
};
/* Definitions for wpmTask */
osThreadId_t wpmTaskHandle;
const osThreadAttr_t wpmTask_attributes = {
  .name = "wpmTask",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 1024 * 4
};
/* Definitions for spmTask */
osThreadId_t spmTaskHandle;
const osThreadAttr_t spmTask_attributes = {
  .name = "spmTask",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 512 * 4
};
/* Definitions for secTimerTask */
osThreadId_t secTimerTaskHandle;
const osThreadAttr_t secTimerTask_attributes = {
  .name = "secTimerTask",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 512 * 4
};
/* Definitions for checkINTTask */
osThreadId_t checkINTTaskHandle;
const osThreadAttr_t checkINTTask_attributes = {
  .name = "checkINTTask",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 512 * 4
};
/* Definitions for dataTask */
osThreadId_t dataTaskHandle;
const osThreadAttr_t dataTask_attributes = {
  .name = "dataTask",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 512 * 4
};
/* Definitions for msgHandleTask */
osThreadId_t msgHandleTaskHandle;
const osThreadAttr_t msgHandleTask_attributes = {
  .name = "msgHandleTask",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 128 * 4
};
/* Definitions for msgQueue */
osMessageQueueId_t msgQueueHandle;
const osMessageQueueAttr_t msgQueue_attributes = {
  .name = "msgQueue"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
osMessageQueueId_t guiQueueHandle;
const osMessageQueueAttr_t guiQueue_attributes = {
  .name = "guiQueue"
};

osMessageQueueId_t intQueueHandle;
const osMessageQueueAttr_t intQueue_attributes = {
  .name = "intQueue"
};

osMessageQueueId_t ppgQueueHandle;
const osMessageQueueAttr_t ppgQueue_attributes = {
  .name = "ppgQueue"
};

osMessageQueueId_t catm1QueueHandle;
const osMessageQueueAttr_t catm1Queue_attributes = {
  .name = "catm1Queue"
};

osMessageQueueId_t timerQueueHandle;
const osMessageQueueAttr_t timerQueue_attributes = {
  .name = "timerQueue"
};

/* USER CODE END FunctionPrototypes */

void StartInitTask(void *argument);
void StartlcdTask(void *argument);
void StartPPMTask(void *argument);
void StartWPMTask(void *argument);
void StartSPMTask(void *argument);
void StartSecTimerTask(void *argument);
void StartCheckINTTask(void *argument);
void StartDATATask(void *argument);
void StartMsgTask(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* Hook prototypes */
void vApplicationIdleHook(void);

/* USER CODE BEGIN 2 */
void vApplicationIdleHook( void )
{
   /* vApplicationIdleHook() will only be called if configUSE_IDLE_HOOK is set
   to 1 in FreeRTOSConfig.h. It will be called on each iteration of the idle
   task. It is essential that code added to this hook function never attempts
   to block in any way (for example, call xQueueReceive() with a block time
   specified, or call vTaskDelay()). If the application makes use of the
   vTaskDelete() API function (as this demo application does) then it is also
   important that vApplicationIdleHook() is permitted to return to its calling
   function, because it is the responsibility of the idle task to clean up
   memory allocated by the kernel to any task that has since been deleted. */
}
/* USER CODE END 2 */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */
  /* creation of msgQueue */
  msgQueueHandle = osMessageQueueNew (16, sizeof(message_t), &msgQueue_attributes);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  guiQueueHandle = osMessageQueueNew (16, sizeof(message_t), &guiQueue_attributes);
  intQueueHandle = osMessageQueueNew (16, sizeof(message_t), &intQueue_attributes);
  ppgQueueHandle = osMessageQueueNew (16, sizeof(message_t), &ppgQueue_attributes);
  catm1QueueHandle = osMessageQueueNew (16, sizeof(message_t), &catm1Queue_attributes);
  timerQueueHandle = osMessageQueueNew (16, sizeof(message_t), &timerQueue_attributes);

  /* USER CODE END RTOS_QUEUES */
  /* creation of initTask */
  initTaskHandle = osThreadNew(StartInitTask, NULL, &initTask_attributes);

  /* creation of lcdTask */
  lcdTaskHandle = osThreadNew(StartlcdTask, NULL, &lcdTask_attributes);

  /* creation of ppmTask */
  ppmTaskHandle = osThreadNew(StartPPMTask, NULL, &ppmTask_attributes);

  /* creation of wpmTask */
  wpmTaskHandle = osThreadNew(StartWPMTask, NULL, &wpmTask_attributes);

  /* creation of spmTask */
  spmTaskHandle = osThreadNew(StartSPMTask, NULL, &spmTask_attributes);

  /* creation of secTimerTask */
  secTimerTaskHandle = osThreadNew(StartSecTimerTask, NULL, &secTimerTask_attributes);

  /* creation of checkINTTask */
  checkINTTaskHandle = osThreadNew(StartCheckINTTask, NULL, &checkINTTask_attributes);

  /* creation of dataTask */
  dataTaskHandle = osThreadNew(StartDATATask, NULL, &dataTask_attributes);

  /* creation of msgHandleTask */
  msgHandleTaskHandle = osThreadNew(StartMsgTask, NULL, &msgHandleTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}
/* USER CODE BEGIN Header_StartInitTask */
/**
* @brief Function implementing the initTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartInitTask */
void StartInitTask(void *argument)
{
  /* USER CODE BEGIN initTask */
  PRINT_INFO("StartInitTask\r\n");
  /* Infinite loop */
  for(;;)
  {
    if(haptic_check) {
      haptic_check = false;
      hapticCheck();
    }


    if(read_measPPG) {
      read_measPPG = false;
      measPPG();
    }
    
    osDelay(1);
  }
  /* USER CODE END initTask */
}

/* USER CODE BEGIN Header_StartlcdTask */
/**
* @brief Function implementing the lcdTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartlcdTask */
void StartlcdTask(void *argument)
{
  /* USER CODE BEGIN lcdTask */
  /* Infinite loop */
  pmic_init();
  pmicInitFlag = 1;
  PRINT_INFO("pmicInitFlag = %d\r\n", pmicInitFlag);

  pmicSOCRead(&ehg.battVal);

  while(!pmicInitFlag){
    osDelay(10);
  }

  eHG4_Init(); // ehg reset

  PRINT_INFO("StartlcdTask\r\n");
//  ehg.hapticFlag = 1;
  runHaptic(20, 500, 1); // turn on device haptic

  ST7789_gpio_setting();
  ST7789_Init();
//  ehg.set_bLevel = 7;
//  ehg.before_bLevel = ehg.set_bLevel;
  ST7789_brightness_setting(ehg.set_bLevel);
  backlightTurnONCheck = 1;

  lcdInitFlag = 1;
  PRINT_INFO("lcdInitFlag = %d\r\n", lcdInitFlag);

  touchgfxSignalVSync();
#if 1
  MX_TouchGFX_Process();

  vTaskDelete(NULL);
#else
  for(;;)
  {
    osDelay(1);
  }
#endif
  /* USER CODE END lcdTask */
}

/* USER CODE BEGIN Header_StartPPMTask */
/**
* @brief Function implementing the ppmTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartPPMTask */
void StartPPMTask(void *argument)
{
  /* USER CODE BEGIN ppmTask */
  while(!pmicInitFlag){
    osDelay(10);
  }
  PRINT_INFO("StartPPMTask\r\n");

  //BLE init
	//stm32wb5mmg_init();
	//stm32wb5mmg_adv_setting(&param_BLE_DATA);

  /* Infinite loop */
  for(;;)
  {
    //stm32wb5mmg_adv(&param_BLE_DATA);
    osDelay(10);
  }
  /* USER CODE END ppmTask */
}

/* USER CODE BEGIN Header_StartWPMTask */
/**
* @brief Function implementing the wpmTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartWPMTask */
void StartWPMTask(void *argument)
{
  /* USER CODE BEGIN wpmTask */
  while(!pmicInitFlag){
    osDelay(10);
  }
  // device ID init (ST UID)
  //deviceID = HAL_GetUIDw2();
  //PRINT_INFO("deviceID >>> %u\r\n",deviceID);
  PRINT_INFO("StartWPMTask\r\n");

  // UART INT INIT, buffer init
  nrf9160_init();
  nrf9160_clear_buf();
  // CatM1 PWR GPIO ON
  catM1PWRGPIOInit(); // ->??
  HAL_Delay(1000);

//  // WiFi-BLE init
//  nora_w10_init();
//  cat_m1_Status_FallDetection_t cat_m1_Status_FallDetection = {
//      .bid = deviceID, // Band??? bid ���� ??????
//      .type = 0,
//      .fall_detect = 1
//  };

//    strncpy((char*)cat_m1_at_cmd_rst.gps,
//      "36.106335,128.384310,119.546387,7.287167,0.220983,0.000000,2024-09-25 08:33:25",
//     sizeof(cat_m1_at_cmd_rst.gps) - 1);
//    cat_m1_at_cmd_rst.gps[sizeof(cat_m1_at_cmd_rst.gps) - 1] = '\0';
  /* Infinite loop */
  for(;;)
  {
    if(gpsCheckFlag) {
      gpsCheckFlag = false;
      
      cat_m1_rssi_cycleTime++;
      //PRINT_INFO("mqttTime >>> %d\r\n",mqttTime);
      if(cat_m1_rssi_cycleTime > cat_m1_rssi_cycle )
      {
        cat_m1_rssi_cycleFlag = true;
        cat_m1_rssi_cycleTime = 0;
      }
#if !defined(nRF9160_KT)
      if(cat_m1_Status.gpsChecking == 0)
      {
        mqttTime++;
      }
#else
        mqttTime++;
#endif
  //    PRINT_INFO("mqttTime >>> %d\r\n",mqttTime);
      if(mqttTime > mqtt_operation_cycle)
      {
        mqttFlag = true;
        mqttTime = 0;
      }

      if(cat_m1_Status.txflag)
      {
        UartRxRetryTime++;
      }
  //    PRINT_INFO("UartRxRetryTime >>> %d\r\n",UartRxRetryTime);
      if(UartRxRetryTime > 3)
      {
        uart_init();
        UartRxRetryTime = 0;
        cat_m1_Status.txflag = 0;
      }
      else if(UartRxRetryTime > 10)
      {
#if !defined(nRF9160_initial_upload)
        catM1Reset();
#endif
        UartRxRetryTime = 0;
        cat_m1_Status.txflag = 0;
      }
#if !defined(nRF9160_no_auto_gps)
      if(ehg.gpsFlag == false)
      {
        gpsTime++;
      }
#endif
  //    PRINT_INFO("gpsTime >>> %d\r\n",gpsTime);
      if(gpsTime > gps_operation_cycle)
      {
        ehg.gpsFlag = true;
        gpsTime = 0;
      }
      if(cat_m1_Status.gpsChecking)
      {
        gpsOffCheckTime++;
      }
      if(gpsOffCheckTime > gps_offCheck_cycle)
      {
#if !defined(nRF9160_KT)
        catM1Reset();
#else
        nrf9160_Stop_gps();
        ehg.gpsFlag = false;
#endif
      }
    }
    
    if(wpmInitializationFlag == 0)
    {
      // CatM1 init
      nrf9160_ready();
    }
    if(wpmInitializationFlag && cat_m1_Status.Checked == 0)
    {
#if defined(nRF9160_nRFCLOUD_Init)
      if(!nRFCloudFlag)
      {
        catM1nRFCloud_Init();
      }
#endif
      nrf9160_check();
    }
    if(wpmInitializationFlag && cat_m1_Status.Checked == 1)
    {
      nrf9160_mqtt_setting();
      if(cat_m1_Status.InitialLoad == 0)
      {
        if(time_check == 0)
        {
          nrf9160_Get_time();
          time_check = 1;
        }
        nrf9160_Get_rssi();
  
        if(-95 <= cat_m1_Status_Band.rssi){
          previousRSSIstate = 0;
          lteRSSI_0_4 = 4;
        } else if(-105 <= cat_m1_Status_Band.rssi && cat_m1_Status_Band.rssi < -95) {
          previousRSSIstate = 0;
          lteRSSI_0_4 = 3;
        } else if(-115 <= cat_m1_Status_Band.rssi && cat_m1_Status_Band.rssi < -105) {
          previousRSSIstate = 0;
          lteRSSI_0_4 = 2;
        } else if(-125 <= cat_m1_Status_Band.rssi && cat_m1_Status_Band.rssi < -115) {
          lteRSSI_0_4 = 1;
        } else {
          lteRSSI_0_4 = 0;
        }
        cat_m1_Status.InitialLoad = 1;
  
        // succ connect CatM1
        sendMessage(MSG_GUI, HOME_SCREEN);
        ehg.brightness_count = 0;
      }
      //gpsTime = 0;
      cat_m1_rssi_cycleTime = 0;
    }
    if(wpmInitializationFlag && cat_m1_Status.Checked == 2)
    {
#if defined(nRF9160_nRFCLOUD_Init)
        if ((strlen((const char*)cat_m1_at_cmd_rst.uuid) > 0) && cat_m1_Status.mqttChecking == 0)
        {
          cat_m1_Status_uuid.bid = ehg.deviceID;
          send_UUID(&cat_m1_Status_uuid);
        }
#endif
#if !defined(nRF9160_KT)
      if ((mqttFlag && cat_m1_Status.gpsChecking == 0) || catM1MqttDangerMessage)
#else
      if (mqttFlag || catM1MqttDangerMessage)
#endif
      {
        //nrf9160_Get_gps_State();
        //test_send_json_publish();
        if(cat_m1_Status.mqttChecking == 0)
        {
          cat_m1_Status_Band_t cat_m1_Status_Band =
          {
            .bid = ehg.deviceID,
            .pid = 0xA021,
            .rssi = (cat_m1_at_cmd_rst.rssi),
            .start_byte = 0xAA,
            .hr = ehg.ssHr,
            .spo2 = ehg.ssSpo2,
            .motionFlag = lcd_ssDataEx.algo.spo2MotionFlag,
            .scdState = ehg.ssSCD,
            .activity = lcd_ssDataEx.algo.activity,
            .walk_steps = ehg.ssWalk,
            .run_steps = 0,
            .temperature = ehg.imuTemp,
            .pres = cat_m1_at_cmd_rst.altitude,
            .battery_level = ehg.battVal
          };
          send_Status_Band(&cat_m1_Status_Band);
  
#if defined(BattData_Value_Send)
          cat_m1_Status_BATTData_Value.bid = ehg.deviceID;
          cat_m1_Status_BATTData_Value.level = (int)ehg.batterylevel;
          cat_m1_Status_BATTData_Value.voltage = (int)batteryVoltage;
          send_BATTData_Value(&cat_m1_Status_BATTData_Value);
#endif
          nrf9160_Get_time();
//        // **RTC time update (correction)**
//        // Retrieve time information from CatM1
//        // Compare the RTC time with the CatM1 time
//        // If the difference is within 1 minute:
//        //     Update the RTC value using the CatM1 time
//        // Otherwise:
//        //     Retain the current RTC value
//        osDelay(100);
//        nrf9160_Get_time();
//        osDelay(100);
//        extern RTC_HandleTypeDef hrtc;
//        extern catM1Time nowTimeinfo;
//        extern RTC_TimeTypeDef sTime;
//        extern RTC_DateTypeDef sDate;
//
//        HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
//        HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
//        catM1Time nowNetTimeinfo = getCatM1Time();
//        catM1Time nowRTCTimeinfo = {sDate.Year, sDate.Month, sDate.Date, sTime.Hours, sTime.Minutes, sTime.Seconds};
//
//        if(isDifferenceWithinNMinute(nowNetTimeinfo, nowRTCTimeinfo, mqtt_operation_cycle+60)){
//          nowTimeinfo = nowNetTimeinfo;
//
//          // To prevent the appearance of time decreasing when updating RTC time with GNSS time,
//          // caused by RTC time flowing faster than GNSS time.
//          // RTC ?��간이 GNSS ?��간보?�� 빠르�????? ?��르면?��, RTC ?��간을 GNSS ?��간으�????? ?��?��?��?��?�� ?�� ?��간이 감소?��?�� 것처?�� 보이?�� ?��?��?�� 방�??���????? ?��?��.
//          if(sTime.Minutes > (uint8_t)nowTimeinfo.min){
//            sDate.Year = (uint8_t)nowTimeinfo.year;
//            sDate.Month = (uint8_t)nowTimeinfo.month;
//            sDate.Date = (uint8_t)nowTimeinfo.day;
//            sTime.Hours = (uint8_t)nowTimeinfo.hour;
//            sTime.Minutes = sTime.Minutes;
//            sTime.Seconds = 0;
//          }
//          else {
//            sDate.Year = (uint8_t)nowTimeinfo.year;
//            sDate.Month = (uint8_t)nowTimeinfo.month;
//            sDate.Date = (uint8_t)nowTimeinfo.day;
//            sTime.Hours = (uint8_t)nowTimeinfo.hour;
//            sTime.Minutes = (uint8_t)nowTimeinfo.min;
//            sTime.Seconds = (uint8_t)nowTimeinfo.sec;
//          }
//
//          HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
//          HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
//        } else {
//          nowTimeinfo = nowRTCTimeinfo;
//        }

          // CatM1 RSSI value update
          nrf9160_Get_rssi();
  
          if(-95 <= cat_m1_Status_Band.rssi){
            lteRSSI_0_4 = 4;
          } else if(-105 <= cat_m1_Status_Band.rssi && cat_m1_Status_Band.rssi < -95) {
            lteRSSI_0_4 = 3;
          } else if(-115 <= cat_m1_Status_Band.rssi && cat_m1_Status_Band.rssi < -105) {
            lteRSSI_0_4 = 2;
          } else if(-125 <= cat_m1_Status_Band.rssi && cat_m1_Status_Band.rssi < -115) {
            lteRSSI_0_4 = 1;
          } else {
            lteRSSI_0_4 = 0;
          }
        }
        mqttFlag = false;
        catM1MqttDangerMessage = 0;
      }
  
      if ((strlen((const char*)cat_m1_at_cmd_rst.gps) > 0) && cat_m1_Status.mqttChecking == 0 && cat_m1_Status.gpsChecking == 0 && gpsSendFlag == 0)
      {
          cat_m1_Status_GPS_Location.bid = ehg.deviceID;
          send_GPS_Location(&cat_m1_Status_GPS_Location);
  //        memset(&cat_m1_at_cmd_rst.gps, 0, sizeof(cat_m1_at_cmd_rst.gps));
      }
#if defined(nRF9160_cell_location)
      //soundFlag off no nRF9160_cell_location
      else if (ehg.soundFlag && !ehg.isCharging && cell_locationFlag && cat_m1_Status.mqttChecking == 0 && cat_m1_Status.gpsChecking == 0)
      {
          nrf9160_Get_cell_location();
          cell_locationFlag = false;
      }
#endif
      if(ehg.gpsFlag)
      {
        //catM1MqttDangerMessage = 1;
        //nrf9160_Stop_gps();
        nrf9160_Get_gps();
        //nrf9160_Get_gps_State();
        //ehg.gpsFlag = false;
      }
      if(cat_m1_Status.gpsChecking)
      {
        //nrf9160_Get_gps_State();
        if(cat_m1_Status.gpsOff)
        {
          nrf9160_Stop_gps();
        }
      }
      if(cat_m1_rssi_cycleFlag && cat_m1_Status.gpsChecking == 0 && cat_m1_Status.mqttChecking == 0)
      {
        nrf9160_Get_rssi();
        cat_m1_rssi_cycleFlag = false;
      }
  
    }
    //  if(wpmFlag ==1)
    //  {
  
    //    wpmFlag = 0;
    //  }
    //osDelay(10000);
    if(initFlag){
  
    }
    //BandAlert();

    osDelay(1);
  }
  /* USER CODE END wpmTask */
}

/* USER CODE BEGIN Header_StartSPMTask */
/**
* @brief Function implementing the spmTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartSPMTask */
void StartSPMTask(void *argument)
{
  /* USER CODE BEGIN spmTask */
  while(!pmicInitFlag){
    osDelay(10);
  }
  // Smart Sensor Hub init
  ssInit();
//  ssBegin(0x00);
//  ssRead_setting();
////  ssRunFlag = 1; // start read PPG, using Timer

  init_iis2mdc();
  init_ism330dhcx();
  init_lps22hh();

//  double pre_pressure[PRESSURE_VAL_LEN] = {0,};
  PRINT_INFO("StartSPMTask\r\n");

  /* Infinite loop */
  for(;;)
  {
    if(read_mems) {
      read_mems = false;
      readMems();
    }
    
    osDelay(1);
  }
  /* USER CODE END spmTask */
}

/* USER CODE BEGIN Header_StartSecTimerTask */
/**
* @brief Function implementing the secTimerTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartSecTimerTask */
void StartSecTimerTask(void *argument)
{
  /* USER CODE BEGIN secTimerTask */
  message_t recvMsg;
  
  while(!pmicInitFlag){
    osDelay(10);
  }
  // using parameter init (default val)
  uint8_t now_bLevel = ehg.set_bLevel;

  uint8_t pre_secTime = 0;
  ehg.screenOnTime = 20;
  uint8_t pre_brightness_count = 0;

  while(!lcdInitFlag){
    osDelay(10);
  }

  PRINT_INFO("StartSecTimerTask\r\n");

  /* Infinite loop */
  for(;;)
  {
#if 1
    if (osMessageQueueGetCount(timerQueueHandle) > 0)
    {
      if (osMessageQueueGet(timerQueueHandle, &recvMsg, 0, 0) == osOK)
      {
        switch(recvMsg.msgType) {
          case TIMER_GET_RTC:
            printf("Recv TIMER_GET_RTC\r\n");
            HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
            HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
            break;
          case TIMER_1SEC:
            printf("Recv TIMER_1SEC\r\n");
            sendMessage(MSG_SYSTEM, SOS_CHECK);
            sendMessage(MSG_SYSTEM, PMIC_CHECK);
            sendMessage(MSG_SYSTEM, BACKLIGHT_CHECK);
            sendMessage(MSG_SYSTEM, IMU_CHECK);

            gpsCheckFlag = true;
            read_measPPG = true;

            break;
          case TIMER_100MS:
//            printf("Recv TIMER_100MS\r\n");
            // change parameter val
            if(now_bLevel != ehg.set_bLevel){
              now_bLevel = ehg.set_bLevel;
              //HAL_Delay(100);
              ST7789_brightness_setting(now_bLevel);
            }
            break;

        }
      }
    }
#else
    if(read_rtc_time) {
      read_rtc_time = false;
      HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
      HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
    }

    if(sec_tick) {
      //PRINT_INFO("sec_tick...\r\n");
      sec_tick = false;
      sendMessage(MSG_SYSTEM, SOS_CHECK);
      sendMessage(MSG_SYSTEM, PMIC_CHECK);
      sendMessage(MSG_SYSTEM, BACKLIGHT_CHECK);

      gpsCheckFlag = true;
      read_measPPG = true;

      if(cat_m1_Status_FallDetection.fall_detect)
      {
        fallCheckTime++;
      }
      if(fallCheckTime > fall_Check_cycle)
      {
        fallCheckFlag = 1;
        fallCheckTime = 0;
        sendMessage(MSG_SYSTEM, BAND_ALERT);
      }
      pressCheckTime++;
      if(pressCheckTime >= 1)
      {
        pressCheckFlag = 1;
        pressCheckTime = 0;
      }
      pressCheckStartTime++;
      if(pressCheckStartTime >= 7)
      {
        pressCheckStartFlag = 1;
        pressCheckStartTime = 0;
      }
    }

    bLevelCtrlTimCount = 0;
    // change parameter val
    if(now_bLevel != ehg.set_bLevel){
      now_bLevel = ehg.set_bLevel;
  //    HAL_Delay(100);
      ST7789_brightness_setting(now_bLevel);
    }
#endif
    osDelay(1);
  }
  /* USER CODE END secTimerTask */
}

/* USER CODE BEGIN Header_StartCheckINTTask */
/**
* @brief Function implementing the checkINTTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartCheckINTTask */
void StartCheckINTTask(void *argument)
{
  /* USER CODE BEGIN checkINTTask */
  message_t recvMsg;
  
  while(!pmicInitFlag){
    osDelay(10);
  }
  double before_falling_pressure[PRESSURE_VAL_LEN] = {0,};
  double after_falling_pressure[PRESSURE_VAL_LEN] = {0,};

  PRINT_INFO("StartCheckINTTask\r\n");

  /* Infinite loop */
  for(;;)
  {
    if (osMessageQueueGetCount(intQueueHandle) > 0)
    {
      if (osMessageQueueGet(intQueueHandle, &recvMsg, 0, 0) == osOK)
      {
        switch(recvMsg.msgType) {
          case INT_HOME_BTN:
            printf("Recv INT_HOME_BTN\r\n");
            if(ehg.occured_HOMEBTNInterrupt == 1){
            	ehg.occured_HOMEBTNInterrupt = 0;
            	ehg.brightness_count = 0;
            	if(ehg.flashlightOn){
            		ehg.flashlightOn = 0;
            		ehg.set_bLevel = ehg.before_bLevel; // turn off flash light : brightness
            	}
              sendMessage(MSG_GUI, HOME_SCREEN);

            	ST7789_brightness_setting(ehg.before_bLevel);

            	// cat_m1_Status_FallDetection.fall_detect = 0;
            	memset(&cat_m1_Status_FallDetection, 0, sizeof(cat_m1_Status_FallDetection));

            	fallCheckTime = 0;

            	sendSOSFlag = 0;
          		fallCheckTime = 0;

#if defined(nRF9160_Fall_Difference_Value_Send)
            	magnitude = 0;
#endif
            }
            break;
        case INT_TOUCH:
          printf("Recv INT_TOUCH\r\n");
          ehg.occurred_touchInterrupt = 0;
          ehg.brightness_count = 0;
          break;
        case INT_PMIC_BTN:
          printf("Recv INT_PMIC_BTN\r\n");

          // PMIC interrupt occur => emergency signal send to Web (CATM1)
          if(ehg.occurred_PMICBUTTInterrupt){
            if (cat_m1_Status.gpsChecking)
            {
              nrf9160_Stop_gps();
            }
            // change screen
            ehg.before_bLevel = ehg.set_bLevel;
            ST7789_brightness_setting(16);
            ehg.brightness_count = 0;
            sendMessage(MSG_GUI, SOS_ALERT);
            // haptic
            ehg.haptic_SOS = 1;
            //      // send SOS MQTT
            //      cat_m1_Status_BandAlert.bid = deviceID;
            //    cat_m1_Status_BandAlert.type = 6;
            //    cat_m1_Status_BandAlert.value = 1;
            //    send_Status_BandAlert(&cat_m1_Status_BandAlert);
            //    catM1MqttDangerMessage = 1;
            //    gpsFlag = true;
            sendSOSFlag = 1;

            ehg.occurred_PMICBUTTInterrupt = 0;
          }
          break;

        case INT_IMU1:
          printf("Recv INT_IMU1\r\n");
          break;
        case INT_PRESS:
          printf("Recv INT_PRESS\r\n");
          break;
        case INT_MAG:
          printf("Recv INT_MAG\r\n");
          break;
        case INT_IMU:
          printf("Recv INT_IMU\r\n");
          break;
        case INT_LTE_GNSS_WKUP:
          printf("Recv INT_LTE_GNSS_WKUP\r\n");
          break;
        case INT_PMIC:
          printf("Recv INT_PMIC\r\n");
          break;
        case INT_IMU2:
          printf("Recv INT_IMU2\r\n");
          break;
        case INT_TEMP:
          printf("Recv INT_TEMP\r\n");
          break;

        }
      }
    }

    osDelay(1);
  }
  /* USER CODE END checkINTTask */
}

/* USER CODE BEGIN Header_StartDATATask */
/**
* @brief Function implementing the dataTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartDATATask */
void StartDATATask(void *argument)
{
  /* USER CODE BEGIN dataTask */
  while(!pmicInitFlag){
    osDelay(10);
  }

  PRINT_INFO("StartDATATask\r\n");

  /* Infinite loop */
  for(;;)
  {
    receive_response();// Cat-M1 Buffer parsing
    osDelay(10);
  }
  /* USER CODE END dataTask */
}

/* USER CODE BEGIN Header_StartMsgTask */
/**
* @brief Function implementing the msgHandleTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartMsgTask */
void StartMsgTask(void *argument)
{
  /* USER CODE BEGIN msgHandleTask */
  message_t recvMsg;

  while(!pmicInitFlag){
    osDelay(10);
  }
  PRINT_INFO("StartMsgTask\r\n");

  /* Infinite loop */
  for(;;)
  {
    if (osMessageQueueGetCount(msgQueueHandle) > 0)
    {
      if (osMessageQueueGet(msgQueueHandle, &recvMsg, 0, 0) == osOK)
      {
        switch(recvMsg.msgType) {
          case BACKLIGHT_CHECK:
            printf("Recv BACKLIGHT_CHECK\r\n");
        		// turn on LCD backlight (in screenOnTime, active only one)
            if(ehg.brightness_count == 0){
              if(backlightTurnONCheck == 0){ // => occurred touch backlight bug
                ST7789_brightness_setting(ehg.set_bLevel);
                backlightTurnONCheck = 1;
              }
              ehg.brightness_count++;
              //now_sleepmode = 0;
            }
            else if(ehg.brightness_count < ehg.screenOnTime){
              ehg.brightness_count++;
            }
            // turn off LCD backlight (out of screenOnTime)
            else if(ehg.brightness_count >= ehg.screenOnTime){
              ST7789_brightness_setting(0);
              backlightTurnONCheck = 0;
              sendMessage(MSG_GUI, BLACK_SCREEN);
              //osDelay(100);
              //now_sleepmode = 1;
            }

            break;
          case PMIC_CHECK:
            printf("Recv PMIC_CHECK\r\n");
            bool pmicBATTERR = false;

            if(pmicSOCRead(&batterylevel) != 0x00){ // occur err
              //MX_I2C3_Init(); // occur err...
              haptic_check_temp = 4;
              pmicBATTERR = 1;
            }
            
            if(!pmicBATTERR) {
              haptic_check_temp = 5;
              // update Battery value
              if(ehg.battVal != batterylevel){
                ehg.battVal = batterylevel;
                //myBatteryprogress_container.changeBATTVal();
              }
            
              // check and update Battery Charging value
              //ehg.isCharging = isBATTCharging();
              uint8_t chargingStatus = (uint8_t)isBATTCharging();
              if(chargingStatus != 0xFF && ehg.battVal<100) {
                bool isCharging_Now = false;
                if(chargingStatus == 1) isCharging_Now = true;
                if(ehg.isCharging != isCharging_Now) {
                  ehg.isCharging = isCharging_Now;
                  if(ehg.isCharging){
                    //myBatteryprogress_container.batteryCharging();
                    sendMessage(MSG_GUI, CHARGE_SCREEN);
            
                    ehg.brightness_count = 0;
                    //ppgMeasFlag = 0;
                  }
                  else{
                    //myBatteryprogress_container.batteryNotCharging();
                    sendMessage(MSG_GUI, UNCHARGE_SCREEN);
                    ehg.brightness_count = 0;
                    //ppgMeasFlag = 1;
                  }
                }
              }
              else if(ehg.battVal == 100 && ehg.isCharging == true){ // charging finish
                ehg.isCharging = false;
                sendMessage(MSG_GUI, UNCHARGE_SCREEN);
                ehg.brightness_count = 0;
              }
            }
            break;
          case SOS_CHECK:
            printf("Recv SOS_CHECK\r\n");
            if(sendSOSFlag == 1)
            {
              SOSCheckTime++;
              ehg.brightness_count = 0;
            }
//            else {
//              if(ehg.brightness_count == 0) {
//                if(backlightTurnONCheck == 0) { // => occurred touch backlight bug
//                  ST7789_brightness_setting(ehg.set_bLevel);
//                  backlightTurnONCheck = 1;
//                }
//                ehg.brightness_count++;
//                //now_sleepmode = 0;
//              }
//              else if(ehg.brightness_count < ehg.screenOnTime) {
//                ehg.brightness_count++;
//              }
//              // turn off LCD backlight (out of screenOnTime)
//              else if(ehg.brightness_count >= ehg.screenOnTime) {
//                ST7789_brightness_setting(0);
//                backlightTurnONCheck = 0;
//                sendMessage(MSG_GUI, BLACK_SCREEN);
//                osDelay(100);
//                //now_sleepmode = 1;
//              }
//              //pre_brightness_count = brightness_count;
//            }
            
            if(SOSCheckTime > SOS_Check_cycle){
              sendMessage(MSG_SYSTEM, SOS_SEND_CHECK);
              sendSOSFlag = 0;
              SOSCheckTime = 0;
            }
            break;
          case SOS_SEND_CHECK:
            printf("Recv SOS_SEND_CHECK\r\n");
            if (cat_m1_Status.gpsChecking)
            {
              nrf9160_Stop_gps();
            }
            sendSOSFlag = 0;
            SOSCheckTime = 0;
            // haptic
            ehg.haptic_SOS = 1;
            // send SOS MQTT
            cat_m1_Status_BandAlert.bid = ehg.deviceID;
            cat_m1_Status_BandAlert.type = 6;
            cat_m1_Status_BandAlert.value = 1;
            send_Status_BandAlert(&cat_m1_Status_BandAlert);
            catM1MqttDangerMessage = 1;

            ehg.gpsFlag = true;
            break;
          case IMU_CHECK:
            printf("Recv IMU_CHECK\r\n");
            if(cat_m1_Status_FallDetection.fall_detect)
            {
              fallCheckTime++;
            }
            if(fallCheckTime > fall_Check_cycle)
            {
              fallCheckFlag = 1;
              fallCheckTime = 0;
              sendMessage(MSG_SYSTEM, BAND_ALERT);
            }
            pressCheckTime++;
            if(pressCheckTime >= 1)
            {
              pressCheckFlag = 1;
              pressCheckTime = 0;
            }
            pressCheckStartTime++;
            if(pressCheckStartTime >= 7)
            {
              pressCheckStartFlag = 1;
              pressCheckStartTime = 0;
            }
            break;

          case BAND_ALERT:
            printf("Recv BAND_ALERT\r\n");
            BandAlert();
            break;
        }
      }
    }


    osDelay(1);
  }
  /* USER CODE END msgHandleTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

