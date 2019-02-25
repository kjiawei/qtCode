#include"server.h"
#include"thread_pool.h"
#include"kernel_list.h"

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
	tcpaddr.sin_addr.s_addr=htonl(INADDR_ANY);//INADDR_ANY改为服务器IP,主机IP
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

void *tcp_send(void *arg)
{
	char *msg=(char *)arg;
	int ret;
	printf("%s\n",msg);
	ret=send(tcpsock,msg,MSG_LEN,0);
	if(ret==-1)
	{
		perror("send");
		return;
	}
	return;
}

void *tcp_recv(void *arg)
{
	int ret;
	char msg[MSG_LEN]={0};
	ret=recv(tcpsock,msg,MSG_LEN,0);
	if(ret<=0)
	{
		perror("recv");
		exit(0);
	}
	printf("%s\n",msg);
}

void *pri(void* arg)
{
	struct thread_pool *mypool=(struct thread_pool *)arg;
	while(1)
	{
		printf("ing_thread = %d task = %d\n",mypool->ing_pth,mypool->effect_task);
		sleep(1);
	}
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
	fd_set readfd;//select机制:I/O端口的复用
	fd_set errorfd;
	struct thread_pool *pth_pool=malloc(sizeof(struct thread_pool));
	struct task *task_head=task_create();
	thread_pool_init(pth_pool,task_head);
	tcp_init();// pthread_t text;// pthread_create(&text,NULL,pri,(void *)pth_pool);
	if(maxfd<tcpsock) maxfd=tcpsock;
	while(1)
	{
		FD_ZERO(&readfd);
		FD_SET(tcpsock,&readfd);
		FD_SET(STDIN_FILENO,&readfd);
		ret=select(maxfd+1,&readfd,NULL,NULL,NULL);
		if(ret==-1)
		{
			perror("select");
			return -1;
		}
		if(FD_ISSET(tcpsock,&readfd)) task_add(tcp_recv,NULL,pth_pool);
		if(FD_ISSET(STDIN_FILENO,&readfd))
		{
			printf("请按照格式发送信息:(IP:内容)");
			scanf("%s",msg);
			task_add(tcp_send,(void *)msg,pth_pool);
			usleep(10000);
		}
	}
}