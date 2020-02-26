#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include "LSM9DS1_Types.h"
#include "LSM9DS1.h"

float prevVelValX, prevVelValY, prevPosValX, prevPosValY, calcVelX, calcVelY, calcPosX, calcPosY = 0;

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
		calcVelX = integrate(ax, 0.1, prevVelValX);
		calcVelY = integrate(ay, 0.1, prevVelValY);
		calcPosX = integrate(calcVelX, 0.1, prevPosValX);
		calcPosY = integrate(calcVelY, 0.1, prevPosValY);
		printf("Position: %f, %f [m]\n", calcPosX, calcPosY);
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
