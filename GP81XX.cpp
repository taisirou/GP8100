/*!
  * @file GP81XX.h
  * @brief 
  * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
  * @license     The MIT License (MIT)
  * @author      [Baikunlin](kunlin.bai@dfrobot.com)
  * @version  V1.0
  * @date  2023-02-10
  * @url https://github.com/DFRobot/DFRobot_GP85XX
  */
 
#include "GP81XX.h"
#define GP81XX_STORE_TIMING_HEAD            0x02  ///< Store function timing start head
#define GP81XX_STORE_TIMING_ADDR            0x10  ///< The first address for entering store timing
#define GP81XX_STORE_TIMING_CMD1            0x03  ///< The command 1 to enter store timing
#define GP81XX_STORE_TIMING_CMD2            0x00  ///< The command 2 to enter store timing
#define GP81XX_STORE_TIMING_DELAY           10    ///< Store procedure interval delay time: 10ms, more than 7ms
#define PWM_PASSAGG0                        0
#define PWM_PASSAGG1                        1

GP81XX::GP81XX()
{
}


/**************************************************************************
                       PWM转0-5V/VCC 模拟电压模块(GP8101)
 **************************************************************************/
 
void GP8101::begin(uint8_t pin)
{
  _pin0 = pin;
  #if defined(ESP32)  
    ledcSetup(PWM_PASSAGG0, 5000, 13);  ////分辨率为12位，即占空比可选0~8191
	ledcAttachPin(_pin0, PWM_PASSAGG0);
  #elif defined(ESP8266) 
    analogWriteRange(8191);
  #else 
    pinMode(_pin,OUTPUT);
  #endif
}
void GP8101::begin(uint8_t pin0,uint8_t pin1)
{
  _pin0 = pin0;
  _pin1 = pin1;
  #if defined(ESP32)  
  ledcSetup(PWM_PASSAGG0, 5000, 13);  ////分辨率为13位，即占空比可选0~8191
	ledcSetup(PWM_PASSAGG1, 5000, 13);
	ledcAttachPin(_pin0, PWM_PASSAGG0);
	ledcAttachPin(_pin1, PWM_PASSAGG1);
  #elif defined(ESP8266) 
    analogWriteRange(8191);
  #else 
    pinMode(_pin,OUTPUT);
  #endif
}
void GP8101::setDACOutRange(eOutPutRange_t range)
{
   if(range == eOutPutRange_t::eOutputRange5V)
  {
    _voltage = 5000;
  }else{
    _voltage = 10000;
  }
}


void GP8101::setDACOutVoltage(uint16_t data , uint8_t channel)
{
  if(data > _voltage){
    data = _voltage;
  }
  #if defined(ESP32) || defined(ESP8266)
    data = (uint16_t)round(((float)data/_voltage)* 8191);
  #else 
    data = (uint16_t)round(((float)data/_voltage)* 255);
  #endif
  sendData(data, channel); 
}


void GP8101::sendData(uint16_t data, uint8_t channel)
{
  #if defined(ESP32)  
    if(channel == 0){
      ledcWrite(PWM_PASSAGG0, data);
    }else if(channel == 1){
      ledcWrite(PWM_PASSAGG1, data);
    }else{
      ledcWrite(PWM_PASSAGG0, data);
	  ledcWrite(PWM_PASSAGG1, data);
    }
  #else 
    if(channel == 0){
      analogWrite(_pin0, data);
    }else if(channel == 1){
      analogWrite(_pin1, data);
    }else{
    analogWrite(_pin0, data);
	  analogWrite(_pin1, data);
    }
  #endif
}