#ifndef FILTER_H
#define FILTER_H

#include "Iir.h"


/**
 * Filtering and integrating accelerometer data in order to achieve position.
 */

class Filter
{

 public:
   
   /** The constructor. */
   Filter();


   /**
    * @brief Threshold and filter used for accelerometer data. 
    *
    * If the threshold is reached the data will be lowpass filtered.
    *
    * @param value the input value that should be processed.
    * @return 0 if the value doesn't reach threshold, otherwise return lowpass filtered value.
    */
    float thresholdOrFilt(float value);


   /**
    * @brief Integrates the input value with the trapezoidal method.
    *
    * @param val0 the initial value.
    * @param curr the current value with unit that needs to be integrated.
    * @param prev the previous value with unit that needs to be integrated.
    * @return the calculated integral.
    */
    float integrate(float val0, float curr, float prev);


   /**
    * @brief Threshold used for velocity data that prevents drift and acts as a hp filter.
    *
    * If the value doesn't reach threshold, both the current value and 
    * previous will be set to 0.
    *
    * @param value the input value that should be checked.
    * @param prev the previous value corresponding to the input value.
    */
    void threshold(float& value, float& prev);


   /**
    * @brief Counts number of times that acceleration has been zero.
    *
    * @param count the counter that is checked.
    * @param accel the value of the current acceleration.
    */
    void counter(int& count, float accel);


   /**
    * @brief Sets current and previous velocity value to zero if the counter has exceeded 5.
    *
    * @param counter the counter that is checked.
    * @param vel the current velocity.
    * @param prevVel the previous velocity.
    */
    void  setVel(int& counter, float& vel, float& prevVel);


   /** The destructor. */
   ~Filter();


 private:

    Iir::Butterworth::LowPass<8> lp; /**< Filter structure for 8th order lp Butterworth. */

    const float dT = 0.01; /**< Time between two samples. */

    const float thresh = 0.06; /**< Threshold value for detection of acceleration */

    const float samplingrate = 100; /**< Sampling rate. */

    const float cutoff_frequency = 5;/**< Cutoff frequency. */

};

#endif
