/*
 * File:    OLED_SH1106_drv.h
 *
 * Low-level driver functions for monochrome graphic display module, 132 x 64 pixels,
 * customized for SH1106 OLED controller using 2-wire IIC (I2C) MCU interface.
 * This version uses I2C driver functions from module "I2C_master_drv".
 *
 * The SH1106 driver functions work with MJB's GLCD library: LCD_graphics_lib.*
 * and OLED display library: OLED_display_avr8_lib.*
 * Macros (alias's) for OLED display functions are defined in OLED_display_avr8_lib.h.
 * 
 * Originated:    2021,  M.J.Bauer  [www.mjbauer.biz]
 * Last revised:  June 2024, MJB
 *
 */
#ifndef SH1106_OLED_DRV_H
#define SH1106_OLED_DRV_H

#include "I2C_master_drv.h"

#ifndef uint8
typedef signed char         int8;
typedef unsigned char       uint8;
typedef signed short        int16;
typedef unsigned short      uint16;
typedef signed long         int32;
typedef unsigned long       uint32;
#endif // uint8

#ifndef bool
typedef unsigned char       bool;
#endif


// Set the IIC device address here (can be wired for 0x3C or 0x3D)
//
#define SH1106_I2C_ADDRESS  (0x3C<<1)  // (pin SA0 = Low)
/*
#define SH1106_I2C_ADDRESS  (0x3D<<1)  // (pin SA0 = High)
*/

// Function name alias's to support specific MCU I2C driver code:
#define I2C_MasterInit(fclk)        i2c_init(fclk)        // void
#define I2C_MasterStart(addr)       i2c_start(addr)       // 0 => success
#define I2C_MasterStartWait(addr)   i2c_start_wait(addr)  // void
#define I2C_MasterSend(dat)         i2c_write(dat)        // 0 => success
#define I2C_MasterStop()            i2c_stop()            // void

//-------------- SH1106 Command Bytes ------------------
//
#define SH1106_SETCONTRAST 0x81
#define SH1106_DISPLAYALLON_RESUME 0xA4
#define SH1106_DISPLAYALLON 0xA5
#define SH1106_NORMALDISPLAY 0xA6
#define SH1106_INVERTDISPLAY 0xA7
#define SH1106_DISPLAYOFF 0xAE
#define SH1106_DISPLAYON 0xAF
#define SH1106_SETDISPLAYOFFSET 0xD3
#define SH1106_SETCOMPINS 0xDA
#define SH1106_SETVCOMDETECT 0xDB
#define SH1106_SETDISPLAYCLOCKDIV 0xD5
#define SH1106_SETPRECHARGE 0xD9
#define SH1106_SETMULTIPLEX 0xA8

#define SH1106_SETCOLUMNADDRLOW 0x00
#define SH1106_SETCOLUMNADDRHIGH 0x10
#define SH1106_SETSTARTLINE 0x40
#define SH1106_MEMORYMODE 0x20
#define SH1106_PAGEADDR   0xB0
#define SH1106_COMSCANINC 0xC0
#define SH1106_COMSCANDEC 0xC8
#define SH1106_SEGREMAP 0xA0
#define SH1106_CHARGEPUMP 0x8D
#define SH1106_EXTERNALVCC 0x01
#define SH1106_SWITCHCAPVCC 0x02

#define SH1106_MESSAGETYPE_COMMAND 0x80
#define SH1106_MESSAGETYPE_DATA 0x40
#define SH1106_READMODIFYWRITE_START 0xE0
#define SH1106_READMODIFYWRITE_END 0xEE
#define SH1106_MAXSEGMENTSPERWRITE 16
#define SH1106_ROWHEIGHT 8
#define SH1106_NUMBEROF_SEGMENTS 132
#define SH1106_NUMBEROF_PAGES 8

// OLED screen size
#define SH1106_WIDTH_PIXELS   128
#define SH1106_HEIGHT_PIXELS  64

#define OLED_Display_Wake()    SH1106_WriteCommand(SH1106_DISPLAYON)
#define OLED_Display_Sleep()   SH1106_WriteCommand(SH1106_DISPLAYOFF); 


//  SH1106 OLED controller low-level functions defined in the driver module
//
void  SH1106_WriteCommand(uint8 cmd);
void  SH1106_WriteData(uint8 data);
void  SH1106_Init();
void  SH1106_Wake();
void  SH1106_Sleep();
void  SH1106_SetContrast(unsigned level_pc);  // %
void  SH1106_ClearGDRAM();
void  SH1106_WriteBlock(uint16 *scnBuf, uint16 x, uint16 y, uint16 w, uint16 h);
void  SH1106_Test_Pattern();

#endif  // SH1106_OLED_DRV_H
