#ifndef FILTER_H
#define FILTER_H

#include "Iir.h"


/**
 * Implementation of filtering and integrating accelerometer data in order to
 * achieve position.
 */

class Filter
{

public:
	Filter(); // Constructor


// methods

	float thresholdOrFilt(float value); // threshold + filter

	float integrate(float val0, float curr, float prev); // integrate

	void threshold(float& value, float& prev); // threshold

	void counter(int& count, float accel); // counts nr. times accel is 0

	void  setVel(int& counter, float& vel, float& prevVel); // forces vel to 0


	~Filter(); // Destructor

// variables

// time between two samples
const float dT = 0.01;

// threshold value for detection of acceleration
const float thresh = 0.06;

// sampling rate and frequencies for filtering high frequencies
const float samplingrate = 100;
const float cutoff_frequency = 5;


private:
        // create the filter structure for 8th order
	Iir::Butterworth::LowPass<8> lp;

};

#endif
