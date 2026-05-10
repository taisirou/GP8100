/*!
  * @file GP81XX.h
  * @brief P8101
  * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
  * @license     The MIT License (MIT)
  * @author      [Baikunlin](kunlin.bai@dfrobot.com)
  * @version  V1.0
  * @date  2023-02-10
  * @url https://github.com/DFRobot/DFRobot_GP85XX
  */


#ifndef _GP81XX_H_
#define _GP81XX_H_

#include "Arduino.h"
#include "Wire.h"

#ifdef ENABLE_DBG
#define DBG(...) {Serial.print("[");Serial.print(__FUNCTION__); Serial.print("(): "); Serial.print(__LINE__); Serial.print(" ] "); Serial.println(__VA_ARGS__);}
#else
#define DBG(...)
#endif
#define GP81XX_CONFIG_CURRENT_REG            uint8_t(0x02)

class GP81XX
{
  public:
    
    /**
     * @fn DFRobot_GP85XX
     * @brief Constructor 
     * @return None
     */
    GP81XX();
  
  private:
  
};
/**************************************************************************
                       PWM转0-5V/VCC 模拟电压模块(GP8101)
 **************************************************************************/
class GP8101: public GP81XX
{
  public:
    typedef enum{
      eOutputRange5V = 0,
      eOutputRange10V= 1,
    }eOutPutRange_t;
    
    /**
     * @fn begin
     * @param pin PWM出输出接口
     * @brief 初始化函数
     */
	void begin(uint8_t pin);
  
    /**
     * @fn setDACOutRange
     * @brief 设置DAC输出范围
     * @param range DAC输出范围
     * @n     eOutputRange5V(0-5V)
     * @n     eOutputRange10V(0-10V)
     * @return NONE
     */	
  void begin(uint8_t pin0,uint8_t pin1);
  
    /**
     * @fn setDACOutRange
     * @brief 设置DAC输出范围
     * @param range DAC输出范围
     * @n     eOutputRange5V(0-5V)
     * @n     eOutputRange10V(0-10V)
     * @return NONE
     */	
    void setDACOutRange(eOutPutRange_t range);
  
    /**
     * @fn setDACOutVoltage
     * @brief 设置输出DAC值
     * @param data 需要输出的电压值
     * @return NONE
     */
    void setDACOutVoltage(uint16_t, uint8_t channel);
	
	/**
     * @fn sendData
     * @brief 设置PWM占空比
     * @param data 需要设置的占空比(0-255),ESP32和ESP8266为：(0-8191)
     * @return NONE
     */
	void sendData(uint16_t data, uint8_t channel);
  
    private:
  
  uint16_t _voltage = 0;
	uint16_t _frequency = 2000;
	uint8_t _pin0;
	uint8_t _pin1;  
};

#endif