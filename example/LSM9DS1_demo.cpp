#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include "LSM9DS1_Types.h"
#include "LSM9DS1.h"
#include "Filter.h"

float accelX, accelY, prevVelValX, prevVelValY, prevPosValX, prevPosValY, calcVelX, calcVelY, calcPosX, calcPosY = 0;
float dT = 0.0084033613;

/**
 * Integrates the input value
 * @param val the value that should be integrated.
 * @param dT the elapsed time between the measured readings.
 * @param prevVal the previously integrated value from the measurements.
 * @return the calculated integral.
 */
float integrate(float val, float dT, float prevVal) {
    return  val*dT + prevVal;
}

// sampling rate 119 and cutoff frequency 3
const float samplingrate = 119;
const float cutoff_frequency = 3;

// filter order is determined in the class found in Filter.h, should be changed
Filter f(samplingrate, cutoff_frequency);

class LSM9DS1printCallback : public LSM9DS1callback {
	virtual void hasSample(float gx,
			       float gy,
			       float gz,
			       float ax,
			       float ay,
			       float az,
			       float mx,
			       float my,
			       float mz) {
				       
		// applying Butterworth filter on measured data
		accelX = f.filterData(ax);
		accelY = f.filterData(ay);
		
		// integrating acceleration twice to get the position
		calcVelX = integrate(accelX, dT, prevVelValX);
		calcVelY = integrate(accelY, dT, prevVelValY);
		calcPosX = integrate(calcVelX, dT, prevPosValX);
		calcPosY = integrate(calcVelY, dT, prevPosValY);
		
		//accelX = f.filter(ax);
		//accelY = f.filter(ay);
		
		calcVelX = integrate(ax, dT, prevVelValX);
		calcVelY = integrate(ay, dT, prevVelValY);
		calcPosX = integrate(calcVelX, dT, prevPosValX);
		calcPosY = integrate(calcVelY, dT, prevPosValY);

		printf("Position: %f, %f [m]\n", calcPosX, calcPosY);
		
		// saving current velocity + position to use in future integration
		prevVelValX = calcVelX;
		prevVelValY = calcVelY;
		prevPosValX = calcPosX;
		prevPosValY = calcPosY;	
	}
};

int main(int argc, char *argv[]) {
    LSM9DS1 imu(IMU_MODE_I2C, 0x6b, 0x1e);
    LSM9DS1printCallback callback;
    imu.setCallback(&callback);
    imu.begin();
    do {
	sleep(1);
    } while (getchar() != 27);
    imu.end();
    exit(EXIT_SUCCESS);
}
