#!/bin/bash

bison -vdty calc.y

flex calc.l

gcc -o calc y.tab.c lex.yy.c

./calc

# 1+2*3
