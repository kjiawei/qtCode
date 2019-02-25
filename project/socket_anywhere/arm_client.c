#include"server.h"
#include"thread_pool.h"
#include"kernel_list.h"

/*
author：yang_junyi
带线程池的socket通信,及跟飞秋通信
*/

static int tcpsock;
static int flag=OFF;
static int maxfd=2;

int tcp_init()
{
	int ret;
	int i=1;
	int on = 1;
	int addrlen=sizeof(struct sockaddr_in);
	struct sockaddr_in tcpaddr;
	bzero(&tcpaddr,sizeof(struct sockaddr_in));
	tcpaddr.sin_family=AF_INET;
	tcpaddr.sin_port=htons(4000);
	tcpaddr.sin_addr.s_addr=inet_addr("192.168.1.117");
	tcpsock=socket(AF_INET,SOCK_STREAM,0);
	if(tcpsock==-1)
	{
		perror("tcpsock");
		exit(0); 
	}
	while(1)
	{
	ret=connect(tcpsock,(struct sockaddr *)&tcpaddr,addrlen);
	if(ret==-1)
	{
		printf("第%d次连接失败\n",i++);
		sleep(1);
	}else break;
	}
}

void *recv_process(void *arg)
{
	int ret;
	int cout=1;
	char *str;
	char *delim=":";
	char msg[MSG_LEN]={0};
	char *p=msg;
	ret=recv(tcpsock,msg,MSG_LEN,0);
	if(ret<=0)
	{
		perror("recv");
		exit(0);
	}
	while(str=strsep(&p,delim))//str不能直接使用,用新的字符数组接收后再通过系统使用使用
	{
		switch(cout++)
		{
			case 1:printf("ip:%s\n",str);break;
			case 2:printf("order:%s\n",str);break;
			default:break;
		}
	}
	system(str);//str为命令
}

void out(int sig)
{
	close(tcpsock);
	exit(0);
}

int main()
{
	char msg[MSG_LEN]={0};
	int ret;
	int i=0;
	fd_set readfd;
	fd_set errorfd;
	struct thread_pool *pth_pool=malloc(sizeof(struct thread_pool));
	struct task *task_head=task_create();
	thread_pool_init(pth_pool,task_head);
	tcp_init();
	// pthread_t text;
	// pthread_create(&text,NULL,pri,(void *)pth_pool);
	if(maxfd<tcpsock) maxfd=tcpsock;
	while(1)
	{
		printf("等待接受命令ING.....\n");
		FD_ZERO(&readfd);
		FD_SET(tcpsock,&readfd);
		ret=select(maxfd+1,&readfd,NULL,NULL,NULL);
		if(ret==-1)
		{
			perror("select");
			return -1;
		}
		if(FD_ISSET(tcpsock,&readfd)) task_add(recv_process,NULL,pth_pool);
	}
}
