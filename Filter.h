#ifndef FILTER_H
#define FILTER_H

#include "Iir.h"

class Filter 
{

private:
	// create the filter structure for 4rd order
	Iir::Butterworth::BandPass<8> bp;
	Iir::Butterworth::LowPass<8> lp;

public: 
       Filter(float samplingrate, float centerFrequency, double widthFrequency) {bp.setup (samplingrate, centerFrequency, widthFrequency);}
       Filter(float samplingrate, float cutoff_frequency) {lp.setup (samplingrate, cutoff_frequency);}

       float bpFilter(float value) {return bp.filter(value);}
       float lpFilter(float value) {return lp.filter(value);}
};

#endif
