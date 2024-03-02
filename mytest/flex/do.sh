#!/bin/bash

#v1
flex set_calc_v1.l
gcc lex.yy.c -o set_calc_v1



#v2
flex  --outfile set_calc_v2.c set_calc_v2.l
gcc set_calc_v2.c -o set_calc_v2

#v3
bison -d set_calc_v3.y # �����﷨������
flex set_calc_v3.l # ���ɴʷ�������
gcc -std=c99 -o set_calc_v3 set_calc_v3.tab.c lex.yy.c # �������ɿ�ִ���ļ�
##./set_calc_v3 < test.set

