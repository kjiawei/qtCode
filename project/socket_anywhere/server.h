#ifndef _SERVER_H_
#define _SERVER_H_

#include<stdio.h>
#include<string.h>
#include<strings.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <signal.h>
#include<pthread.h>
#include <signal.h>
#include <unistd.h>
#include <stdbool.h> 
#include <sys/socket.h>
#include <semaphore.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/mman.h>
#include <sys/un.h>
#include<sys/time.h>
#include<bits/time.h>
#include <time.h>

#define TCP 1
#define UDP 2
#define ONLINE 3
#define NEWS 4
#define OFFLINE 5
#define ON 6
#define OFF 7
#define ORDER_LEN 50
#define MSG_LEN 256

#endif