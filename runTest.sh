#!/bin/bash

gcc -pthread prod-con.c -o runPC.out
./runPC.out > $1

python3 plot.py $1
rm $1

