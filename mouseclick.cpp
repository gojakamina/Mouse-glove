#include "xdosimulation.h"

void mouseclick()
{
	xdo_t* x = xdo_new(NULL);
	wiringPiSetup();
	pinMode(17, INPUT);//Left button
	pinMode(27, INPUT);//Right button
	pinMode(22, INPUT);//Switch
	pinMode(18, OUTPUT);//Motor
	while (true) {
		if (digitalRead(17) == 0)
		{
			xdo_mouse_down(x, CURRENTWINDOW, 1);
			digitalWrite(18, HIGH); delay(100);
			digitalWrite(18, LOW); delay(100);
		}
		else
		{
			xdo_mouse_up(x, CURRENTWINDOW, 1);
		}
		if (digitalRead(27) == 0)
		{
			xdo_mouse_down(x, CURRENTWINDOW, 3);
			digitalWrite(18, HIGH); delay(100);
			digitalWrite(18, LOW); delay(100);
		}
		else
		{
			xdo_mouse_up(x, CURRENTWINDOW, 3);
		}
		usleep(20);//control the interval	
	}
}
