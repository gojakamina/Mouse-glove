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

#include <pthread.h> 
#include <iostream>
#include <wiringPi.h>

#define Left_Key_down  0 //PIN11
#define Left_Key_up    1 //PIN12
#define Right_Key_down 2 //PIN13
#define Right_Key_up   3 //Pin15
#define reset_button   4 //Pin16
#define Motor		   5 //Pin18


float currAccZ, currAccY, currVelZ, currVelY, currPosZ, currPosY, prevAccZ, prevAccY, prevVelZ, prevVelY, prevPosZ, prevPosY = 0;
float dT = 0.01;
float conv = 9.80665;
float thresh  = 0.06;
float dpi = 1920/53.15; //24' 1080p
int countZ, countY = 0;


// sampling rate and frequencies for filtering high frequencies
const float samplingrate = 100;
const float cutoff_frequency = 5;

// filter order is determined in the class found in Filter.h, should be changed
Filter lowpass(samplingrate, cutoff_frequency);

xdo_t * x = xdo_new(NULL);


void mouse_upL(void){
	xdo_mouse_up(x, CURRENTWINDOW, 1);
	//std::cout << "release\n";
}

void mouse_upR(void){
	xdo_mouse_up(x, CURRENTWINDOW, 3);
	//std::cout << "release\n";
}

void mouse_downL(void){
	//anti-shake
	delay(20);
	if(digitalRead(Left_Key_down)){
		xdo_mouse_down(x, CURRENTWINDOW, 1);
		//std::cout << "press\n";
	}
}

void mouse_downR(void){
	//anti-shake
	delay(20);
	if(digitalRead(Left_Key_down)){
		xdo_mouse_down(x, CURRENTWINDOW, 3);
		//std::cout << "press\n";
	}
}

//thread for Click event
void *MouseClik(void *args){
	pinMode(Left_Key_down,INPUT);
	pinMode(Left_Key_up,INPUT);
	
	pinMode(Right_Key_down,INPUT);
	pinMode(Right_Key_up,INPUT);
		
	//setup interrupte
	wiringPiISR (Left_Key_up, INT_EDGE_FALLING, &mouse_upL);
	wiringPiISR (Left_Key_down, INT_EDGE_RISING, &mouse_downL);
	wiringPiISR (Right_Key_up, INT_EDGE_FALLING, &mouse_upR);
	wiringPiISR (Right_Key_down, INT_EDGE_RISING, &mouse_downR);
	return 0;
}


void positionReset() {
	currPosZ = 0;
	currPosY = 0;
	digitalWrite(Motor, HIGH);
	delay(500);
}
	
//thread for reset position
void *reset(void *args){
	pinMode(reset_button,INPUT);
	pinMode(Motor, OUTPUT);
	wiringPiISR (reset_button, INT_EDGE_FALLING, &positionReset);
	return 0;
}
	

/**
 * Threshold used for accelerometer data. Prevents values lower than a specified limit.
 * If the threshold is reached the data will be filtered.
 * @param value the input value that should be processed.
 * @param thresh the threshold value.
 * @return 0 if the value doesn't reach threshold, otherwise return filtered value.
 */
float thresholdOrFilt(float value, float thresh) {
	if( value < thresh && value > -thresh) {return 0;}
	else {return lowpass.lpFilter(value);}
}


/**
 * Threshold used for velocity data. Prevents drift and acts as a high pass filter.
 * If the value doesn't reach threshold, both the current value and previous will be set to 0.
 * @param value the input value that should be checked.
 * @param prev the previous value corresponding to the input value.
 * @thresh the threshold value.
 */
void threshold(float& value, float& prev, float thresh) {
	if(value < thresh && value > - thresh) {
		value = 0;
		prev = 0;
	}
}

/**
 * Integrates the input value with the trapezoidal method.
 * @param val0 the initial value.
 * @param curr the current value with unit that needs to be integrated.
 * @param prev the previous value with unit that needs to be integrated.
 * @param dT the elapsed time between the measured readings.
 * @return the calculated integral.
 */
float integrate(float val0, float curr, float prev, float dT) {
    return val0 + dT*(curr+prev)*0.5;
}


/**
 * Counts number of times that acceleration has been zero.
 * @param count the counter that is checked.
 * @param accel the value of the current acceleration.
 */
void counter(int& count, float accel) {
	if(accel == 0) {count++;}
	else {count = 0;}
}

/**
 * Sets current and previous velocity value to zero if the counter has exceeded 5.
 * @param counter the counter that is checked.
 * @param vel the current velocity.
 * @param prevVel the previous velocity.
 */
void  setVel(int& counter, float& vel, float& prevVel) {
	if (counter >= 6) {
		vel = 0;
		prevVel = 0;
		counter = 0;}
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
		currAccZ = thresholdOrFilt(az-1, thresh);
		currAccY = thresholdOrFilt(ay, thresh);

		// ceeps track of how many times accel has been zero to prevent drift in velocity.
		counter(countZ, currAccZ);
		counter(countY, currAccY);

		// integrate to get velocity
		currVelZ = integrate(prevVelZ, currAccZ, prevAccZ, dT);
		currVelY = integrate(prevVelY, currAccY, prevAccY, dT);

		// prevent drift in velocity
		setVel(countZ, currVelZ, prevVelZ);
		threshold(currVelZ, prevVelZ, 0.001);

		setVel(countY, currVelY, prevVelY);
		threshold(currVelY, prevVelY, 0.001);

		// integrate to get position
		currPosZ = integrate(prevPosZ, currVelZ, prevVelZ, dT);
		currPosY = integrate(prevPosY, currVelY, prevVelY, dT);


		// print values
		//printf("Acc, vel & pos: %f, %f, %f, %f, %f, %f \n", currAccZ, currVelZ, currPosZ*conv, currAccY, currVelY, currPosY*conv);


		// set current values to previous
		prevAccZ = currAccZ;
		prevAccY = currAccY;

		prevVelZ = currVelZ;
		prevVelY = currVelY;

		prevPosZ = currPosZ;
		prevPosY = currPosY;
		
		xdo_move_mouse(x, currPosY*conv*dpi*100, currPosY*conv*dpi*100,0);
		//move mouse
	}
};

int main(int argc, char *argv[]) {
	
	wiringPiSetup();
	
	pthread_t click,Topleftmove;
	pthread_create(&click,NULL,MouseClik,NULL);
	pthread_create(&Topleftmove,NULL,reset,NULL);
	
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
