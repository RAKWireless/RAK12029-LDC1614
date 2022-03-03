| <center><img src="./assets/rakstar.jpg" alt="RAKstar" width=25%></center>  | ![RAKWireless](./assets/RAK-Whirls.png) | [![Build Status](https://github.com/RAKWireless/RAK12029-LDC1614/workflows/RAK%20Library%20Build%20CI/badge.svg)](https://github.com/RAKWireless/RAK12029-LDC1614/actions) |
| -- | -- | -- |

# <RAK12029>

LDC1614 is the inductor chip of Texas Instruments This library provides basic support for configuring functions and reading data.

[*RAKwireless <RAK12029> <Inductive>*](https://store.rakwireless.com/products/rak12029)


# Documentation

* **[Product Repository](https://github.com/RAKWireless/RAK12029-LDC1614)** - Product repository for the RAKWireless RAK12029 Inductive module.
* **[Documentation](https://docs.rakwireless.com/Product-Categories/WisBlock/RAK12029/Overview/)** - Documentation and Quick Start Guide for the RAK12029 Inductive module.

# Installation

In Arduino IDE open Sketch->Include Library->Manage Libraries then search for RAK12029.    

In PlatformIO open PlatformIO Home, switch to libraries and search for RAK12029. 
Or install the library project depend by adding 

```log
lib_deps = rakwireless/RAKwireless LDC1614 Inductive library
```
into **`platformio.ini`**

For manual installation download the archive, unzip it and place the RAK12029-LDC1614-Library folder into the library directory.    
In Arduino IDE this is usually <arduinosketchfolder>/libraries/    
In PlatformIO this is usually <user/.platformio/lib>     

# Usage

The library provides an inductance class that allows you to communicate with ldc1614 and get the chip data,Check out the examples how to get the chip data.

## This class provides the following methods:
**RAK12029_LDC1614_Inductive(u8 IIC_ADDR = DEFAULT_IIC_ADDRESS);**    
Constructor for Inductive interface,Initialize object.
Parameters:    

| Direction | Name | Function |
| --------- | ---- | :------- |
| in        | IIC_ADDR | Hardware IIC Address,The  default address is 0x2A |
| return    |          | none                                              |

**s32 LDC1614_init();**
IIC initialization.   
Parameters:    

| Direction | Name | Function                                                     |
| --------- | ---- | ------------------------------------------------------------ |
| return    |      | If the LDC1614 initialization succeeds return true else return false |

**s32 LDC1614_get_channel_result(u8 channel, u32 *result);**
read the raw channel result from register.     
Parameters:    

| Direction | Name | Function |
| --------- | ---- | -------- |
| in          | channel | LDC1614 has total four channels,The value ranges from 0 to 3 |
| out         | result | result raw data |
| return | | If the configuration is successful, return 0, otherwise return something else |

**s32 LDC1614_set_conversion_time(u8 channel, u16 value);**
set conversion interval time. 
Parameters:    

| Direction | Name | Function |
| --------- | ---- | -------- |
| in        | channel | LDC1614 has total four channels,The value ranges from 0 to 3 |
| in        | value   | the value to be set |
| return |  | If the configuration is successful, return 1, otherwise return 0 |

**s32 LDC1614_set_LC_stabilize_time(u8 channel);**
Before conversion,wait LC sensor stabilize for a short time  
Parameters:    

| Direction | Name | Function |
| --------- | ---- | -------- |
| in        | channel | LDC1614 has total four channels,The value ranges from 0 to 3 |
| return |  | If the configuration is successful, return 1, otherwise return 0 |

**s32 LDC1614_set_conversion_offset(u8 channel, u16 value);**
Set conversion offset. 
Parameters:    

| Direction | Name | Function |
| --------- | ---- | -------- |
| in        | channel | LDC1614 has total four channels,The value ranges from 0 to 3 |
| in        | value   | the value to be set                                          |
| return    |         | If the configuration is successful, return 1, otherwise return 0 |

**u32 LDC1614_get_sensor_status();**
 Get sensor status.  
Parameters:    

| Direction | Name | Function |
| --------- | ---- | -------- |
|  return | | return the register data |

**s32 LDC1614_set_ERROR_CONFIG(u16 value);**
Error output config. 
Parameters:    

| Direction | Name | Function |
| --------- | ---- | -------- |
| in        | value | the value to be set                                          |
| return    |       | If the configuration is successful, return 1, otherwise return 0 |

**s32 LDC1614_set_sensor_config(u16 value);**
Main config part of sensor.Contains select channel、start conversion、sleep mode、sensor activation mode、INT pin disable 
Parameters:    

| Direction | Name | Function |
| --------- | ---- | -------- |
| in        | value | the value to be set                                          |
| return    |       | If the configuration is successful, return 1, otherwise return 0 |

**s32 LDC1614_set_mux_config(u16 value);**    

Channel Multiplexing Configuration.

Parameters:    

| Direction | Name | Function |
| --------- | ---- | -------- |
| in        | value | the value to be set                                          |
| return    |       | If the configuration is successful, return 1, otherwise return 0 |

**s32 LDC1614_reset_sensor();**
Reset sensor. 
Parameters:    

| Direction | Name | Function |
| --------- | ---- | -------- |
|  return | | If the configuration is successful, return 1, otherwise return 0 |

**s32 LDC1614_set_driver_current(u8 channel, u16 value);**
Set input frequency divide and LDC1614_Fref divide.
Parameters:    

| Direction | Name | Function |
| --------- | ---- | -------- |
| in | value | the value to be set                                          |
| return    |       | If the configuration is successful, return 1, otherwise return 0 |

**s32 LDC1614_set_FIN_LDC1614_Fref_DIV(u8 channel);**
Validate LIN frame checksum    
Parameters:    

| Direction | Name | Function |
| --------- | ---- | -------- |
| in        | channel | LDC1614 has total four channels,The value ranges from 0 to 3 |
|  return | | If the configuration is successful, return 1, otherwise return 0 |

**s32 LDC1614_single_channel_config(u8 channel,float inductance,float capatance);**
Configure one channel 
Parameters:    

| Direction | Name | Function |
| --------- | ---- | -------- |
| in        | channel    | LDC1614 has total four channels,The value ranges from 0 to 3 |
| in | inductance | set the inductance (unit-uH) |
| in | capatance | set the capatance  (unit-pf) |
| return | | If the configuration is successful, return 0, otherwise return something else |

**s32 LDC1614_mutiple_channel_config(float inductance,float capatance);**
Configure four channels
Parameters:    

| Direction | Name | Function |
| --------- | ---- | -------- |
| in        | inductance | set the inductance (unit-uH)                                 |
| in        | capatance  | set the capatance  (unit-pf)                                 |
|  return | | If the configuration is successful, return 0, otherwise return something else |
