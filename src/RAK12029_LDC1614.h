/**
   @file RAK12029_LDC1614.h
   @author rakwireless.com
   @brief  This is a library for the inductive sensor
   @version 1.0
   @date 2021-11-17
   @copyright Copyright (c) 2021
**/

#ifndef _RAK12029_LDC1614_H
#define _RAK12029_LDC1614_H

#include <Wire.h>
#include <Arduino.h>

#ifndef RAK12029_LDC1614_DEFINES
#define RAK12029_LDC1614_DEFINES

#ifdef ARDUINO_SERIAL
#define Serial_Print SerialUSB
#else
#define Serial_Print Serial
#endif

typedef int s32;
typedef long unsigned int u32;
typedef short s16;
typedef unsigned short u16;
typedef char s8;
typedef unsigned char u8;

#endif

#define DEFAULT_IIC_ADDRESS 0x2A // if the chip ADDR pin is low,the IIC address is 0x2a,if the chip ADDR pin is HIGH,the IIC address is 0x2b

/*Define Register address */
/***************************************************************************/
#define LDC1614_CONVERTION_RESULT_REG_START 0X00
#define LDC1614_set_conversion_time_REG_START 0X08
#define LDC1614_set_conversion_offset_REG_START 0X0C
#define LDC1614_SET_LC_STABILIZE_REG_START 0X10
#define LDC1614_SET_FREQ_REG_START 0X14

#define LDC1614_SENSOR_STATUS_REG 0X18
#define LDC1614_ERROR_CONFIG_REG 0X19
#define LDC1614_SENSOR_CONFIG_REG 0X1A
#define LDC1614_MUL_CONFIG_REG 0X1B
#define LDC1614_SENSOR_RESET_REG 0X1C
#define LDC1614_set_driver_current_REG 0X1E

#define LDC1614_READ_MANUFACTURER_ID 0X7E
#define LDC1614_READ_DEVICE_ID 0X7F
/******************************************************************************/

/******************************************************************************/
/*ERROR bit flag*/
#define LDC1614_UR_ERR2OUT ((u16)1 << 15)
#define LDC1614_OR_ERR2OUT ((u16)1 << 14)
#define LDC1614_WD_ERR2OUT ((u16)1 << 13)
#define LDC1614_AH_ERR2OUT ((u16)1 << 12)
#define LDC1614_AL_ERR2OUT ((u16)1 << 11)
#define LDC1614_UR_ERR2INT ((u16)1 << 7)
#define LDC1614_OR_ERR2INT ((u16)1 << 6)
#define LDC1614_WD_ERR2INT ((u16)1 << 5)
#define LDC1614_AH_ERR2INT ((u16)1 << 4)
#define LDC1614_AL_ERR2INT ((u16)1 << 3)
#define LDC1614_ZC_ERR2INT ((u16)1 << 2)
#define LDC1614_DRDY_2INT  ((u16)1 << 0)

/******************************************************************************/

/***************************************************************************/
/*SENSOR CONFIG bit*/
#define LDC1614_ACTIVE_CHANNEL (((u16)1 << 15) | ((u16)1 << 14))
#define LDC1614_SLEEP_MODE_EN ((u16)1 << 13)
#define LDC1614_RP_OVERRIDE_EN ((u16)1 << 12)
#define LDC1614_SENSOR_ACTIVATE_SEL ((u16)1 << 11)
#define LDC1614_AUTO_AMP_DIS ((u16)1 << 10)
#define LDC1614_REF_CLK_SRC ((u16)1 << 9)
#define LDC1614_INTB_DIS ((u16)1 << 7)
#define LDC1614_HIGH_CURRENT_DRV ((u16)1 << 6)
/*!!!!
  The low bit 0~5 are reserved,must set to 000001.
*/
/***************************************************************************/

// define channel number
#define LDC1614_CHANNEL_0 3
#define LDC1614_CHANNEL_1 2

#define LDC1614_CHANNEL_2 1
#define LDC1614_CHANNEL_3 0

//#define LDC1614_CHANNEL_NUM  2   //LCD 1612
#define LDC1614_CHANNEL_NUM 4 // LCD 1614

/****************************************************
   RAK12029_LDC1614_Inductive  Class
 ***************************************************/
class RAK12029_LDC1614_Inductive
{
  public:
    RAK12029_LDC1614_Inductive(u8 IIC_ADDR = DEFAULT_IIC_ADDRESS);
    ~RAK12029_LDC1614_Inductive() {}
    void IIC_begin()
    {
      Wire.begin();
    }
    s32 IIC_write_byte(u8 reg, u8 byte);
    void IIC_read_byte(u8 reg, u8 *byte);
    void set_iic_addr(u8 IIC_ADDR);
    void IIC_read_16bit(u8 start_reg, u16 *value);
    s32 IIC_write_16bit(u8 reg, u16 value);

    void LDC1614_read_sensor_infomation();
    s32 LDC1614_init();
    s32 LDC1614_get_channel_result(u8 channel, u32 *result);
    s32 LDC1614_set_conversion_time(u8 channel, u16 value);
    s32 LDC1614_set_LC_stabilize_time(u8 channel);
    s32 LDC1614_set_conversion_offset(u8 channel, u16 value);
    u32 LDC1614_get_sensor_status();
    s32 LDC1614_set_ERROR_CONFIG(u16 value);
    s32 LDC1614_set_sensor_config(u16 value);
    s32 LDC1614_set_mux_config(u16 value);
    s32 LDC1614_reset_sensor();
    s32 LDC1614_set_driver_current(u8 channel, u16 value);
    s32 LDC1614_set_FIN_LDC1614_Fref_DIV(u8 channel);
    s32 LDC1614_single_channel_config(u8 channel,float inductance,float capatance);
    s32 LDC1614_mutiple_channel_config(float inductance,float capatance);
    void LDC1614_select_channel_to_convert(u8 channel, u16 *value);
    void LDC1614_set_Rp(u8 channel, float n_kom);
    void LDC1614_set_L(u8 channel, float n_uh);
    void LDC1614_set_C(u8 channel, float n_pf);
    void LDC1614_set_Q_factor(u8 channel, float q);

  private:
    u8 _IIC_ADDR;
    s32 LDC1614_parse_result_data(u8 channel, u32 raw_result, u32 *result);
    s32 LDC1614_sensor_status_parse(u16 value);
    float LDC1614_resistance[LDC1614_CHANNEL_NUM];
    float LDC1614_inductance[LDC1614_CHANNEL_NUM];
    float LDC1614_capacitance[LDC1614_CHANNEL_NUM];
    float LDC1614_Fref[LDC1614_CHANNEL_NUM];
    float LDC1614_Fsensor[LDC1614_CHANNEL_NUM];
    float LDC1614_Q_factor[LDC1614_CHANNEL_NUM];
};

#endif
