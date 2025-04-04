/*
 * eHG4_api.h
 *
 *  Created on: Mar 8, 2025
 *      Author: lsj95
 */

#ifndef INC_EHG4_API_H_
#define INC_EHG4_API_H_
#include "main.h"
#include "nrf9160.h"
#include "smartsensor.h"
#include "pmic.h"
#include "mems.h"
#include "bl6133.h"
#include "speaker.h"
#include "st7789.h"
//#include "stm32wb5mmg.h"
//#include "stm32wb_at_ble.h"

typedef enum {
  MSG_SYSTEM = 0x0000,
  MSG_GUI,
  MSG_INT,
  MSG_PPG_MESA,
  MSG_CATM1,
  MSG_TIMER,
} MSG_IDX;

typedef enum {
  TYPE_NONE = 0x0000,

  // System MSG Type
  BACKLIGHT_CHECK,
  SOS_CHECK,
  SOS_SEND_CHECK,
  PMIC_CHECK,
  IMU_CHECK,
  BAND_ALERT,

  //GUI MSG Type
  HOME_SCREEN = 0x0020,
  BLACK_SCREEN,
  CHARGE_SCREEN,
  UNCHARGE_SCREEN,
  FALL_DETECTION,
  TEMP_HOME,
  SOS_ALERT,

  // CatM1 MSG Type
  GPS_CHECK = 0x0040,
  
  // Interrupt MSG Type
  INT_HOME_BTN = 0x0080,
  INT_TOUCH,
  INT_PMIC_BTN,
  INT_IMU,
  INT_IMU1,
  INT_IMU2,
  INT_PRESS,
  INT_MAG,
  INT_LTE_GNSS_WKUP,
  INT_PMIC,
  INT_TEMP,

  // Timer MSG Type
  TIMER_100MS = 0x00A0,
  TIMER_1SEC,
  TIMER_GET_RTC,

} MSG_TYPE;

typedef struct {
  uint8_t set_bLevel; // GUI val ?��?�� // default bright level
  uint8_t before_bLevel;
  uint8_t flashlightOn;

  uint8_t occurred_imuInterrupt;
  uint8_t occurred_PMICBUTTInterrupt;
  uint8_t occured_HOMEBTNInterrupt;
  uint8_t occurred_touchInterrupt;

  // Sensor Parameter.
  uint8_t ssSCD;
  uint16_t ssHr;
  uint16_t ssSpo2;
  uint32_t ssWalk;
  uint32_t imuTemp;
  uint32_t press;
  uint8_t battVal;

  uint8_t canDisplayPPG;
  
  uint8_t hapticFlag;
  uint8_t beforeHaptic;
  uint8_t soundFlag;
  
  uint8_t haptic_SOS;
  
  bool isCharging;

  uint8_t screenOnTime;
  uint8_t brightness_count;

  bool gpsFlag;
  uint32_t deviceID;
} eHG4_Data;

extern eHG4_Data ehg;
extern RTC_TimeTypeDef sTime;
extern RTC_DateTypeDef sDate;

extern cat_m1_Status_t cat_m1_Status;
extern cat_m1_Status_Band_t cat_m1_Status_Band;
extern cat_m1_at_cmd_rst_t cat_m1_at_cmd_rst;
extern cat_m1_Status_FallDetection_t cat_m1_Status_FallDetection;
extern cat_m1_Status_BandAlert_t cat_m1_Status_BandAlert;
extern cat_m1_Status_GPS_Location_t cat_m1_Status_GPS_Location;
extern cat_m1_Status_uuid_t cat_m1_Status_uuid;
extern cat_m1_Status_Fall_Difference_Value_t cat_m1_Status_Fall_Difference_Value;

extern uint8_t nRFCloudFlag;
extern bool cell_locationFlag;
extern uint8_t wpmInitializationFlag;
extern int gpsOffCheckTime;
extern int UartRxRetryTime;
extern int gps_operation_cycle;
extern uint32_t deviceID;
extern uint8_t deviceID_check;
extern uint8_t gpsRSSI_0_1;
extern bool gpsSendFlag;

extern uint8_t fallCheckFlag;
extern uint8_t catM1MqttDangerMessage;
extern int previousRSSIstate;

#if defined(nRF9160_Fall_Difference_Value_Send)
extern double magnitude;
#endif

extern uint8_t haptic_check_temp;
extern uint8_t pressCheckStartFlag;
extern uint8_t pressCheckFlag;

extern struct ssDataEx_format lcd_ssDataEx;


void sendMessage(MSG_IDX id, MSG_TYPE type);

void eHG4_Init(void);
void hapticCheck(void);

void read_ppg();
void measPPG();

void readMems(void);

double getAltitude(double pressure_hPa);
void updateHeightData();
void checkFallDetection();
void BandAlert();

#endif /* INC_EHG4_API_H_ */
