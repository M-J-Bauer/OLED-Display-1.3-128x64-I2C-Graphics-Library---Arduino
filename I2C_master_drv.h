/*************************************************************************
* File:      I2C_master_drv.h  [derived from i2cmaster.h]
* Title:     I2C master library using hardware TWI interface
* Origin:    Peter Fleury <pfleury@gmx.ch>
* Modified:  M.J.Bauer [www.mjbauer.biz] 2024 - added param in i2c_init()
* Compiler:  Microchip/Atmel Studio IDE v7 (AVR-GCC)
* Target:    Any 8-bit AVR device with I2C/TWI periph 
**************************************************************************/
#ifndef _I2CMASTER_H
#define _I2CMASTER_H

#include <avr/io.h>

/** defines the data direction (reading from I2C device) in i2c_start(),i2c_rep_start() */
#define I2C_READ    1

/** defines the data direction (writing to I2C device) in i2c_start(),i2c_rep_start() */
#define I2C_WRITE   0


/**
 @brief initialize the I2C master interace. Needs to be called only once 
 @param  clock_freq_kHz = SCL clock rate, typically 100 or 400 kHz
 @return none
 */
void  i2c_init(unsigned clock_freq_kHz);


/** 
 @brief Terminates the data transfer and releases the I2C bus 
 @return none
 */
void i2c_stop(void);


/** 
 @brief Issues a start condition and sends address and transfer direction 
  
 @param    addr address and transfer direction of I2C device
 @retval   0   device accessible 
 @retval   1   failed to access device 
 */
unsigned char i2c_start(unsigned char addr);


/**
 @brief Issues a repeated start condition and sends address and transfer direction 

 @param   addr address and transfer direction of I2C device
 @retval  0 device accessible
 @retval  1 failed to access device
 */
unsigned char i2c_rep_start(unsigned char addr);


/**
 @brief Issues a start condition and sends address and transfer direction 
   
 If device is busy, use ack polling to wait until device ready 
 @param    addr address and transfer direction of I2C device
 @return   none
 */
void i2c_start_wait(unsigned char addr);

 
/**
 @brief Send one byte to I2C device
 @param    data  byte to be transfered
 @retval   0 write successful
 @retval   1 write failed
 */
unsigned char i2c_write(unsigned char data);


/**
 @brief    read one byte from the I2C device, request more data from device 
 @return   byte read from I2C device
 */
unsigned char i2c_readAck(void);

/**
 @brief    read one byte from the I2C device, read is followed by a stop condition 
 @return   byte read from I2C device
 */
unsigned char i2c_readNak(void);

/** 
 @brief    read one byte from the I2C device
 
 Implemented as a macro, which calls either @ref i2c_readAck or @ref i2c_readNak
 
 @param    ack 1 send ack, request more data from device<br>
               0 send nak, read is followed by a stop condition 
 @return   byte read from I2C device
 */
unsigned char i2c_read(unsigned char ack);

#define i2c_read(ack)  (ack) ? i2c_readAck() : i2c_readNak(); 

#endif  // _I2CMASTER_H
