#include <fcntl.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include <iostream>
#include <sys/syscall.h>

using namespace std;

const int MAX_EPOLL_EVENTS = 1000;
const int MAX_MSG_LEN = 1024;

void setFdNonblock(int fd)
{
    fcntl(fd, F_SETFL, fcntl(fd, F_GETFL) | O_NONBLOCK);
}

void err_exit(const char *s){
    printf("error: %s\n",s);
    exit(0);
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

int create_socket(const char *ip, const int port_number)
{
    struct sockaddr_in server_addr = {0};
    /* ����ipv4ģʽ */
    server_addr.sin_family = AF_INET;           /* ipv4 */
    /* ���ö˿ں� */
    server_addr.sin_port = htons(port_number);
    /* ����������ַ */
    if(inet_pton(server_addr.sin_family, ip, &server_addr.sin_addr) == -1){
        err_exit("inet_pton");
    }
    /* ����socket */
    int sockfd = socket(PF_INET, SOCK_STREAM, 0);
    if(sockfd == -1){
        err_exit("socket");
    }
    /* ���ø���ģʽ */
    int reuse = 1;
    if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) == -1)
    {
        err_exit("setsockopt");
    }
    /* �󶨶˿� */
    if(bind(sockfd, (sockaddr *)&server_addr, sizeof(server_addr)) == -1){
        err_exit("bind");
    }
    /* ���ñ����� */
    if(listen(sockfd, 5) == -1){
        err_exit("listen");
    }
    return sockfd;
}

int main(int argc, const char *argv[])
{
    /* ��ȡ���������� */
	/*
    if(argc < 3){
        printf("usage:%s ip port\n", argv[0]);
        exit(0);
    }
    const char * ip = argv[1];
    const int port = atoi(argv[2]);
	*/
	const char * ip = "localhost";
    const int port = 1234;
	
	print_info();

    /* �����׽��� */
    int sockfd = create_socket(ip, port);
    printf("success create sockfd %d\n", sockfd);
    setFdNonblock(sockfd);

    /* ����epoll */
    int epollfd = epoll_create1(0);
    if(epollfd == -1) err_exit("epoll_create1");

    /* ���sockfd��epollfd��Ȥ�б� */
    struct epoll_event ev;
    ev.data.fd = sockfd;
    ev.events = EPOLLIN ;
    if(epoll_ctl(epollfd, EPOLL_CTL_ADD, sockfd, &ev) == -1){
        err_exit("epoll_ctl1");
    }

    /* ����һ���б����ڴ��wait�����ص�events */
    struct epoll_event events[MAX_EPOLL_EVENTS] = {0};
    /* ��ʼ�ȴ�������epoll�Ϲ���ȥ���¼� */

	char r[32];
    while(1){
        /* �ȴ��¼� */
        //printf("begin wait\n");
		// �ȴ���������������
		int wait_ms = 1;
        int number = epoll_wait(epollfd, events, MAX_EPOLL_EVENTS, wait_ms); 
        //printf("end wait\n");
        if(number > 0){
            /* ���������¼� */
            for (int i = 0; i < number; i++)
            {
                int eventfd = events[i].data.fd;
                /* ��������¼���fd��sockfd����˵���������������ˣ�������Ҫaccept�� */
                if(eventfd == sockfd){
                    printf("accept new client...\n");
                    struct sockaddr_in client_addr;
                    socklen_t client_addr_len = sizeof(client_addr);
                    int connfd = accept(sockfd, (struct sockaddr *)&client_addr, &client_addr_len);
                    setFdNonblock(connfd);

                    /* accept֮����Ҫ���ļ����������뵽�����б��� */
                    struct epoll_event ev;
                    ev.data.fd = connfd;
                    ev.events = EPOLLIN;
                    if(epoll_ctl(epollfd, EPOLL_CTL_ADD, connfd, &ev) == -1){
                        err_exit("epoll_ctl2");
                    }
                    printf("accept new client end.\n");
                }
                /* ���������fd����sockfd���Ǿ����¼ӵ�connfd */
                else{
                    /* �������ݣ�ֱ�������س���Ȼ����ʾ�����ݡ� */
                    //printf("read start...\n");
                    while(1){
                        int ret = read(eventfd, &r, 32);
                        if(ret > 0){
                            printf("%s\n", r);
                        }
                        if (ret < 0){
                            printf("read error.\n");
                            break;
                        }
                    }
                    //printf("read end.\n");
                }
            }
        }

        sleep(1);
    }
}

