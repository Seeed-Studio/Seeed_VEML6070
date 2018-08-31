/*
 * Seeed_VEML6070.h
 * Driver for UV Sensor(VEML6070)
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

#ifndef _SEEED_VE_H
#define _SEEED_VE_H

#include "arduino.h"
#include "Wire.h"


#ifdef ARDUINO_SAMD_VARIANT_COMPLIANCE
  #define SERIAL SerialUSB
#else
  #define SERIAL Serial
#endif


#define CHECK_RESULT(a,b)   do{if(a=b)  {    \
                            SERIAL.print(__FILE__);    \
                            SERIAL.print(__LINE__);   \
                            SERIAL.print(" error code =");  \
                            SERIAL.println(a);                   \
                            return a;   \
                            }}while(0)


typedef int s32;
typedef long unsigned int u32;
typedef unsigned char u8;
typedef unsigned short u16;


#define ENABLE 1
#define DISABLE 0
#define INT_102_STEP    0
#define INT_145_STEP    1


#define IIC_ADDR_H      0X39
#define IIC_ADDR_L      0X38
#define IIC_ADDR_ARA    0X0C




/*Three IIC address,Different functions are implemented by different addresses*/
/* F**K!!! */
#define ENABLE_BIT          0X01
#define INT_ENABLE_BIT      0X20
#define THRES_BIT           0X10

#define INTEGRA_BIT         0X0C

/**Divide UV index into five levels:LOW,MODERATE,HIGH,VERY_HIGH,EXTREME.
 * 
*/
typedef enum 
{
    LOW_LEVEL=0,
    MODERATE, 
    HIGH_LEVEL,
    VERY_HIGH, 
    EXTREME,
} RISK_LEVEL;


/** Tntegration time,When Rset =300kΩ，T=125ms，Rset = 600KΩ,T=-250ms
 * 
 * */
typedef enum
{
    HALF_OF_T=0X00,
    ONE_T=0X04,
    TWO_T=0X08,
    FOUR_T=0X0C,
}integration_time_t;


typedef enum
{
    NO_ERROR=0,
    ERROR_PARAM=-1,
    ERROR_COMM =-2,
    ERROR_OTHERS=-128,
}err_t;


class VEML6070
{
    public:
        VEML6070();
        ~VEML6070(){}
        err_t clear_ack();
        err_t set_cmd_reg();
        err_t read_step(u16 &step);

        err_t init();
        err_t disable();
        err_t enable();
        err_t set_interrupt(bool thre,bool stat);
        err_t set_integra_time(integration_time_t T);
        void wait_for_ready();
        RISK_LEVEL convert_to_risk_level(u16 uvs_step);
    private:
        u8 addr_h;
        u8 addr_l;
        u8 addr_ara;
        u8 cmd_reg;
};








#endif
