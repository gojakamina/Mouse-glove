#include <xdo.h>
#include "LSM9DS1.h"

int main() {
    xdo_t* x = xdo_new(NULL);
    
    while (true) {      
        readAccel();
        int16_t ax;
        int16_t ay;//get the shifting
        xdo_mouse_move_relative(x, ax, ay);//change the coordinate         
        usleep(20);//control the interval 
    }
 
}