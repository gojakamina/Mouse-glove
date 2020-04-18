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
#define Motor          4

static xdo_t * x = xdo_new(NULL);

/**
 * @brief The class of mouse event including static functions called by interrupt.
 */
class Mouse {
	
	public:
	
	/**
	 * @brief The constructor.
	 */
	Mouse();
	
	/**
	 * @brief release mouse Left bottom.
	 */
	static void mouse_upL(void);

	/**
	 * @brief release mouse right bottom.
	 */
	static void mouse_upR(void);

	/**
	 * @brief press mouse Left bottom (with anti-shake).
	 */
	static void mouse_downL(void);

	/**
	 * @brief press mouse right bottom (with anti-shake).
	 */
	static void mouse_downR(void);

};

#endif
