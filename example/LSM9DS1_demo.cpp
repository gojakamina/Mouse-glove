#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include "LSM9DS1_Types.h"
#include "LSM9DS1.h"

float prevValX = 0;
float prevValY = 0;

/**
  Calculates the velocity baseed on accelerometer measurements.
  @param accel the value of the acceleration measurement.
  @param dT the elapsed time between the accelerometer readings.
  @param prevVel the previous value of the velocity
  @return the calculated velocity
*/
float calcVel(float accel, float dT, float prevVel) {
    float  v = prevVel + accel*dT;
    return v;
}

/**
  Gets the previous value for the x-velovity.
  @return the previous value for the velocity in x.
*/
float prevVelX() {
    if (prevValX == 0){
	return 0;
    } else {
	return prevValX;
    }
}

/**
  Gets the previous value for the y-velovity.
  @return the previous value for the velocity in y.
*/
float prevVelY() {
    if (prevValY == 0){
	return 0;
    } else {
	return prevValY;
    }
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
		printf("Velocity: %f, %f [m/s]\n", calcVel(ax, 0.1, prevVelX()), calcVel(ay, 0.1, prevVelY()));
		prevValX = ax;
		prevValY = ay;
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
