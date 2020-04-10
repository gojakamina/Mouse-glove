#ifndef MMOUSE_H
#define MMOUSE_H

extern "C" {
#include <xdo.h>
}

#define Left_Key_down  17 //PIN11
#define Left_Key_up    18 //PIN12
#define Right_Key_down 22 //PIN15
#define Right_Key_up   23 //Pin16
#define reset_button   27 //Pin13
#define Motor          24 //Pin18

static xdo_t * x = xdo_new(NULL);

/** @brief release mouse Left bottum */
void mouse_upL(void);

/** @brief release mouse right bottum */
void mouse_upR(void);

/** @brief press mouse Left bottum */
void mouse_downL(void);

/** @brief press mouse right bottum */
void mouse_downR(void);

#endif