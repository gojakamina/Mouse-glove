==================Main Board===================  
5V-3.3V LDO.  
Sensor unit (LSN9DS1 based).  
I2C buffering unit (P82B91).  
vibration driver circuit.  
Connectors to Expansion Board, switchs, and vibration motor.

==================Connections===================  
```diff
To Switches:
Black------>GND  
Green------>Mode switch  
Pink------->Right button  
Blue------->Left button
```

```diff
Expansion Board:

3-way connector:
Similar to Switch connector

6-way connector, right to left
Red---------->5V
Orange------->3.3V
Black-------->GND
Yellow------->I2C_SCL
White-------->I2C_SDA
Grey--------->Motor control


```
![image](https://github.com/gojakamina/Mouse-glove/raw/master/PCB/MainBoard/MainBoard.png)
