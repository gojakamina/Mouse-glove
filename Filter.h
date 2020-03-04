#ifndef __FILTER_H__
#define __FILTER_H__

#include "Iir.h"

class FilterData 
{

private:
	// filter parameters
	const float samplingrate = 119;
	const float cutoff_frequency = 3;
	// create the filter structure for 3rd order
	Iir::Butterworth::LowPass<3> f;

public: 
	FilterData() {f.setup (samplingrate, cutoff_frequency);}
	
	Iir::Butterworth::LowPass getFilter() {return f}
}

#endif
