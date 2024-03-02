#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string>
#include <iostream>
#include <limits>
#include <pthread.h>
#include <sys/syscall.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <sys/ipc.h>
#include <sys/shm.h>


// 也可以在run.sh的编译语句里加 -D RAW
//#define RAW
//#define MUTEX
//#define COND
//#define SEM
#define RW

using namespace std;

#define SUB_PROCESS_NUM 3

static bool closing = false;
static int *global_counter;
static int sock_fd = 0;

void err_exit(const char *s){
    printf("error: %s\n",s);
    exit(0);
}

int create_socket(const char *ip, const int port_number, int idx = 0)
{
	int ret = 0;
    struct sockaddr_in server_addr = {0};
    /* 设置ipv4模式 */
    server_addr.sin_family = AF_INET;           /* ipv4 */
    /* 设置端口号 */
    server_addr.sin_port = htons(port_number);
    /* 设置主机地址 */
    if(inet_pton(PF_INET, ip, &server_addr.sin_addr) == -1){
        err_exit("inet_pton");
    }

	// 客户端绑定自己的socket，可以省略
	struct sockaddr_in cli_addr = {0};
    cli_addr.sin_family = AF_INET;
    cli_addr.sin_port = htons(10000 + idx);
    if(inet_pton(PF_INET, ip, &cli_addr.sin_addr) == -1){
        err_exit("inet_pton");
    }

    /* 建立socket */
    sock_fd = socket(PF_INET, SOCK_STREAM, 0);
    if(sock_fd == -1){
        err_exit("socket");
    }

  	if(bind(sock_fd, (sockaddr *)&cli_addr, sizeof(cli_addr)) == -1){
        err_exit("bind");
	}

    ret = connect(sock_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1;
	if(ret < 0){
		cout << ret << endl;
        err_exit("connect");
    }

    return sock_fd;
}

static char buff[32];
void exec_func_wrapper(int idx, int val)
{
	sprintf(buff, " [%d]: %d\n", idx, val);
	cout << buff;

    write(sock_fd, buff, 32);
}

void print_info(char *ext_info = NULL)
{
	int i = 1;
	int *p = (int *)malloc(sizeof(int));
	
	cout << "cur info for :" ;
	if(ext_info != NULL)
	{
		cout << ext_info;
	}

	cout << endl;
	cout << "    getpid: " << getpid() << endl;
	cout << "    getppid: " << getppid() << endl;
	cout << "    syscall gettid: " << syscall(SYS_gettid) << endl;
	cout << "    pthread_self: " << pthread_self() << endl;
	cout << "    stack addr: " << &i << endl;
	cout << "    heap addr: " << p << endl;
	cout << endl;

	free(p);
}


void sub_process_routine(int idx)
{
	sprintf(buff, "child %d: %d routine start ", idx, getpid());
	print_info(buff);

	// 链接服务器
	sock_fd = create_socket("localhost", 1234, idx);

	int self_val = 0;

	do{
		if(closing)
		{
			break;
		}

		if(self_val != *global_counter)
		{
			exec_func_wrapper(idx, self_val);

			//cout << "child " << idx << "set val from " << self_val << " to " << *global_counter << endl;
			self_val = *global_counter;
		}

		usleep(1000);

	}while(1);
}

int create_shm()
{
	key_t key = 1888;
	size_t size = 32;
	int shmid = shmget(key, size, IPC_CREAT|0666);
	if(shmid < 0)
	{
        err_exit("shmget");
	}

	int *shmadd = (int*)shmat(shmid, NULL, 0);
	if(shmadd < 0)
	{
        err_exit("shmat");
	}

	global_counter = shmadd;
	return 0;
}

int main(int argc, const char *argv[])
{
	srand(unsigned(time(NULL)));
	
	print_info("main");

	create_shm();

	int idx = 0;
	pid_t pid;
	for(idx = 0; idx < SUB_PROCESS_NUM; ++idx)
	{
		pid = fork();
		if(pid == 0) // 子进程
		{
			break;
		}	
		if(pid < 0)
		{
			cout << "invalid fork ret " << pid << endl;
		}
	}

	if(pid == 0)
	{
		sub_process_routine(idx);
		exit(0);
	}

	// 父进程逻辑：
	// 处理输入
	char c;
	do{
		cin >> c;
		cout << c;
		if(c == ']')
		{
			closing = true;
			break;
		}
		(*global_counter)++;
		cout << "global_counter: " << *global_counter << endl;

	}while(1);

	// 回收进程
	for(int i = 0; i < SUB_PROCESS_NUM; ++i)
	{
		pid_t p = wait(NULL);
		cout << "child " << p << " recycled" << endl;
	}
	
    return 0;

}

