=================Overview=====================  
There are two PCBs were designed for the mouse-glove. The Main Board and RaspberryPi Expansion Board. Aiming to ensure the I2C for long-distance communication two P82B96 was used for both mouse-glove (integrated on mainboard) and Expansion Board. It actually increases the cost of hardware. Therefore in some cases (the distance between glove and RaspberryPi is relatively short), the hardware design could be simplified by omitting the buffer design and used I2C directly.

==================Optimization=================  
The PCB design is just a prototype for verification. SMD 1206 package resistors and capacitors are used could be replaced by a small package with the same parameter. For the wiring layout, there is also large-leaved leeway since the limited technology for manufacturing the PCB board. It could also be optimized. 
