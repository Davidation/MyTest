#!/bin/bash

g++ -Wall -lpthread main_svr.c -o server && g++ -Wall -lpthread main_cli.c -o client


#./server 
#./client 

# 服务器客户端通过1234端口进行通信 
# 客户端主线程生成1000个子线程，主线程每次输入一个字符后，有10个线程往1234端口的socket写数据
# 服务器收到数据后打印出来

# 有4种模式 
# - RAW： 不做线程同步管理，会发现服务器收到的数据是混乱的
# - MUTEX: 线程间做了互斥，会发现每次10个线程以随机顺序发送自己的数据，每个线程发送的数据是正确的
# - COND: 在互斥基础上做了同步，强制10个线程从前到后工作，接收端的数据按照顺序打印
# - SEM: 同一时刻允许多个(2个)线程发送，每次10个线程只有4个可以发送(因为没上锁会有问题，具体看代码的注释)
