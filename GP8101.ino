/*!
DFRobot_GP85XXを基にGP8101用に改変しました。
  * @file GP8101outputData.ino
  * @brief 设置输出电压值和范围，将PWM信号转换为1路0--5V或0-10V的模拟电压信号
  * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
  * @license     The MIT License (MIT)
  * @author      [Baikunlin](kunlin.bai@dfrobot.com)
  * @url https://github.com/DFRobot/DFRobot_GP85XX
  */

#include "GP81XX.h"

GP8101 GP8101;
//ピン設定
int pin0 = 25;
int pin1 = 26;

void setup() {
  Serial.begin(115200);
  GP8101.begin(pin0,pin1);
  Serial.println("init succeed");
  /**
   * 0-5V、0-10Vを宣言します。
   * @n     eOutputRange5V(0-5V)
   * @n     eOutputRange10V(0-10V)
   */	
  GP8101.setDACOutRange(GP8101.eOutputRange10V);
  /**
   * GP8101.setDACOutVoltage(値,ch)
   */
  GP8101.setDACOutVoltage(4000,0);
  GP8101.setDACOutVoltage(4000,1);
}

void loop() {
}
