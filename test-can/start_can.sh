#!/bin/bash
sudo rmmod -f mcp251x
sudo modprobe mcp251x
sudo ip link set can0 up type can bitrate 500000

