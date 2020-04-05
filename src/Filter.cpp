#include "Filter.h"


// Constructor
Filter::Filter() {
	lp.setup(samplingrate, cutoff_frequency);
}


float Filter::thresholdOrFilt(float value) {
	if( value < thresh && value > -thresh) {
		return 0;
	}
	else {
		return lp.filter(value);
	}
}


float Filter::integrate(float val0, float curr, float prev) {
    return val0 + dT*(curr+prev)*0.5;
}


void Filter::threshold(float& value, float& prev) {
	if(value < 0.001 && value > -0.001) {
		value = 0;
		prev = 0;
	}
}


void Filter::counter(int& count, float accel) {
	if(accel == 0) {count++;}
	else {count = 0;}
}


void Filter::setVel(int& counter, float& vel, float& prevVel) {
	if (counter >= 6) {
		vel = 0;
		prevVel = 0;
		counter = 0;}
}


Filter::~Filter() 
{
	//delete lp;
}
