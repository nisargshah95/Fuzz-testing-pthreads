#!/bin/bash

gcc -pthread prod-con.c -o runPC.out
sudo ./runPC.out > $1

python3 plot.py $1
