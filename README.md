# Mouse-glove

## Project in Real Time Embedded Programming 5 (Team 15)

### Description
In this project, the aim is to create a wireless glove that acts as a mouse. Users will be able to controll the pointer with the motion of their hand. Additional features of the Mouse-glove will enable users to make right and left clicks. Structural details of the system can be found below.

![image](https://github.com/gojakamina/Mouse-glove/raw/master/Schematic.png)

### Members
* Amina Gojak: Sensor data processing, GUI & documentation.
* Tong He: Hardware design & part of docmumentation.
* Yuzhen Liu: Mouse event code & media.


### Packages/Libraries installation

```diff
WiringPi: $sudo apt-get install wiringpi 
//For GPIO control and I2C  
```
```diff
iir: https://github.com/berndporr/iir1 
//For iir filter 
```
```diff
xdo: $sudo apt-get install -y libxdo-dev 
//For simulate mouse action
```
library for LSM9DS1 has been integrated in the project.

```diff
boost test : sudo apt-get install libboost-all-dev 
//For unit testing
```

### Install
```diff
mkdir build
cd build
cmake ..  
make
```

### Test
After finishing Installation
```diff
cd build  
make test
```
Only run Mouse click and position reset threads:
```diff
cd bin
./ClickTest
```
### Run
#### NOTE: Due to wiringPi being unable to setup GPIO to pull up in RaspberryPi 4B, execucate script is necessary.
```diff
//Set pullup:
chmod +x PullUpSet.sh
./PullUpSet.sh

//Reset back to pulldown:
chmod +x PullDnReset.sh
./PullDnReset.sh
```
Without GUI
```diff
cd bin  
./main
```
With GUI see in ./GUI/README.md

[Documentation](https://gojakamina.github.io/Mouse-glove/)

[Follow us on twitter](https://twitter.com/glove_mouse)
