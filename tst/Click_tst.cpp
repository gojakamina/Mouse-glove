#include <pthread.h> 
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <wiringPi.h>
#include "Mouse.h"

extern "C" {
#include <xdo.h>
}

void positionreset(){
	xdo_move_mouse(x,0,0,0);
	std::cout << "reset\n";
	digitalWrite(Motor,HIGH);
	delay(500);
	digitalWrite(Motor,LOW);
}
 
void *reset(void *arge){
	pinMode(reset_button,INPUT);
	pinMode(Motor,OUTPUT);
	
	wiringPiISR(reset_button,INT_EDGE_FALLING,&positionreset);
	return 0;
}

void *MouseClik(void *args){
	
	pinMode(Left_Key_down,INPUT);
	pinMode(Left_Key_up,INPUT);

	pinMode(Right_Key_down,INPUT);
	pinMode(Right_Key_up,INPUT);

	//setup interrupte
	wiringPiISR (Left_Key_up, INT_EDGE_FALLING, &Mouse::mouse_downL);
	wiringPiISR (Left_Key_down, INT_EDGE_RISING, &Mouse::mouse_upL);
	wiringPiISR (Right_Key_up, INT_EDGE_FALLING, &Mouse::mouse_upR);
	wiringPiISR (Right_Key_down, INT_EDGE_RISING, &Mouse::mouse_downR);
	return 0;
}


int main() {

	wiringPiSetupGpio();
	pthread_t click;
	pthread_t Topleftmove;

	pthread_create(&click,NULL,MouseClik,NULL);
	pthread_create(&Topleftmove,NULL,reset,NULL);	
	while(1){
	}
}
