#include "Filter.h"


// Constructor
Filter::Filter() {
	lp->setup(samplingrate, cutoff_frequency);
}



/**
 * Threshold used for accelerometer data. Prevents values lower than a specified limit
 *
 * If the threshold is reached the data will be lowpass filtered
 *
 * @param value the input value that should be processed
 * @return 0 if the value doesn't reach threshold, otherwise return lowpass filtered value
 */
float Filter::thresholdOrFilt(float value) {
	if( value < thresh && value > -thresh) {
		return 0;
	}
	else {
		return lp->filter(value);
	}
}



/**
 * Integrates the input value with the trapezoidal method
 *
 * @param val0 the initial value
 * @param curr the current value with unit that needs to be integrated
 * @param prev the previous value with unit that needs to be integrated
 * @return the calculated integral
 */
float Filter::integrate(float val0, float curr, float prev) {
    return val0 + dT*(curr+prev)*0.5;
}



/**
 * Threshold used for velocity data. Prevents drift and acts as a high pass filter
 *
 * If the value doesn't reach threshold, both the current value and previous will be set to 0
 *
 * @param value the input value that should be checked.
 * @param prev the previous value corresponding to the input value.
 */
void Filter::threshold(float& value, float& prev) {
	if(value < 0.001 && value > -0.001) {
		value = 0;
		prev = 0;
	}
}



/**
 * Counts number of times that acceleration has been zero
 *
 * @param count the counter that is checked
 * @param accel the value of the current acceleration
 */
void Filter::counter(int& count, float accel) {
	if(accel == 0) {count++;}
	else {count = 0;}
}



/**
 * Sets current and previous velocity value to zero if the counter has exceeded 5
 *
 * @param counter the counter that is checked
 * @param vel the current velocity
 * @param prevVel the previous velocity
 */
void Filter::setVel(int& counter, float& vel, float& prevVel) {
	if (counter >= 6) {
		vel = 0;
		prevVel = 0;
		counter = 0;}
}



Filter::~Filter() 
{
	delete lp;
}
