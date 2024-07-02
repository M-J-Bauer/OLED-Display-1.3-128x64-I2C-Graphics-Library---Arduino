/*
 * File:          OLED_display_avr8_lib.h
 *
 * Overview:      Library for Monochrome Graphic LCD or OLED module, 128 x 64 pixels.
 *
 * Target MCU:    AVR 8-bit MCU family, e.g. ATmega32U4, ATmega328P, etc.
 *
 * Dependencies:  This module links with a low-level driver module supporting the LCD controller
 *                chip-set, which may be "LCD_KS0108_drv.c" (for KS0107/KS0108 chipset),
 *                LCD_ST7920_drv.c (for ST7920 chip), or OLED_SH1106_drv.c (for SH1106 chip).
 *
 * Originated:    2015 M.J. Bauer,  Last Revised: June 2024   [www.mjbauer.biz]
 */
 
#ifndef LCD_GRAPHICS_LIB_H
#define LCD_GRAPHICS_LIB_H

#include <avr/pgmspace.h>  // required for PGM_ReadData() function"

// Include display controller driver file -- HW platform specific
#include "OLED_SH1106_drv.h"  

#ifndef uint8
typedef signed char     int8;
typedef unsigned char   uint8;
typedef signed short    int16;
typedef unsigned short  uint16;
typedef signed long     int32;
typedef unsigned long   uint32;
#endif // uint8

#ifndef bool
typedef unsigned char   bool;
#endif

#ifndef FALSE
#define FALSE  0
#define TRUE   (!FALSE)
#endif

#ifndef NULL
#define NULL ((void *) 0)
#endif

#ifndef HI_BYTE
#define HI_BYTE(w)  (((w) >> 8) & 0xFF)   // Extract high-order byte from unsigned word
#define LO_BYTE(w)  ((w) & 0xFF)          // Extract low-order byte from unsigned word
#define ARRAY_SIZE(a)  (sizeof(a)/sizeof(a[0]))
#define MIN(x,y)       ((x > y)? y: x)
#endif

// Rendering modes for LCD write functions...
#define CLEAR_PIXELS  0
#define SET_PIXELS    1
#define FLIP_PIXELS   2

// Character font styles;  size is cell height in pixels.
// Use one of the font names defined here as the arg value in function: LCD_SetFont(arg).
// Note:  Font size 16 is monospace only -- N/A in proportional.
//        Font size 12 is proportional spacing -- N/A in monospace.
//
enum  Graphics_character_fonts
{
    MONO_8_NORM = 0,   // (0) Mono-spaced font;  char width is 5 pix
    MONO_8_BOLD_X,     // (1) N/A 
    PROP_8_NORM,       // (2) Proportional font;  char width is 3..5 pix
    PROP_8_BOLD_X,     // (3) N/A 

    MONO_12_NORM_X,    // (4) N/A
    MONO_12_BOLD_X,    // (5) N/A
    PROP_12_NORM,      // (6) Proportional font;  char width is 4..7 pix
    PROP_12_BOLD,      // (7) as above, but bold weight

    MONO_16_NORM,      // (8) Mono-spaced font;  char width is 10 pix
    MONO_16_BOLD,      // (9) as above, but bold weight
    PROP_16_NORM_X,    // (10) N/A
    PROP_16_BOLD_X,    // (11) N/A
};


typedef  const unsigned char  bitmap_t;  // Bitmap image is an array of bytes in flash

// Character font data tables are stored in flash program memory...
// This function, defined in pro-micro-periph.c, accesses data in flash PM:
void  PGM_ReadData(const uint8 *src, uint8 *dest, unsigned nbytes);

//---------- Controller low-level functions, defined in driver module -------------------
//
extern  bool  LCD_Init(void);      // LCD controller initialisation
extern  void  LCD_ClearGDRAM();
extern  void  LCD_WriteBlock(uint16 *scnBuf, uint16 x, uint16 y, uint16 w, uint16 h);

//---------- LCD function & macro library (API) -----------------------------------------
//
#define LCD_GetMaxX()       (127)
#define LCD_GetMaxY()       (63)

void    LCD_ClearScreen(void);            // Clear LCD GDRAM and MCU RAM buffers
void    LCD_Mode(uint8 mode);             // Set pixel write mode (set, clear, flip)
void    LCD_PosXY(uint16 x, uint16 y);    // Set graphics cursor position to (x, y)
uint16  LCD_GetX(void);                   // Get graphics cursor pos x-coord
uint16  LCD_GetY(void);                   // Get graphics cursor pos y-coord
void    LCD_SetFont(uint8 font_ID);       // Set font for char or text display
uint8   LCD_GetFont();                    // Get current font ID
void    LCD_PutChar(char uc);             // Show ASCII char at (x, y)
void    LCD_PutText(char *str);           // Show text string at (x, y)
void    LCD_PutDigit(uint8 h);            // Show hex/decimal digit value (1 char)
void    LCD_PutHexByte(uint8 bDat);       // Show hexadecimal byte value (2 chars)

void    LCD_PutDigit_16p(uint8 digit);    // Show decimal digit (16p norm HD)
void    LCD_PutDigit_20p(uint8 d);        // Show decimal digit (20p bold HD)
void    LCD_PutDecimalWord(uint16 val, uint8 fieldSize);  // Show uint16 in decimal
void    LCD_BlockFill(uint16 w, uint16 h);   // Fill area, w x h pixels, at cursor (x, y)
void    LCD_BlockClear(uint16 w, uint16 h);  // Clear area, w x h pixels, at cursor (x, y)
uint8   LCD_PutImage(bitmap_t *image, uint16 w, uint16 h);  // Show bitmap image at (x, y)
uint16 *LCD_ScreenCapture();              // Return a pointer to the screen buffer

// These macros draw various objects at the current graphics cursor position...
#define LCD_PutPixel()           LCD_BlockFill(1, 1)
#define LCD_DrawBar(w, h)        LCD_BlockFill(w, h)
#define LCD_DrawLineHoriz(len)   LCD_BlockFill(len, 1)
#define LCD_DrawLineVert(len)    LCD_BlockFill(1, len)

//---------- Aliases for OLED (or other 128 x 64 pixel display) ----------------------------
//
#define Disp_GetMaxX()      (127)                   // Screen width, pixels
#define Disp_GetMaxY()      (63)                    // Screen height, pixels
#define Disp_Init()         LCD_Init()              // Controller initialisation
#define Disp_ClearScreen()  LCD_ClearScreen()       // Clear GDRAM and MCU RAM buffers
#define Disp_Mode(mode)     LCD_Mode(mode)          // Set pixel write mode (set, clear, flip)
#define Disp_PosXY(x, y)    LCD_PosXY(x, y)         // Set graphics cursor position
#define Disp_GetX()         LCD_GetX()              // Get cursor pos'n x-coord
#define Disp_GetY()         LCD_GetY()              // Get cursor pos'n y-coord
#define Disp_SetFont(font)  LCD_SetFont(font)       // Set font for text
#define Disp_GetFont()      LCD_GetFont()           // Get current font ID
#define Disp_PutChar(c)     LCD_PutChar(c)          // Show ASCII char at (x, y)
#define Disp_PutText(s)     LCD_PutText(s)          // Show text string at (x, y)
#define Disp_PutDigit(d)    LCD_PutDigit(d)         // Show hex/decimal digit (1 char)
#define Disp_PutHexByte(h)  LCD_PutHexByte(h)       // Show hexadecimal byte (2 chars)

#define Disp_PutDigit_16p(d)      LCD_PutDigit_16p(d);      // Show decimal digit (16p norm HD)
#define Disp_PutDigit_20p(d)      LCD_PutDigit_20p(d)       // Show decimal digit (20p bold HD)
#define Disp_PutDecimal(w, n)     LCD_PutDecimalWord(w, n)  // Show uint16 in decimal (n places)
#define Disp_BlockFill(w, h)      LCD_BlockFill(w, h)       // Fill area w x h pixels at (x, y)
#define Disp_BlockClear(w, h)     LCD_BlockClear(w, h);     // Clear area w x h pixels at (x, y)
#define Disp_PutImage(img, w, h)  LCD_PutImage(img, w, h)   // Show bitmap image at (x, y)
#define Disp_ScreenCapture()      LCD_ScreenCapture()       // Return a pointer to the screen buffer

#define Disp_PutPixel()           LCD_BlockFill(1, 1)
#define Disp_DrawBar(w, h)        LCD_BlockFill(w, h)
#define Disp_DrawLineHoriz(len)   LCD_BlockFill(len, 1)
#define Disp_DrawLineVert(len)    LCD_BlockFill(1, len)

#endif  // LCD_GRAPHICS_LIB_H
