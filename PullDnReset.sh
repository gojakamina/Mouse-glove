#!/bin/bash
echo current pin mode:
raspi-gpio get 17-18
raspi-gpio get 22-23
raspi-gpio get 27
raspi-gpio set 17-18 pd
raspi-gpio set 22-23 pd
raspi-gpio set 27 pd
echo pin mode after setting:
raspi-gpio get 17-18
raspi-gpio get 22-23
raspi-gpio get 27
echo PIN17,18,22,23,27 has been set to pull-down
