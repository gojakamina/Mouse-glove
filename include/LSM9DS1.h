/******************************************************************************
SFE_LSM9DS1.h
SFE_LSM9DS1 Library Header File
Jim Lindblom @ SparkFun Electronics
Original Creation Date: February 27, 2015
https://github.com/sparkfun/LSM9DS1_Breakout

2020, Bernd Porr, mail@berndporr.me.uk

This file prototypes the LSM9DS1 class, implemented in SFE_LSM9DS1.cpp. In
addition, it defines every register in the LSM9DS1 (both the Gyro and Accel/
Magnetometer registers).

Development environment specifics:
    Hardware Platform: Raspberry PI
    LSM9DS1 Breakout Version: 1.0

This code is beerware; if you see me (or any other SparkFun employee) at the
local, and you've found our code helpful, please buy us a round!

Distributed as-is; no warranty is given.
******************************************************************************/
#ifndef __LSM9DS1_H__
#define __LSM9DS1_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <thread>
#include "LSM9DS1_Registers.h"
#include "LSM9DS1_Types.h"
#include "CppTimer.h"

#define LSM9DS1_AG_ADDR(sa0)    ((sa0) == 0 ? 0x6A : 0x6B)
#define LSM9DS1_M_ADDR(sa1)        ((sa1) == 0 ? 0x1C : 0x1E)

enum lsm9ds1_axis {
		   X_AXIS,
		   Y_AXIS,
		   Z_AXIS,
		   ALL_AXIS
};


/**
 * @brief Sensor data callback.
 **/
class LSM9DS1callback {
public:
        /**
         * @brief Called after a sample has arrived.
         **/
        virtual void hasSample(float gx,
			       float gy,
			       float gz,
			       float ax,
			       float ay,
			       float az,
			       float mx,
			       float my,
			       float mz) = 0;
};

/**
 * @brief Class to enable sensor readings.
 **/
class LSM9DS1 : public CppTimer
{
public:
	IMUSettings settings;

	// We'll store the gyro, accel, and magnetometer readings in a series of
	// public class variables. Each sensor gets three variables -- one for each
	// axis. Call readGyro(), readAccel(), and readMag() first, before using
	// these variables!
	// These values are the RAW signed 16-bit readings from the sensors.
	int16_t gx, gy, gz; // x, y, and z axis readings of the gyroscope
	int16_t ax, ay, az; // x, y, and z axis readings of the accelerometer
	int16_t mx, my, mz; // x, y, and z axis readings of the magnetometer
	int16_t temperature; // Chip temperature
	float gBias[3], aBias[3], mBias[3];
	int16_t gBiasRaw[3], aBiasRaw[3], mBiasRaw[3];
    
    
	/**
     * @brief The Constructor.
     * 
     * The constructor sets up private variables and sets the communication mode.
     * 
     * @param interface sets the interface, either IMU_MODE_SPI or IMU_MODE_I2C
     * @param xgAddr sets an address or pin. If MU_MODE_I2C, this is the I2C address of the accel/gyroscope
     * and if IMU_MODE_SPI, this is the chip select pin of the gyro (CS_AG).
     * @param mAddr sets an address or pin. If IMU_MODE_I2C, this is the I2C address of the magnetometer
     * and if IMU_MODE_SPI, this is the cs pin of the magnetometer (CS_M).
     **/
	LSM9DS1(interface_mode interface, uint8_t xgAddr, uint8_t mAddr);
	LSM9DS1();
        

	/**
     * @brief Initializes the gyro, accelerometer and magnetometer.
     * 
     * This will set up the scale and output rate of each sensor. The values set
     * in the IMUSettings struct will take effect after calling this function.
     * 
     * @return whoAmICombined.
     **/
	uint16_t begin();


	/**
     * @brief Ends a possible thread in the background.
     **/
	void end();


	/**
     * @brief Sets a callback.
     * 
     * @param cb the callback to be set.
     **/
	void setCallback(LSM9DS1callback* cb) {
		lsm9ds1Callback = cb;
	}

    
    /**
     * @brief Calibrates the sensor data.
     * 
     * @param autoCalc could either be set true (default) or false.
     **/
	void calibrate(bool autoCalc = true);
	
	
    /**
     * @brief Calibrates the magnetometer data.
     * 
     * @param autoCalc could either be set true (default) or false.
     **/
	void calibrateMag(bool loadIn = true);
	
	
    /**
     * @brief Sets the magnetometer offset.
     * 
     * @param axis the axis for which the offset should be set.
     * @param offset the offset that should be set.
     **/
	void magOffset(uint8_t axis, int16_t offset);
    

	 /**
     * @brief Polls the accelerometer status register to check if new data is available.
     * 
     * @return 1 if new data is available, 0 if no new data is available.
     **/
	uint8_t accelAvailable();
    

	 /**
     * @brief Polls the gyroscope status register to check if new data is available.
     * 
     * @return 1 if new data is available, 0 if no new data is available.
     **/
	uint8_t gyroAvailable();
    

	 /**
     * @brief Polls the temperature status register to check if new data is available.
     * 
     * @return 1 if new data is available, 0 if no new data is available.
     **/
	uint8_t tempAvailable();
    

	 /**
     * @brief Polls the temperature status register to check if new data is available.
     * 
     * @param axis can either be X_AXIS, Y_AXIS, Z_AXIS, to check for new data on one specific axis or ALL_AXIS (default) to check for new data on all axes.
     * @return 1 if new data is available, 0 if no new data is available.
     **/
	uint8_t magAvailable(lsm9ds1_axis axis = ALL_AXIS);
    
	
	/**
     * @brief Reads the gyroscope output registers.
     * 
     * This function will read all six gyroscope output registers.
     * The readings are stored in the class' gx, gy, and gz variables. Read
     * those _after_ calling readGyro().
     **/
	void readGyro();
    
    
	/**
     * @brief Reads a specific axis of the gyroscope.
     * 
     * [axis] can be any of X_AXIS, Y_AXIS, or Z_AXIS.
     * 
     * @param axis can either be can be either X_AXIS, Y_AXIS, or Z_AXIS.
     * @return a 16-bit signed integer with sensor data on requested axis.
     **/
	int16_t readGyro(lsm9ds1_axis axis);
    

	/**
     * @brief Reads the accelerometer output registers.
     * 
     * This function will read all six accelerometer output registers.
     * The readings are stored in the class' ax, ay, and az variables. Read those _after_ calling readAccel().
     **/
	void readAccel();
    

	/**
     * @brief Reads a specific axis of the accelerometer.
     * 
     * [axis] can be any of X_AXIS, Y_AXIS, or Z_AXIS.
     * 
     * @param axis can either be can be either X_AXIS, Y_AXIS, or Z_AXIS.
     * @return a 16-bit signed integer with sensor data on requested axis.
     **/
	int16_t readAccel(lsm9ds1_axis axis);
    
    
	/**
     * @brief Reads the magnetometer output registers.
     * 
     * This function will read all six magnetometer output registers.
     * The readings are stored in the class' ax, ay, and az variables. Read those _after_ calling readMag().
     **/
	void readMag();
    

	/**
     * @brief Reads a specific axis of the magnetometer.
     * 
     * [axis] can be any of X_AXIS, Y_AXIS, or Z_AXIS.
     * 
     * @param axis can either be can be either X_AXIS, Y_AXIS, or Z_AXIS.
     * @return a 16-bit signed integer with sensor data on requested axis.
     **/
	int16_t readMag(lsm9ds1_axis axis);


	/**
     * @brief Reads the temperature output registers.
     * 
     * This function will read two temperature output registers.
     * The readings are stored in the class' temperature variables. Read those _after_ calling readTemp().
     **/
	void readTemp();
    
    
    /**
     * @brief Converts from RAW signed 16-bit value to degrees per second.
     * 
     * This function reads in a signed 16-bit value and returns the scaled DPS. This function relies on gScale and gRes being correct.
     * 
     * @param gyro is a signed 16-bit raw reading from the gyroscope.
     * @return the gyro raw reading times our pre-calculated DPS / (ADC tick).
     **/
	float calcGyro(int16_t gyro);
    
    
    /**
     * @brief Converts from RAW signed 16-bit value to gravity (g's).
     * 
     * This function reads in a signed 16-bit value and returns the scaled g's. This function relies on aScale and aRes being correct.
     * 
     * @param accel is a signed 16-bit raw reading from the accelerometer.
     * @return the accel raw reading times our pre-calculated g's / (ADC tick).
     **/
	float calcAccel(int16_t accel);
    
    
    /**
     * @brief Converts from RAW signed 16-bit value to Gauss (Gs).
     * 
     * This function reads in a signed 16-bit value and returns the scaled Gs. This function relies on mScale and mRes being correct.
     * 
     * @param mag is a signed 16-bit raw reading from the magnetometer.
     * @return the mag raw reading times our pre-calculated Gs / (ADC tick).
     **/
	float calcMag(int16_t mag);
    
    
    /**
     * @brief Sets the full-scale range of the gyroscope.
     * 
     * This function can be called to set the scale of the gyroscope to 245, 500, or 200 degrees per second.
     * 
     * @param gScl is the desired gyroscope scale.
     **/
	void setGyroScale(uint16_t gScl);
    
    
    /**
     * @brief Sets the full-scale range of the accelerometer.
     * 
     * This function can be called to set the scale of the accelerometer to 2, 4, 6, 8, or 16 g's.
     * 
     * @param aScl is the desired accelerometer scale. Must be one of five possible values from the accel_scale.
     **/
	void setAccelScale(uint8_t aScl);
    
    
    /**
     * @brief Sets the full-scale range of the magnetometer.
     * 
     * This function can be called to set the scale of the magnetometer to 2, 4, 8, or 12 Gs.
     * 
     * @param mScl is the desired magnetometer scale. Must be one of four possible values from the mag_scale.
     **/
	void setMagScale(uint8_t mScl);
    
    
    /**
     * @brief Sets the output data rate and bandwidth of the gyroscope.
     * 
     * @param gRate is the desired output rate and cutoff frequency of the gyro.
     **/
	void setGyroODR(uint8_t gRate);
    
    
    /**
     * @brief Sets the output data rate and bandwidth of the accelerometer.
     * 
     * @param aRate is the desired output rate and cutoff frequency of the accel.
     **/
	void setAccelODR(uint8_t aRate);     
    
    
    /**
     * @brief Sets the output data rate and bandwidth of the magnetometer.
     * 
     * @param mRate is the desired output rate and cutoff frequency of the mag.
     **/
	void setMagODR(uint8_t mRate);
    
    
    /**
     * @brief Configures inactivity interrupt parameters.
     * 
     * @param duration is the inactivity duration. The actual value depends on gyro ODR.
     * @param threshold is the activity threshold.
     * @param sleepOn is the gyroscope operating mode during inactivity.
     *  true: gyroscope in sleep mode
     *  false: gyroscope in power-down
     **/
	void configInactivity(uint8_t duration, uint8_t threshold, bool sleepOn);
    
    
     /**
     * @brief Configures Accelerometer Interrupt Generator.
     * 
     * @param generator is the interrupt axis/high-low events. Any OR'd combination of ZHIE_XL, ZLIE_XL, YHIE_XL, YLIE_XL, XHIE_XL, XLIE_XL
     * @param andInterrupts AND/OR combination of interrupt events.
     * true: AND combination
     * false: OR combination
     **/
	void configAccelInt(uint8_t generator, bool andInterrupts = false);
    
    
    /**
     * @brief Configures the threshold of an accelereomter axis.
     * 
     * @param threshold is the interrupt threshold. Possible values: 0-255.
     * @param axis the axis to be configured. Either X_AXIS, Y_AXIS, or Z_AXIS.
     * @param duration the value must be above or below threshold to trigger intrerrupt.
     * @param wait the duration samples before exiting the interrupt.
     * true: Wait for duration samples before exiting interrupt
     * false: Wait function off
     **/
	void configAccelThs(uint8_t threshold, lsm9ds1_axis axis, uint8_t duration = 0, bool wait = 0);
    
    
    /**
     * @brief Configures Gyroscope Interrupt Generator.
     * 
     * @param generator interrupts axis/high-low events. Any OR'd combination of ZHIE_G, ZLIE_G, YHIE_G, YLIE_G, XHIE_G, XLIE_G
     * @param aoi AND/OR combination of interrupt events.
     * true: AND combination
     * false: OR combination
     * @param latch latches gyroscope interrupt request.
     **/
	void configGyroInt(uint8_t generator, bool aoi, bool latch);
    
    
    /**
     * @brief Configures the threshold of a gyroscope axis
     * 
     * @param threshold interrupts threshold. Possible values: 0-0x7FF. Value is equivalent to raw gyroscope value.
     * @param axis the axis to be configured. Either X_AXIS, Y_AXIS, or Z_AXIS.
     * @param duration the duration value must be above or below threshold to trigger interrupt.
     * @param wait value for duration sample before exiting interrupt.
     * true: Wait for duration samples before exiting interrupt
     * false: Wait function off
     **/
	void configGyroThs(int16_t threshold, lsm9ds1_axis axis, uint8_t duration, bool wait);
    
    
    
    /**
     * @brief Configures INT1 or INT2 (Gyro and Accel Interrupts only).
     * 
     * @param interrupt Select INT1 or INT2. Possible values: XG_INT1 or XG_INT2
     * @param generator Or'd combination of interrupt generators. ossible values: INT_DRDY_XL, INT_DRDY_G, INT1_BOOT (INT1 only), INT2_DRDY_TEMP (INT2 only)
     * INT_FTH, INT_OVR, INT_FSS5, INT_IG_XL (INT1 only), INT1_IG_G (INT1 only), INT2_INACT (INT2 only).
     * @param activeLow interrupts active configuration. Can be either INT_ACTIVE_HIGH or INT_ACTIVE_LOW.
     * @param pushPull push-pulls or open drains interrupt configuration. Can be either INT_PUSH_PULL or INT_OPEN_DRAIN.
     **/
	void configInt(interrupt_select interupt, uint8_t generator,
		       h_lactive activeLow = INT_ACTIVE_LOW, pp_od pushPull = INT_PUSH_PULL);
                     
                   
    /**
     * @brief Configures Magnetometer Interrupt Generator.
     * 
     * @param generator interrups axis/high-low events.
     * @param activeLow interrupts active configuration. Can be either INT_ACTIVE_HIGH or INT_ACTIVE_LOW.
     * @param latch latches gyroscope interrupt request.
     **/
	void configMagInt(uint8_t generator, h_lactive activeLow, bool latch = true);
    
    
    /**
     * @brief Configures the threshold of a gyroscope axis.
     * 
     * @param threshold interrupts threshold. Possible values: 0-0x7FF. Value is equivalent to raw magnetometer value.
     **/
	void configMagThs(uint16_t threshold);
	
	
	/**
     * @brief Gets contents of gyroscope interrupt source register.
     * 
     * @return the contents of gyroscope interrupt source register.
     **/
	uint8_t getGyroIntSrc();
    
    
	/**
     * @brief Gets contents of accelerometer interrupt source register.
     * 
     * @return the contents of accelerometer interrupt source register.
     **/
	uint8_t getAccelIntSrc();
    
    
   /**
     * @brief Gets contents of magnetometer interrupt source register.
     * 
     * @return the contents of magnetometer interrupt source register.
     **/
	uint8_t getMagIntSrc();
    
    
    /**
     * @brief Gets status of inactivity interrupt.
     * 
     * @return the status of inactivity interrupt.
     **/
	uint8_t getInactivity();
    
    
    /**
     * @brief Sets gyro to sleep or wake.
     * 
     * @param enable gyro to sleep or wake. True = sleep, false = wake.
     **/
	void sleepGyro(bool enable = true);
    
    
    /**
     * @brief Enables or disables the FIFO.
     * 
     * @param enable FIFO or diable. True = enable, false = disable.
     **/
	void enableFIFO(bool enable = true);
    
    
    /**
     * @brief Configures FIFO mode and Threshold
     * 
     * @param fifoMode sets FIFO mode to off, FIFO (stop when full), continuous, bypass. 
     * Possible inputs: FIFO_OFF, FIFO_THS, FIFO_CONT_TRIGGER, FIFO_OFF_TRIGGER, FIFO_CONT.
     * @param fifoThs sets FIFO threshold level. Any value from 0-0x1F is acceptable.
     **/
	void setFIFO(fifoMode_type fifoMode, uint8_t fifoThs);
    
    
   /**
     * @brief Gets number of FIFO samples.
     * 
     * @return number of FIFO samples.
     **/
	uint8_t getFIFOSamples();
        

protected:
	// File descriptors
	int _fd;
    
	// x_mAddress and gAddress store the I2C address or SPI chip select pin
	// for each sensor.
	uint8_t _mAddress, _xgAddress;
    
	// gRes, aRes, and mRes store the current resolution for each sensor. 
	// Units of these values would be DPS (or g's or Gs's) per ADC tick.
	// This value is calculated as (sensor scale) / (2^15).
	float gRes, aRes, mRes;
    
	// _autoCalc keeps track of whether we're automatically subtracting off
	// accelerometer and gyroscope bias calculated in calibrate().
	bool _autoCalc;
    

   /**
     * @brief Sets up gyro, accel, and mag settings to default.
     * 
     * @param interface sets the interface mode (IMU_MODE_I2C or IMU_MODE_SPI).
     * @param xgAddr sets either the I2C address of the accel/gyro or SPI chip. Select pin connected to the CS_XG pin.
     * @param mAddr sets either the I2C address of the magnetometer or SPI chip select pin connected to the CS_M pin. 
     **/
	void init(interface_mode interface, uint8_t xgAddr, uint8_t mAddr);
    
    
      /**
     * @brief Sets up the gyroscope to begin reading.
     *
     * // initGyro() -- Sets up the gyroscope to begin reading.
     * This function steps through all five gyroscope control registers.
     * Upon exit, the following parameters will be set:
     *    - CTRL_REG1_G = 0x0F: Normal operation mode, all axes enabled. 
     *        95 Hz ODR, 12.5 Hz cutoff frequency.
     *    - CTRL_REG2_G = 0x00: HPF set to normal mode, cutoff frequency
     *        set to 7.2 Hz (depends on ODR).
     *    - CTRL_REG3_G = 0x88: Interrupt enabled on INT_G (set to push-pull and
     *        active high). Data-ready output enabled on DRDY_G.
     *    - CTRL_REG4_G = 0x00: Continuous update mode. Data LSB stored in lower
     *        address. Scale set to 245 DPS. SPI mode set to 4-wire.
     *    - CTRL_REG5_G = 0x00: FIFO disabled. HPF disabled. 
     **/
	void initGyro();
    
    
    /**
     * @brief Sets up the accelerometer to begin reading.
     * 
     * This function steps through all accelerometer related control registers.
     * Upon exit these registers will be set as:
     *    - CTRL_REG0_XM = 0x00: FIFO disabled. HPF bypassed. Normal mode.
     *    - CTRL_REG1_XM = 0x57: 100 Hz data rate. Continuous update.
     *        all axes enabled.
     *    - CTRL_REG2_XM = 0x00:  2g scale. 773 Hz anti-alias filter BW.
     *    - CTRL_REG3_XM = 0x04: Accel data ready signal on INT1_XM pin.
     **/
	void initAccel();
    
    
    /**
     * @brief Sets up the magnetometer to begin reading.
     * 
     * This function steps through all magnetometer-related control registers.
     * Upon exit these registers will be set as:
     *    - CTRL_REG4_XM = 0x04: Mag data ready signal on INT2_XM pin.
     *    - CTRL_REG5_XM = 0x14: 100 Hz update rate. Low resolution. Interrupt
     *        requests don't latch. Temperature sensor disabled.
     *    - CTRL_REG6_XM = 0x00:  2 Gs scale.
     *    - CTRL_REG7_XM = 0x00: Continuous conversion mode. Normal HPF mode.
     *    - INT_CTRL_REG_M = 0x09: Interrupt active-high. Enable interrupts. 
     **/
	void initMag();
    
    
    /**
     * @brief Reads a byte from a specified gyroscope register.
     * 
     * @param subAddress the register to be read from.
     * @return a 8-bit value read from the requested address.
     **/
	uint8_t mReadByte(uint8_t subAddress);
    
    
    /**
     * @brief Reads a number of bytes -- beginning at an address and incrementing from there -- from the gyroscope.
     * 
     * @param subAddress the register to be read from.
     * @param dest a pointer to an array of uint8_t's. Values read will be stored in here on return.
     * @param count the number of bytes to be read.
     **/
	void mReadBytes(uint8_t subAddress, uint8_t * dest, uint8_t count);
    
    
    /**
     * @brief Writes a byte to a register in the gyroscope.
     * 
     * @param subAddress the register to be written to.
     * @param data the data to be written into the register.  
     **/
	void mWriteByte(uint8_t subAddress, uint8_t data);
    
    
    /**
     * @brief Reads a byte from a register in the accel/mag sensor.
     * 
     * @param subAddress the register to be read from.
     * @return a 8/bit value read from the requested register.  
     **/
	uint8_t xgReadByte(uint8_t subAddress);
    
    
    /**
     * @brief Reads a number of bytes -- beginning at an address and incrementing from there -- from the accelerometer/magnetometer.
     * 
     * @param subAddress the register to be read from.
     * @param dest a pointer to an array of uint8_t's. Values read will be stored in here on return.
     * @param count the number of bytes to be read.  
     **/
	void xgReadBytes(uint8_t subAddress, uint8_t * dest, uint8_t count);
    
    
    /**
     * @brief Writes a byte to a register in the accel/mag sensor.
     * 
     * @param subAddress the register to be written to.
     * @param data the data to be written to the register.
     * @param
     * @param   
     **/
	void xgWriteByte(uint8_t subAddress, uint8_t data);
    
    
    /**
     * @brief Calculates the resolution of the gyroscope. 
     * 
     * This function will set the value of the gRes variable. gScale must be set prior to calling this function.
     **/
	void calcgRes();
    
    
    /**
     * @brief Calculates the resolution of the magnetometer.
     * 
     * This function will set the value of the mRes variable. mScale must be set prior to calling this function.
     **/
	void calcmRes();
    
    
    /**
     * @brief Calculates the resolution of the accelerometer.
     * 
     * This function will set the value of the aRes variable. aScale must be set prior to calling this function.
     **/
	void calcaRes();
    
    
	//////////////////////
	// Helper Functions //
	//////////////////////
	
	/**
     * @brief Constrains scales.
     **/
	void constrainScales();
    
    
	///////////////////
	// SPI Functions //
	///////////////////
	
	
	/**
     * @brief Initializes the SPI hardware.
     * 
     * This function will setup all SPI pins and related hardware.  
     **/
	void initSPI();
    
    
    /**
     * @brief Writes a byte out of SPI to a register in the device
     * 
     * @param csPin the chip select pin of the slave device. 
     * @param subAddress the register to be written to.
     * @param data byte to be written into the register. 
     **/
	void SPIwriteByte(uint8_t csPin, uint8_t subAddress, uint8_t data);
    
    
    /**
     * @brief Reads a single byte from a register over SPI.
     * 
     * @param csPin the chip select pin of the slave device.
     * @param subAddress the register to be read from.
     * @return the byte read from the requested address. 
     **/
	uint8_t SPIreadByte(uint8_t csPin, uint8_t subAddress);
    
    
    
    /**
     * @brief Initializes the SPI hardware.
     * 
     * @param 
     * @param
     * @param
     * @param   
     **/
	// SPIreadBytes() -- Read a series of bytes, starting at a register via SPI
	// Input:
	//    - csPin = The chip select pin of a slave device.
	//    - subAddress = The register to begin reading.
	//     - * dest = Pointer to an array where we'll store the readings.
	//    - count = Number of registers to be read.
	// Output: No value is returned by the function, but the registers read are
	//         all stored in the *dest array given.
	void SPIreadBytes(uint8_t csPin, uint8_t subAddress, 
			  uint8_t * dest, uint8_t count);
    
	///////////////////
	// I2C Functions //
	///////////////////
	
	
   /**
     * @brief Initializes the I2C hardware.
     * 
     * This function will setup all I2C pins and related hardware. 
     **/
	void initI2C();
    
    
    /**
     * @brief Writes a byte out of I2C to a register in the device.
     * 
     * @param address the 7-bit I2C address of the slave device.
     * @param subAddress the register to be written to.
     * @param data byte to be written to the register.
     **/
	void I2CwriteByte(uint8_t address, uint8_t subAddress, uint8_t data);
    

	/**
     * @brief Reads a single byte from a register over I2C.
     * 
     * @param address the 7-bit I2C address of the slave device.
     * @param subAddress the register to be read from.
     * @return the byte read from the requested address. 
     **/
	uint8_t I2CreadByte(uint8_t address, uint8_t subAddress);
    
    
    /**
     * @brief Reads a series of bytes, starting at a register via SPI
     * 
     * @param address the 7-bit I2C address of the slave device.
     * @param subAddress the register to begin reading.
     * @param dest the pointer to an array where we'll store the readings.
     * @param count number of register to be read.
     **/
	uint8_t I2CreadBytes(uint8_t address, uint8_t subAddress, uint8_t * dest, uint8_t count);



	LSM9DS1callback* lsm9ds1Callback = NULL;
	
	/**
     * @brief The timer event. 
     **/
	void timerEvent();
};

#endif // SFE_LSM9DS1_H //
