#!/bin/bash

gcc -o tinyc tinyc.c
./tinyc

 python pysim.py pcode_1.asm  -d

python3 pysim.py pcode_3.asm -da

