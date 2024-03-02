#!/bin/bash

g++ -Wall main_svr.c -o server && g++ -Wall main_cli.c -o client


#./server localhost 1234
#./client localhost 1234


#服务器首先创建被动打开socket文件描述符，然后将该文件描述符加入到epoll兴趣列表。接下来进入循环。每当兴趣列表wait结束时，说明对应文件描述符可以进行操作。当有客户端连上被动打开socket文件描述符时，说明有客户端连上，被动打开文件描述符可以被accept。accept后所创建的新的文件描述符是与客户端通信的文件描述符，该文件描述符继续加入兴趣列表。当客户端发送数据时，该文件描述符也会产生可读信号，会导致wait结束，此时进入处理模式，读取并显示客户端所发送的数据。

