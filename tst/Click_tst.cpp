#include <pthread.h> 
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <wiringPi.h>
#include "Mouse.h"


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
	pthread_create(&click,NULL,MouseClik,NULL);
	
	while(1){
	}
}
