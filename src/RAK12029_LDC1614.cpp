/**
   @file RAK12029_LDC1614_Inductive.cpp
   @author rakwireless.com
   @brief  This is a library for the inductive sensor
   @version 1.0
   @date 2021-11-17
   @copyright Copyright (c) 2021
**/

#include "RAK12029_LDC1614.h"
#include "math.h"

/**@brief read sensor's information
 * */
void RAK12029_LDC1614_Inductive::LDC1614_read_sensor_infomation()
{
  u16 value = 0;
  IIC_read_16bit(LDC1614_READ_MANUFACTURER_ID, &value);
  Serial.print("manufacturer id =0x");
  Serial.println(value, HEX);
  IIC_read_16bit(LDC1614_READ_DEVICE_ID, &value);
  Serial.print("DEVICE id =0x");
  Serial.println(value, HEX);
  return;
}

/**@brief constructor,support set IIC addr,default iic addr is 0x2a.
 * */
RAK12029_LDC1614_Inductive::RAK12029_LDC1614_Inductive(u8 IIC_ADDR)
{
  set_iic_addr(IIC_ADDR);
}

/**@brief config sensor
   @return 0:succeeded
 * */
s32 RAK12029_LDC1614_Inductive::LDC1614_init()
{
  /*Start IIC communication!*/
  IIC_begin();
  return 0;
  /*reset sensor*/

}

/**@brief Configure one channel and set inductance、capatance
   @param channel LDC1614 has total four channels.
   @param set the inductance unit-uH
   @param set the capatance unit-pf
   @return If the configuration is successful, return 0, otherwise return something else
 * */
s32 RAK12029_LDC1614_Inductive::LDC1614_single_channel_config(u8 channel, float inductance, float capatance)
{
  if (channel >= 4 || channel < 0)
  {
    Serial.println("Incorrect channel number!!!");
    return -2;
  }

  /*Set coil inductor parameter first.*/
  /*20 TURNS*/
  // LDC1614_set_Rp(channel, 15.727);
  //  LDC1614_set_L(channel, 18.147);
  LDC1614_set_L(channel, inductance);
  LDC1614_set_C(channel, capatance);
  // LDC1614_set_Q_factor(channel, 35.97);

  // /*25 TURNS*/
  // LDC1614_set_Rp(LDC1614_CHANNEL_0,24.9);
  // LDC1614_set_L(LDC1614_CHANNEL_0,53.95);
  // LDC1614_set_C(LDC1614_CHANNEL_0,100);
  // LDC1614_set_Q_factor(LDC1614_CHANNEL_0,32.57);

  /*36 TURNS,single layer*/

  // LDC1614_set_Rp(LDC1614_CHANNEL_0,28.18);
  // LDC1614_set_L(LDC1614_CHANNEL_0,18.56);
  // LDC1614_set_C(LDC1614_CHANNEL_0,100);
  // LDC1614_set_Q_factor(LDC1614_CHANNEL_0,43.25);

  /*40 TURNS*/
  // LDC1614_set_Rp(LDC1614_CHANNEL_0,57.46);
  // LDC1614_set_L(LDC1614_CHANNEL_0,85.44);
  // LDC1614_set_C(LDC1614_CHANNEL_0,100);
  // LDC1614_set_Q_factor(LDC1614_CHANNEL_0,40.7);

  if (LDC1614_set_FIN_LDC1614_Fref_DIV(channel))
  {
    return -1;
  }

  LDC1614_set_LC_stabilize_time(channel);

  /*Set conversion interval time*/
  LDC1614_set_conversion_time(channel, 0x0546);

  /*Set driver current!*/
  LDC1614_set_driver_current(channel, 0xa000);

  /*single conversion*/
  LDC1614_set_mux_config(0x20c);
  /*start channel 0*/
  u16 config = 0x1401;
  LDC1614_select_channel_to_convert(channel, &config);
  LDC1614_set_sensor_config(config);
  return 0;
}

/**@brief Configure four channels and set inductance、capatance
   @param inductance unit-uH
   @param capatance unit-pf
   @return If the configuration is successful, return 0, otherwise return something else
 * */
s32 RAK12029_LDC1614_Inductive::LDC1614_mutiple_channel_config(float inductance, float capatance)
{
  /*Set coil inductor parameter first.*/
  /*20 TURNS*/
  // LDC1614_set_Rp(LDC1614_CHANNEL_0, 15.727);
  LDC1614_set_L(LDC1614_CHANNEL_0, inductance); // 13.000
  LDC1614_set_C(LDC1614_CHANNEL_0, capatance);  // 100
  // LDC1614_set_Q_factor(LDC1614_CHANNEL_0, 35.97);

  /*20 TURNS*/
  // LDC1614_set_Rp(LDC1614_CHANNEL_1, 15.727);
  LDC1614_set_L(LDC1614_CHANNEL_1, inductance);
  LDC1614_set_C(LDC1614_CHANNEL_1, capatance);
  // LDC1614_set_Q_factor(LDC1614_CHANNEL_1, 35.97);

  /*20 TURNS*/
  // LDC1614_set_Rp(LDC1614_CHANNEL_2, 15.727);
  LDC1614_set_L(LDC1614_CHANNEL_2, inductance);
  LDC1614_set_C(LDC1614_CHANNEL_2, capatance);
  // LDC1614_set_Q_factor(LDC1614_CHANNEL_2, 35.97);

  /*20 TURNS*/
  // LDC1614_set_Rp(LDC1614_CHANNEL_3, 15.727);
  LDC1614_set_L(LDC1614_CHANNEL_3, inductance);
  LDC1614_set_C(LDC1614_CHANNEL_3, capatance);
  // LDC1614_set_Q_factor(LDC1614_CHANNEL_3, 35.97);

  if (LDC1614_set_FIN_LDC1614_Fref_DIV(LDC1614_CHANNEL_0))
  {
    return -1;
  }
  if (LDC1614_set_FIN_LDC1614_Fref_DIV(LDC1614_CHANNEL_1))
  {
    return -1;
  }
  if (LDC1614_set_FIN_LDC1614_Fref_DIV(LDC1614_CHANNEL_2))
  {
    return -1;
  }
  if (LDC1614_set_FIN_LDC1614_Fref_DIV(LDC1614_CHANNEL_3))
  {
    return -1;
  }

  /* 16*38/LDC1614_Fref=30us ,wait 30us for LC sensor stabilize before initiation of a conversion.*/
  LDC1614_set_LC_stabilize_time(LDC1614_CHANNEL_0);
  LDC1614_set_LC_stabilize_time(LDC1614_CHANNEL_1);

  /*********LDC1614**************/
  LDC1614_set_LC_stabilize_time(LDC1614_CHANNEL_2);
  LDC1614_set_LC_stabilize_time(LDC1614_CHANNEL_3);

  /*Set conversion interval time*/
  LDC1614_set_conversion_time(LDC1614_CHANNEL_0, 0x0546);
  LDC1614_set_conversion_time(LDC1614_CHANNEL_1, 0x0546);
  /*********LDC1614**************/
  LDC1614_set_conversion_time(LDC1614_CHANNEL_2, 0x0546);
  LDC1614_set_conversion_time(LDC1614_CHANNEL_3, 0x0546);

  /*Set driver current!*/
  LDC1614_set_driver_current(LDC1614_CHANNEL_0, 0xa000);
  LDC1614_set_driver_current(LDC1614_CHANNEL_1, 0xa000);
  /*********LDC1614**************/
  LDC1614_set_driver_current(LDC1614_CHANNEL_2, 0xa000);
  LDC1614_set_driver_current(LDC1614_CHANNEL_3, 0xa000);

  /*mutiple conversion*/
  LDC1614_set_mux_config(0xC20c); // LDC 1614 four channel config
  // LDC1614_set_mux_config(0x820c);   //LDC 1612 two channel config
  // LDC1614_set_mux_config(0x20c);    //SINGLE channel config
  /*start channel 0*/
  LDC1614_set_sensor_config(0x1401);
  // u16 config = 0x1401;
  // LDC1614_select_channel_to_convert(0, &config);
  return 0;
}

/**@brief parse the data which read from data register.
   @param channel LDC1614 has total four channels.
   @param raw_result the raw data which read from data register,it contains error codes and sensor value;
   @return If the configuration is successful, return 0, otherwise return something else
 * */
s32 RAK12029_LDC1614_Inductive::LDC1614_parse_result_data(u8 channel, u32 raw_result, u32 *result)
{
  u8 value = 0;
  *result = raw_result & 0x0fffffff;
  if (0xfffffff == *result)
  {
    Serial.printf("the channel%d can't detect coil Coil LDC1614_inductance!!!\r\n", 4 - channel); //
    *result = 0;
    return -1;
  }
  else if (0 == *result)
  {
    Serial.println("result is none,please reset the sensor!!!");
  }
  value = raw_result >> 24;
  if (value & 0x80)
  {
    Serial.print("channel ");
    Serial.print(channel);
    Serial.println(": ERR_UR-Under range error!!!");
  }
  if (value & 0x40)
  {
    Serial.print("channel ");
    Serial.print(channel);
    Serial.println(": ERR_OR-Over range error!!!");
  }
  if (value & 0x20)
  {
    Serial.print("channel ");
    Serial.print(channel);
    Serial.println(": ERR_WD-Watch dog timeout error!!!");
  }
  if (value & 0x10)
  {
    Serial.print("channel ");
    Serial.print(channel);
    Serial.println(": ERR_AE-error!!!");
  }
  return 0;
}

/**@brief read the raw channel result from register.
   @param channel LDC1614 has total four channels.
   @param result raw data
   @return If the configuration is successful, return 0, otherwise return something else
 * */
s32 RAK12029_LDC1614_Inductive::LDC1614_get_channel_result(u8 channel, u32 *result)
{
  u32 raw_value = 0;
  if (NULL == result)
  {
    return -1;
  }
  if (channel >= 4 || channel < 0)
  {
    Serial.println("Incorrect channel number!!!");
    return -2;
  }
  u16 value = 0;
  IIC_read_16bit(LDC1614_CONVERTION_RESULT_REG_START + channel * 2, &value);
  raw_value |= (u32)value << 16;
  IIC_read_16bit(LDC1614_CONVERTION_RESULT_REG_START + channel * 2 + 1, &value);
  raw_value |= (u32)value;
  LDC1614_parse_result_data(channel, raw_value, result);
  return 0;
}

/**@brief set conversion interval time.
   @param channel LDC1614 has total four channels.
   @param result The value to be set.
   @return If the configuration is successful, return 1, otherwise return 0
 * */
s32 RAK12029_LDC1614_Inductive::LDC1614_set_conversion_time(u8 channel, u16 value)
{
  return IIC_write_16bit(LDC1614_set_conversion_time_REG_START + channel, value);
}

/**@brief set conversion offset.
   @param channel LDC1614 has total four channels.
   @param result The value to be set.
   @return If the configuration is successful, return 1, otherwise return 0
 * */
s32 RAK12029_LDC1614_Inductive::LDC1614_set_conversion_offset(u8 channel, u16 value)
{
  return IIC_write_16bit(LDC1614_SET_LC_STABILIZE_REG_START + channel, value);
}

/**@brief Before conversion,wait LC sensor stabilize for a short time.
   @param channel LDC1614 has total two channels.
   @param result The value to be set.
   @return If the configuration is successful, return 1, otherwise return 0
 * */
s32 RAK12029_LDC1614_Inductive::LDC1614_set_LC_stabilize_time(u8 channel)
{
  u16 value = 0;
  value = 30;
  return IIC_write_16bit(LDC1614_SET_LC_STABILIZE_REG_START + channel, value);
}

/**@brief set input frequency divide and LDC1614_Fref divide.
   @param channel LDC1614 has total four channels.
   @param FIN_DIV FIN input divide.
   @param LDC1614_Fref_DIV LDC1614_Fref,reference frequency of sensor.
   @return If the configuration is successful, return 1, otherwise return 0
 * */
s32 RAK12029_LDC1614_Inductive::LDC1614_set_FIN_LDC1614_Fref_DIV(u8 channel)
{
  u16 value;
  u16 FIN_DIV, LDC1614_Fref_DIV;

  LDC1614_Fsensor[channel] = 1 / (2 * 3.14 * sqrt(LDC1614_inductance[channel] * LDC1614_capacitance[channel] * pow(10, -18))) * pow(10, -6);
  // Serial.print("LDC1614_Fsensor =");
  // Serial.println(LDC1614_Fsensor[channel]);

  FIN_DIV = (u16)(LDC1614_Fsensor[channel] / 8.75 + 1);

  if (LDC1614_Fsensor[channel] * 4 < 40)
  {
    LDC1614_Fref_DIV = 2;
    LDC1614_Fref[channel] = 40 / 2;
  }
  else
  {
    LDC1614_Fref_DIV = 4;
    LDC1614_Fref[channel] = 40 / 4;
  }

  value = FIN_DIV << 12;
  value |= LDC1614_Fref_DIV;
  return IIC_write_16bit(LDC1614_SET_FREQ_REG_START + channel, value);
}

/**@brief Error output config.
   @param result The value to be set.
   @return If the configuration is successful, return 1, otherwise return 0
 * */
s32 RAK12029_LDC1614_Inductive::LDC1614_set_ERROR_CONFIG(u16 value)
{
  return IIC_write_16bit(LDC1614_ERROR_CONFIG_REG, value);
}

/**@brief Channel Multiplexing Configuration
   @param result The value to be set.
   @return If the configuration is successful, return 1, otherwise return 0
 * */
s32 RAK12029_LDC1614_Inductive::LDC1614_set_mux_config(u16 value)
{
  return IIC_write_16bit(LDC1614_MUL_CONFIG_REG, value);
}

/**@brief reset sensor.
   @return If the configuration is successful, return 1, otherwise return 0
 * */
s32 RAK12029_LDC1614_Inductive::LDC1614_reset_sensor()
{
  return IIC_write_16bit(LDC1614_SENSOR_RESET_REG, 0x8000);
}

/**@brief set drive current of sensor.
   @param result The value to be set.
   @return If the configuration is successful, return 1, otherwise return 0
 * */
s32 RAK12029_LDC1614_Inductive::LDC1614_set_driver_current(u8 channel, u16 value)
{
  return IIC_write_16bit(LDC1614_set_driver_current_REG + channel, value);
}

/**@brief Main config part of sensor.Contains select channel、start conversion、sleep mode、sensor activation mode、INT pin disable ..
   @param result The value to be set.
   @return If the configuration is successful, return 1, otherwise return 0
 * */
s32 RAK12029_LDC1614_Inductive::LDC1614_set_sensor_config(u16 value)
{
  return IIC_write_16bit(LDC1614_SENSOR_CONFIG_REG, value);
}

/**@brief select channel to convert

 * */
void RAK12029_LDC1614_Inductive::LDC1614_select_channel_to_convert(u8 channel, u16 *value)
{
  switch (channel)
  {
    case 0:
      *value &= 0x3fff;
      break;
    case 1:
      *value &= 0x7fff;
      *value |= 0x4000;
      break;
    case 2:
      *value &= 0xbfff;
      *value |= 0x8000;
      break;
    case 3:
      *value |= 0xc000;
      break;
  }
}

/**@brief set the channel and config the resistance.
   @param channel LDC1614 has total four channels.
   @param Set the Rb(resistance unit-kom).
 * */
void RAK12029_LDC1614_Inductive::LDC1614_set_Rp(u8 channel, float n_kom)
{
  LDC1614_resistance[channel] = n_kom;
}

/**@brief set the channel and config the inductance.
   @param channel LDC1614 has total four channels.
   @param Set the L(inductance unit-uH).
 * */
void RAK12029_LDC1614_Inductive::LDC1614_set_L(u8 channel, float n_uh)
{
  LDC1614_inductance[channel] = n_uh;
}

/**@brief set the channel and config the capacitance.
   @param channel LDC1614 has total four channels.
   @param Set the C(capatance unit-pf).
 * */
void RAK12029_LDC1614_Inductive::LDC1614_set_C(u8 channel, float n_pf)
{
  LDC1614_capacitance[channel] = n_pf;
}

void RAK12029_LDC1614_Inductive::LDC1614_set_Q_factor(u8 channel, float q)
{
  LDC1614_Q_factor[channel] = q;
}

const char *status_str[] = {"conversion under range error", "conversion over range error",
                            "watch dog timeout error", "Amplitude High Error",
                            "Amplitude Low Error", "Zero Count Error",
                            "Data Ready", "unread conversion is present for channel 0",
                            " unread conversion is present for Channel 1.",
                            "unread conversion ispresent for Channel 2.",
                            "unread conversion is present for Channel 3."
                           };

/**@brief parse sensor statu data.
 * */
s32 RAK12029_LDC1614_Inductive::LDC1614_sensor_status_parse(u16 value)
{
  u16 section = 0;
  section = value >> 14;
  switch (section)
  {
    case 0:
      Serial.println("Channel 0 is source of flag or error.");
      break;
    case 1:
      Serial.println("Channel 1 is source of flag or error.");
      break;
    /*Only support LDC1614*/
    case 2:
      Serial.println("Channel 2 is source of flag or error.");
      break;
    case 3:
      Serial.println("Channel 3 is source of flag or error.");
      break;
    default:
      break;
  }
  for (u32 i = 0; i < 6; i++)
  {
    if (value & (u16)1 << (8 + i))
    {
      Serial.println(status_str[6 - i]);
    }
  }
  if (value & (1 << 6))
  {
    Serial.println(status_str[6]);
  }
  for (u32 i = 0; i < 4; i++)
  {
    if (value & (1 << i))
    {
      Serial.println(status_str[10 - i]);
    }
  }
}

/**@brief get sensor status.
   @return the register data.
 * */
u32 RAK12029_LDC1614_Inductive::LDC1614_get_sensor_status()
{
  u16 value = 0;
  IIC_read_16bit(LDC1614_SENSOR_STATUS_REG, &value);

  //   Serial.print("status =");
  //   Serial.println(value,HEX);

  LDC1614_sensor_status_parse(value);
  return value;
}

s32 RAK12029_LDC1614_Inductive::IIC_write_byte(u8 reg, u8 byte)
{
  Wire.beginTransmission(_IIC_ADDR);
  Wire.write(reg);
  Wire.write(byte);
  return Wire.endTransmission();
}

s32 RAK12029_LDC1614_Inductive::IIC_write_16bit(u8 reg, u16 value)
{
  Wire.beginTransmission(_IIC_ADDR);
  Wire.write(reg);

  Wire.write((u8)(value >> 8));
  Wire.write((u8)value);
  return Wire.endTransmission();
}

void RAK12029_LDC1614_Inductive::IIC_read_byte(u8 reg, u8 *byte)
{
  Wire.beginTransmission(_IIC_ADDR);
  Wire.write(reg);
  Wire.endTransmission(false);

  Wire.requestFrom(_IIC_ADDR, (u8)1);
  // while (1 != Wire.available());
  if (Wire.available() == 1)
  {
    *byte = Wire.read();
  }
  else
  {
    *byte = 0x00;
  }
}

void RAK12029_LDC1614_Inductive::IIC_read_16bit(u8 start_reg, u16 *value)
{
  u8 val = 0;
  *value = 0;
  Wire.beginTransmission(_IIC_ADDR);
  Wire.write(start_reg);
  Wire.endTransmission(false);

  Wire.requestFrom(_IIC_ADDR, sizeof(u16));
  // while (sizeof(u16) != Wire.available());
  if (Wire.available())
  {
    val = Wire.read();
    *value |= (u16)val << 8;
    val = Wire.read();
    *value |= val;
  }
  else
  {
    *value = 0x0000;
  }
}

void RAK12029_LDC1614_Inductive::set_iic_addr(u8 IIC_ADDR)
{
  _IIC_ADDR = IIC_ADDR;
}
