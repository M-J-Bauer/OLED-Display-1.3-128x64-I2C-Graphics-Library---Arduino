//==========   F L A S H   M E M O R Y   D A T A   R E A D   F U N C T I O N   ==========
/* 
 * Function:  PGM_ReadData()
 *
 * Copy data from flash program memory to an array in data memory (SRAM).
 * Target platform is any 8-bit AVR device, e.g. ATmega328P, ATmega32U4, etc.
 *
 * Entry args:  src    =  address of source data in program memory
 *              dest   =  address of destination array in data memory
 *              nbytes =  number of bytes to be copied
 * 
 * The macro pgm_read_byte() is defined in header file avr/pgmspace.h
 * which must be #included in source files which call this function.
 *
 * Flash memory data is declared and initialized as in this example:
 * const char array_name[] PROGMEM = { k0, k1, k2, ... kn };
 */
 
#include <avr/io.h>
#include <avr/pgmspace.h> 
 
 
void  PGM_ReadData(const uint8 *src, uint8 *dest, unsigned nbytes)
{
    while (nbytes != 0)
    {
        *dest++ = pgm_read_byte(src++);
        --nbytes;
    }
}
