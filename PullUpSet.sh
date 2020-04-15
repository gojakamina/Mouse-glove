#!/bin/bash
raspi-gpio set 17-18 pu
raspi-gpio set 22-23 pu
raspi-gpio get 17-18
raspi-gpio get 22-23
echo PIN17,18,22,23 has been set to pull-up