#ifndef MMOUSE_H
#define MMOUSE_H

extern "C" {
#include <xdo.h>
}


///PIN11 left button (detect press) Intrrupt.
#define Left_Key_down  17

///PIN12 left button (detect release) Intrrupt.
#define Left_Key_up    18

///PIN15 right button (detect press) Intrrupt.
#define Right_Key_down 22

///Pin16 right button (detect release) Intrrupt.
#define Right_Key_up   23

///Pin13 the button force curser to screen topleft (DigitalIn).
#define reset_button   27

///Pin18 control motor (DigitalOut).
#define Motor          24

static xdo_t * x = xdo_new(NULL);

/**
 * @brief The class of mouse event including static functions called by interrupt.
 */
class Mouse {
	
	public:
	
	Mouse();
	
	/**
	 * @brief release mouse Left bottum.
	 */
	static void mouse_upL(void);

	/**
	 * @brief release mouse right bottum.
	 */
	static void mouse_upR(void);

	/**
	 * @brief press mouse Left bottum (with anti-shake).
	 */
	static void mouse_downL(void);

	/**
	 * @brief press mouse right bottum (with anti-shake).
	 */
	static void mouse_downR(void);

};

#endif
