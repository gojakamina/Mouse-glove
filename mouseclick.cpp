#include "xdosimulation.h"

void mouseclick()
{
	xdo_t* x = xdo_new(NULL);
	wiringPiSetup();
	pinMode(L, INPUT);
	pinMode(R, INPUT);
	pinMode(S, INPUT);
	pinMode(M, OUTPUT);
	while (true) {
		if (digitalRead(L) == 0)
		{
			xdo_mouse_down(x, CURRENTWINDOW, 1);
			digitalWrite(M, HIGH); delay(100);
			digitalWrite(M, LOW); delay(100);
		}
		else
		{
			xdo_mouse_up(x, CURRENTWINDOW, 1);
		}
		if (digitalRead(R) == 0)
		{
			xdo_mouse_down(x, CURRENTWINDOW, 3);
			digitalWrite(M, HIGH); delay(100);
			digitalWrite(M, LOW); delay(100);
		}
		else
		{
			xdo_mouse_up(x, CURRENTWINDOW, 3);
		}
		usleep(20);//control the interval	
	}
}