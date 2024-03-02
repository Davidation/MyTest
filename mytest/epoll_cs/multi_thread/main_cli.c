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
#include <semaphore.h>


// Ҳ������run.sh�ı��������� -D RAW
//#define RAW
//#define MUTEX
//#define COND
//#define SEM
#define RW

using namespace std;

#define THREAD_NUM 1000
#define EXEC_NUM_PER_TIME 10

static bool closing = false;
static int global_counter = 0;
static int sock_fd = 0;

void err_exit(const char *s){
    printf("error: %s\n",s);
    exit(0);
}

int create_socket(const char *ip, const int port_number)
{
	int ret = 0;
    struct sockaddr_in server_addr = {0};
    /* ����ipv4ģʽ */
    server_addr.sin_family = AF_INET;           /* ipv4 */
    /* ���ö˿ں� */
    server_addr.sin_port = htons(port_number);
    /* ����������ַ */
    if(inet_pton(PF_INET, ip, &server_addr.sin_addr) == -1){
        err_exit("inet_pton");
    }

	/*
	// �ͻ��˰��Լ���socket������ʡ��
	struct sockaddr_in cli_addr = {0};
    cli_addr.sin_family = AF_INET;
    cli_addr.sin_port = htons(10000);
    if(inet_pton(PF_INET, ip, &cli_addr.sin_addr) == -1){
        err_exit("inet_pton");
    }
	*/

    /* ����socket */
    sock_fd = socket(PF_INET, SOCK_STREAM, 0);
    if(sock_fd == -1){
        err_exit("socket");
    }

	/*
  	if(bind(sock_fd, (sockaddr *)&cli_addr, sizeof(cli_addr)) == -1){
        err_exit("bind");
	}
	*/

    ret = connect(sock_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1;
	if(ret < 0){
		cout << ret << endl;
        err_exit("connect");
    }

    return sock_fd;
}

static char c[32];

void exec_func(int idx, int val)
{
	sprintf(c, " [%d]: %d\n", idx, val);
	cout << c;

    write(sock_fd, c, 32);
}

// ��̬��ʼ�������ж�̬��init��ʼ����ʽ
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
void exec_func_mutex(int idx, int val)
{
	pthread_mutex_lock(&mutex);
	sprintf(c, " aaaaaaaaaaaaaaaaaaaaa [%d]: %d\n", idx, val);
	cout << c;

    write(sock_fd, c, 32);
	pthread_mutex_unlock(&mutex);
}

static int cond_val = 0;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void exec_func_cond(int idx, int val)
{
	// ����������Ҫ��ϻ�����ʹ��
	pthread_mutex_lock(&mutex);
	while((cond_val % EXEC_NUM_PER_TIME) < (idx % EXEC_NUM_PER_TIME))
	{
		cout << idx << " waiting" << endl;
		pthread_cond_wait(&cond, &mutex);
	}
	++cond_val;
	sprintf(c, " bbbbbbbbbbbbbb [%d]: %d\n", idx, val);
	cout << c;

    write(sock_fd, c, 32);
	pthread_mutex_unlock(&mutex);

	// ����Ҫbroadcast������signal��
	// ��Ϊ��20-29�Ž���ͬʱ�ȴ��ź�����signal����ȷ��20�ŷ���֮���ѵ���21��
	// �������21�ţ���ô21-29�Ż���������
	//pthread_cond_signal(&cond); 
	pthread_cond_broadcast(&cond);
}

static int sem_val = 0;
sem_t sem;
void exec_func_sem(int idx, int val)
{
	// ע��������Ϊ�ź�����ʼ������1����д����cֻ��һ�ݣ����ܻ������Ⱦ
	if(sem_wait(&sem) == 0)
	{
		// ÿ��10���̣߳�ֻ���ĸ�����д����
		// ��Ϊ����û������sem_val��ֵ�ǲ��ɿ��ģ����Բ������ϸ�ȷ����4��
		if(sem_val >= global_counter * 4)
		{
			sem_post(&sem);
			return;
		}

		sprintf(c, " ccccccccccccc [%d]: %d\n", idx, val);
		cout << c;

		write(sock_fd, c, 32);

		// ����
		pthread_mutex_lock(&mutex);
		sem_val++;
		pthread_mutex_unlock(&mutex);

		sem_post(&sem);
	}
}

pthread_rwlock_t rw = PTHREAD_RWLOCK_INITIALIZER;
static int rw_val = 0;
void exec_func_rw(int idx, int val)
{
	// 10����0�ź�1���̸߳���д
	if(idx % 10 == 0 || idx % 10 == 1) 
	{
		pthread_rwlock_wrlock(&rw);
		++rw_val;

		sprintf(c, " dddddd write [%d]: %d\n", idx, rw_val);
		cout << c;

		write(sock_fd, c, 32);
		pthread_rwlock_unlock(&rw);
	}
	// �����̸߳����
	else
	{
		pthread_rwlock_rdlock(&rw);
		sprintf(c, " dddddd [%d]: %d\n", idx, rw_val);
		cout << c;

		write(sock_fd, c, 32);

		pthread_rwlock_unlock(&rw);
	}
}
void exec_func_wrapper(int idx, int val)
{
#ifdef RAW
	exec_func(idx, val);
#endif

#ifdef MUTEX
	exec_func_mutex(idx, val);
#endif

#ifdef COND
	exec_func_cond(idx, val);
#endif

#ifdef SEM
	exec_func_sem(idx, val);
#endif

#ifdef RW
	exec_func_rw(idx, val);
#endif

}

void *thread_routine(void *arg)
{
	int* p_val= (int* )arg;
	int self_idx = *p_val;

	int self_val = 0;
	do{
		if(closing)
		{
			break;
		}

		if(self_val != global_counter)
		{
			// ÿ����EXEC_NUM_PER_TIME���̹߳���
			if((global_counter % (THREAD_NUM / EXEC_NUM_PER_TIME)) == (self_idx / EXEC_NUM_PER_TIME))
			{
				exec_func_wrapper(self_idx, self_val);
			}

			self_val = global_counter;
		}

		usleep(1000);
	}while(1);
	cout << "pthread exit " << self_idx << endl;

	pthread_exit((void *)"pthread exit");
}

int main(int argc, const char *argv[])
{
	srand(unsigned(time(NULL)));
	sem_init(&sem, 0, 2); //SEMģʽ��ͬʱֻ��2�߳̿���д

	// ���ӷ�����
	sock_fd = create_socket("localhost", 1234);

	// �����߳�
	pthread_t id[THREAD_NUM];
	int arg[THREAD_NUM];
	int val, ret;
	for(int i = 0; i < THREAD_NUM; ++i)
	{
		arg[i] = i;
		ret = pthread_create(&id[i], NULL, thread_routine, &arg[i]); 
		if(ret != 0)
		{
			cout << "create error" << endl;
			exit(1);
		}
	}

	// ��������
	char c;
	do{
		cin >> c;
		cout << c;
		if(c == ']')
		{
			closing = true;
			break;
		}
		global_counter++;
		cout << "global_counter: " << global_counter << endl;

	}while(1);

	// �����߳�
	void *a;
	for(int i = 0;i < THREAD_NUM;++i)
	{
		pthread_join(id[i], &a); // ���̼߳�ʹ�Ѿ�ִ�н����ˣ����̻߳��ǿ���join��һ�����Ҳȷʵ�����߳�Ҫ�����߳̽����Ž���
		cout << "get idx " << i << " id[" << id[i] << "] " << "exit return -- " << (char*)a << endl;
	}
	sem_destroy(&sem);
	
    return 0;

}

