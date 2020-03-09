#ifndef FILTER_H
#define FILTER_H

#include "Iir.h"

class Filter 
{

private:
	// create the filter structure for 4rd order
	Iir::Butterworth::BandPass<4> bp;
	Iir::Butterworth::HighPass<4> hp;

public: 
       Filter(float samplingrate, float centerFrequency, double widthFrequency) {bp.setup (samplingrate, centerFrequency, widthFrequency);}
       Filter(float samplingrate, float cutoff_frequency) {hp.setup (samplingrate, cutoff_frequency);}
	
       float bpFilter(float value) {return bp.filter(value);}
       float hpFilter(float value) {return hp.filter(value);}
};

#endif
