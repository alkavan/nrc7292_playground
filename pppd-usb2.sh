#!/bin/sh

# 192.168.200.1 is the IP of the device, 192.168.200.7 is mapped to your host machine.

sudo pppd -detach noauth local nocrtscts modem \
/dev/ttyUSB2 192.168.200.1:192.168.200.7 115200
