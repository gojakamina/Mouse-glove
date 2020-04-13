extern "C" {
#include <xdo.h>
}

#include <stdio.h>
#include <iostream>
#include <wiringPi.h>
#include "Mouse.h"

void Mouse::mouse_upL(void){
	xdo_mouse_up(x, CURRENTWINDOW, 1);
	std::cout << "releaseL\n";
}

void Mouse::mouse_upR(void){
	xdo_mouse_up(x, CURRENTWINDOW, 3);
	std::cout << "releaseR\n";
}

void Mouse::mouse_downL(void){
	//anti-shake
	delay(20);
	if(digitalRead(Left_Key_down)){
		xdo_mouse_down(x, CURRENTWINDOW, 1);
		std::cout << "pressL\n";
	}
}

void Mouse::mouse_downR(void){
	//anti-shake
	delay(20);
	if(digitalRead(Right_Key_down)){
		xdo_mouse_down(x, CURRENTWINDOW, 3);
		std::cout << "pressR\n";
	}
}



