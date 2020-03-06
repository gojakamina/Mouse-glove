#ifndef FILTER_H
#define FILTER_H

#include "Iir.h"

class Filter 
{

private:
	// create the filter structure for 3rd order
	Iir::Butterworth::LowPass<3> f;

public: 
       Filter(float samplingrate, float cutoff_frequency) {f.setup (samplingrate, cutoff_frequency);}

       float  filterData(float value) {return f.filter(value);}
};

#endif
