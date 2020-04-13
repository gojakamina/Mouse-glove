extern "C" {
#include <xdo.h>
}

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include <cmath>

#include "LSM9DS1_Types.h"
#include "LSM9DS1.h"
#include "Filter.h"
#include "Mouse.h"

#include <pthread.h>
#include <iostream>
#include <wiringPi.h>

float currAccZ, currAccY, currVelZ, currVelY, currPosZ, currPosY = 0;
float prevAccZ, prevAccY, prevVelZ, prevVelY, prevPosZ, prevPosY = 0;

int countZ, countY = 0;

float conv = 9.80665;

int dpi = 36; //24' 1080p 1920 / 53.5 cm

// filter
Filter filter;

//reset mouse position (Topleft)
void positionReset() {
	currPosZ = 0;
	currPosY = 0;
	xdo_move_mouse(x, 0, 0, 0);
	std::cout << "reset\n";
	digitalWrite(Motor, HIGH);
	delay(500);
}

//thread for Click event
void *MouseClik(void *args){
	pinMode(Left_Key_down,INPUT);
	pinMode(Left_Key_up,INPUT);

	pinMode(Right_Key_down,INPUT);
	pinMode(Right_Key_up,INPUT);

	//setup interrupte
	wiringPiISR (Left_Key_up, INT_EDGE_FALLING, &Mouse::mouse_upL);
	wiringPiISR (Left_Key_down, INT_EDGE_RISING, &Mouse::mouse_downL);
	wiringPiISR (Right_Key_up, INT_EDGE_FALLING, &Mouse::mouse_upR);
	wiringPiISR (Right_Key_down, INT_EDGE_RISING, &Mouse::mouse_downR);
	return 0;
}



//thread for reset position
void *reset(void *args){
	pinMode(reset_button,INPUT);
	pinMode(Motor, OUTPUT);
	wiringPiISR (reset_button, INT_EDGE_FALLING, &positionReset);
	return 0;
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

		// filter data, bandpass.
		currAccZ = filter.thresholdOrFilt(az-1);
		currAccY = filter.thresholdOrFilt(ay);

		// ceeps track of how many times accel has been zero to prevent drift in velocity.
		filter.counter(countZ, currAccZ);
		filter.counter(countY, currAccY);

		// integrate to get velocity
		currVelZ = filter.integrate(prevVelZ, currAccZ, prevAccZ);
		currVelY = filter.integrate(prevVelY, currAccY, prevAccY);

		// prevent drift in velocity
		filter.setVel(countZ, currVelZ, prevVelZ);
		filter.threshold(currVelZ, prevVelZ);

		filter.setVel(countY, currVelY, prevVelY);
		filter.threshold(currVelY, prevVelY);

		// integrate to get position
		currPosZ = filter.integrate(prevPosZ, currVelZ, prevVelZ);
		currPosY = filter.integrate(prevPosY, currVelY, prevVelY);

		// print to check sensor data
		printf("Acc, vel & pos: %f, %f, %f, %f, %f, %f \n", currAccZ, currVelZ, currPosZ*conv, currAccY, currVelY, currPosY*conv);

		//xdo_move_mouse(x, currPosY*conv*dpi*100, currPosY*conv*dpi*100,0);
		//move mouse

		prevAccZ = currAccZ;
		prevAccY = currAccY;

		prevVelZ = currVelZ;
		prevVelY = currVelY;

		prevPosZ = currPosZ;
		prevPosY = currPosY;

	}
};

void *MouseMove(void *args){    
    LSM9DS1 imu(IMU_MODE_I2C, 0x6b, 0x1e);
    LSM9DS1printCallback callback;
    imu.setCallback(&callback);
    imu.begin();

    do {
	sleep(1);
    } while (getchar() != 27);
    imu.end();
    return 0;

}


int main(int argc, char *argv[]) {

    wiringPiSetupGpio();

    pthread_t click;
    pthread_t Topleftmove;
    pthread_t move;
    
    pthread_create(&click,NULL,MouseClik,NULL);
    pthread_create(&Topleftmove,NULL,reset,NULL);
    pthread_create(&move,NULL,MouseMove,NULL);
    
    do {
	sleep(1);
    } while (getchar() != 27);

    exit(EXIT_SUCCESS);
}
