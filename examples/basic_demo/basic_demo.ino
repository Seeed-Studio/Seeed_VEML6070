/*
 * basic_demo.ino
 * Example for UV Sensor(VEML6070)
 *  
 * Copyright (c) 2018 Seeed Technology Co., Ltd.
 * Website    : www.seeed.cc
 * Author     : downey
 * Create Time: May 2018
 * Change Log :
 *
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "Seeed_VEML6070.h"


/*SAMD core*/
#ifdef ARDUINO_SAMD_VARIANT_COMPLIANCE
  #define SERIAL SerialUSB
#else
  #define SERIAL Serial
#endif

VEML6070 sensor;

char *UV_str[]={"low level","moderate level","high_level","very high","extreme"};

err_t read_UV()
{
    err_t ret=NO_ERROR;
    u16 step;
    sensor.wait_for_ready();
    CHECK_RESULT(ret,sensor.read_step(step));
    SERIAL.print("UV step = ");
    SERIAL.println(step);
    RISK_LEVEL level=sensor.convert_to_risk_level(step);
    
    SERIAL.print("UV level is ");
    SERIAL.println(UV_str[level]);
    SERIAL.println(" ");
    SERIAL.println(" ");
    SERIAL.println(" ");
    return ret;
}

void setup()
{
    SERIAL.begin(115200);
    delay(10);
    SERIAL.println("serial start!!");
    delay(1000);
    if(sensor.init())
    {
      SERIAL.println("init failed!!!");
    }
}


void loop()
{
    if(read_UV())
    {
      SERIAL.print("read UV sensor failed!!");
    }
    //sensor.enable();
    //sensor.disable();
    delay(1000);
}






