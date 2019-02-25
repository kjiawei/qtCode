#include"server.h"
#include"kernel_list.h"
#include"thread_pool.h"

#define INVALID 10

static int udpsock;
static int tcpsock;
static int maxfd=2;

struct usr_list
{
	char ip[16];
	char usr_name[50];
	char com_name[50];
	unsigned short port;
	int selfsock;
	int protocol;
	int tcp_flag;
	struct list_head list;
};

struct data
{
	struct usr_list *usr;
	struct usr_list *sender;
	char msg[MSG_LEN];
};

struct usr_list *create_head()
{
	struct usr_list *head=malloc(sizeof(struct usr_list));
	bzero(head,sizeof(struct usr_list));
	INIT_LIST_HEAD(&head->list);
	return head;
}

struct usr_list *create_new()
{
	struct usr_list *new=malloc(sizeof(struct usr_list));
	bzero(new,sizeof(struct usr_list));
	new->list.next=NULL;
	new->list.prev=NULL;
	return new;
}

void *udprecmsg_process(void* arg)
{
	struct usr_list *usr=(struct usr_list *)arg;
	struct usr_list *someone=malloc(sizeof(struct usr_list));
	struct usr_list *pos;
	char msg[500]={0};
	char buf[500]={0};
	char q[20]={0};
	char *delim=":";
	char *str;
	char *p=buf;
	int cout=1;
	int ret;
	int order=0;
	int addrlen=sizeof(struct sockaddr_in);
	struct sockaddr_in clientaddr;
	bzero(someone,sizeof(struct usr_list));
	bzero(buf,200);
	ret=recvfrom(udpsock,buf,200,0,(struct sockaddr *)&clientaddr,&addrlen);
	if(ret<=0) return;
		while(str=strsep(&p,delim))
		{
			switch(cout++)
			{
				case 1:printf("程序版本号:%s\n",str);break;
				case 2:printf("数据包序列号:%s\n",str);break;
				case 3:printf("用户名:%s\n",str);
						strcpy(someone->usr_name,str);
						break;
				case 4:printf("主机号:%s\n",str);
						strcpy(someone->com_name,str);
						break;
				case 5:printf("命令：%s\n",str);
						if(strncmp(str,"6291457",7)==0) order=ONLINE;
						else if(strncmp(str,"6291459",7)==0) order=ONLINE;
						else if(strncmp(str,"6291458",7)==0) order=OFFLINE;
						else if(strncmp(str,"288",3)==0) order=NEWS;
						break;
				case 6:printf("传送信息:%s\n",str);strcpy(msg,str);break;
				default:break;
			}
		}
	if(order==NEWS)
	{
		if(strcmp(msg,"get_list")==0)
		{
			sprintf(buf,"1:2:%s:%s:288:%s",someone->usr_name,someone->com_name,pos->ip);
			list_for_each_entry(pos,&usr->list,list)
			{
				sprintf(q,"\n%s",pos->ip);
				strcat(buf,q);
				bzero(q,20);
			}
			sendto(udpsock,buf,sizeof(buf),0,(struct sockaddr *)&clientaddr,addrlen);
		}
		else if((str=strsep(&p,delim))!=NULL)
		{
			strcpy(someone->ip,msg);
			bzero(msg,sizeof(msg));
			strcpy(msg,str);
		}
		list_for_each_entry(pos,&usr->list,list)
		{
			if(strcmp(pos->ip,someone->ip)==0 && pos->protocol==TCP)
			{
				tcp_send(pos,msg);
				break;
			}
			else if(strcmp(pos->ip,someone->ip)==0 && pos->protocol==UDP)
			{
				udp_send(pos,msg);
				break;
			}
		}
		free(someone);
		someone=NULL;
	}
	else if(order==OFFLINE)
	{
		list_for_each_entry(pos,&usr->list,list)
		{
			if(strcmp(pos->ip,inet_ntoa(clientaddr.sin_addr))==0) break;
		}
		if(pos!=usr) 
		{
			if(*pos->ip!=0)
			{
			printf("用户%s离线了\n",pos->ip);
			bzero(pos->ip,sizeof(pos->ip));
			list_del(&pos->list);
			free(pos);
			pos=NULL;
			}
		}
	}
	else if(order==ONLINE)
	{
		list_for_each_entry(pos,&usr->list,list)
		{
			if(strcmp(pos->ip,inet_ntoa(clientaddr.sin_addr))==0) goto end;
		}
		stpcpy(someone->ip,inet_ntoa(clientaddr.sin_addr));
		someone->port=ntohs(clientaddr.sin_port);
		someone->protocol=UDP;
		list_add_tail(&someone->list,&usr->list);
		printf("用户%s上线了\n",someone->ip);
		sendto(udpsock,"1:2:server:PC0:33",18,0,(struct sockaddr *)&clientaddr,addrlen);
	}
	end:return;
}

void *tcprecmsg_process(void *arg)
{
	struct usr_list *pos;
	struct data *transfer=(struct data *)arg;
	char name[50]={0};
	char msg[MSG_LEN]={0};
	char ip[16];
	char *delim=":";
	char *str;
	char *p=transfer->msg;
	int ret;
	int cout=1;
	unsigned short port;
	while(str=strsep(&p,delim))
		{
			switch(cout++)
			{
				case 1:printf("ip地址:%s\n",str);
						strcpy(ip,str);
						break;
				case 2:printf("传输信息:%s",str);
						sprintf(msg,"%s:%s",transfer->sender->ip,str);
						break;
				default:break;
			}
		}
	list_for_each_entry(pos,&transfer->usr->list,list)
	{
		if(strcmp(pos->ip,ip)==0 && pos->protocol==TCP)
		{
			tcp_send(pos,msg);
			break;
		}else if(strcmp(pos->ip,ip)==0 && pos->protocol==UDP)
		{
			udp_send(pos,msg);
			break;
		}
	}
}

int udp_send(struct usr_list *send_obj,char *msg)
{
	char udpmsg[MSG_LEN]={0};
	int ret;
	int addrlen=sizeof(struct sockaddr);
	struct sockaddr_in objaddr;
	objaddr.sin_family=AF_INET;
	objaddr.sin_port=htons(send_obj->port);
	objaddr.sin_addr.s_addr=inet_addr(send_obj->ip);
	sprintf(udpmsg,"1:2:%s:PC0:288:%s",send_obj->ip,msg);
	printf("要传输的信息是:%s\n",msg);
	ret=sendto(udpsock,udpmsg,MSG_LEN,0,(struct sockaddr *)&objaddr,addrlen);
	if(ret==-1)
	{
		perror("udu send");
		return -1;
	}
	return 0;
}

int tcp_send(struct usr_list *send_obj,char *msg)
{
	int ret;
	ret=send(send_obj->selfsock,msg,MSG_LEN,0);
	if(ret==-1)
	{
		perror("tcp send");
		exit(0);
	}
	printf("发完收工TCP\n");
	return 0;
}

void *store_tcpusr(void* arg)
{
	char msg[256]={0};
	int ret;
	int newsock;
	int addrlen=sizeof(struct sockaddr_in);
	struct usr_list *usr=(struct usr_list *)arg;
	struct usr_list *new=malloc(sizeof(struct usr_list));
	struct usr_list *pos;
	struct sockaddr_in clientaddr;
	bzero(&clientaddr,sizeof(clientaddr));
	newsock=accept(tcpsock,(struct sockaddr *)&clientaddr,&addrlen);
	if(newsock==-1)
	{
		perror("newsock");
		exit(0);
	}
	if(newsock>maxfd) maxfd=newsock;
	strcpy(new->ip,inet_ntoa(clientaddr.sin_addr));
	bzero(&new->usr_name,sizeof(new->usr_name));
	bzero(&new->com_name,sizeof(new->com_name));
	new->port=ntohs(clientaddr.sin_port);
	new->selfsock=newsock;
	new->protocol=TCP;
	list_add_tail(&new->list,&usr->list);
	printf("TCP用户%s已连接\n",new->ip);
	new=NULL;
}

int del_tcp(struct usr_list *pos)
{
		close(pos->selfsock);
		printf("对用户%s已做离线处理\n",pos->ip);
		list_del(&pos->list);
		free(pos);
		pos=NULL;
		return 0;
}

int udp_init()
{
	int ret;
	int on=1;
	int addrlen=sizeof(struct sockaddr_in);
	struct sockaddr_in udpaddr;
	struct sockaddr_in selfaddr;
	struct timeval overtime;
	bzero(&overtime,sizeof(struct timeval));
	overtime.tv_usec=5000;
	udpaddr.sin_family=AF_INET;
	udpaddr.sin_port=htons(2425);
	udpaddr.sin_addr.s_addr=inet_addr("192.168.1.255");
	
	selfaddr.sin_family=AF_INET;
	selfaddr.sin_port=htons(2425);
	selfaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	udpsock=socket(AF_INET,SOCK_DGRAM,0);
	if(udpsock==-1)
	{
		perror("udpsock");
		return -1;
	}
	setsockopt(udpsock,SOL_SOCKET,SO_BROADCAST,&on,sizeof(on));
	ret=bind(udpsock,(struct sockaddr *)&selfaddr,addrlen);
	if(ret==-1)
	{
		perror("bind1");
		return -1;
	}
	setsockopt(udpsock, SOL_SOCKET, SO_RCVTIMEO, (char*)&overtime, sizeof(struct timeval));
	char buf[50]="1:2:yang:PC0:2:student";
	sendto(udpsock,buf,sizeof(buf),0,(struct sockaddr *)&udpaddr,addrlen);
	strcpy(buf,"1:2:yang:PC0:1:student"); 
	sendto(udpsock,buf,sizeof(buf),0,(struct sockaddr *)&udpaddr,addrlen);
	return 0;
}

int tcp_init()
{
	int ret;
	int on = 1;
	int addrlen=sizeof(struct sockaddr_in);
	struct sockaddr_in tcpaddr;
	bzero(&tcpaddr,sizeof(struct sockaddr_in));
	tcpaddr.sin_family=AF_INET;
	tcpaddr.sin_port=htons(4000);
	tcpaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	tcpsock=socket(AF_INET,SOCK_STREAM,0);
	if(tcpsock==-1)
	{
		perror("tcpsock");
		exit(0); 
	}
	setsockopt(tcpsock,SOL_SOCKET,SO_BROADCAST,&on,sizeof(on));
	ret=bind(tcpsock,(struct sockaddr *)&tcpaddr,addrlen);
	if(ret==-1)
	{
		perror("bind2");
		exit(0);
	}
	listen(tcpsock,20);
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

int main()
{
	char tcpmsg[MSG_LEN]={0};
	int ret;
	int i=1;
	fd_set readfd;
	fd_set errorfd;
	struct usr_list *pos;
	struct usr_list *usr=create_head();
	struct task *task_head=task_create();
	struct thread_pool *pth_pool=malloc(sizeof(struct thread_pool));
	struct timeval overtime;
	bzero(&overtime,sizeof(struct timeval));
	overtime.tv_usec=100000;
	thread_pool_init(pth_pool,task_head);
	udp_init();
	tcp_init();
	pthread_t text;
	pthread_create(&text,NULL,pri,(void *)pth_pool);//监测线程池工作状态和任务链表状态
	if(maxfd<udpsock) maxfd=udpsock;
	if(maxfd<tcpsock) maxfd=tcpsock;
	while(1)
	{
		FD_ZERO(&errorfd);
		FD_ZERO(&readfd);
		list_for_each_entry(pos,&usr->list,list)
		{
			if(pos->protocol==TCP) 
			{
				FD_SET(pos->selfsock,&readfd);
				FD_SET(pos->selfsock,&errorfd);
			}
		}
		FD_SET(udpsock,&readfd);
		FD_SET(tcpsock,&readfd);
		ret=select(maxfd+1,&readfd,NULL,&errorfd,&overtime);
		while(i){  sleep(1); i--; }
		if(ret==-1)
		{
			perror("select");
			return -1;
		}
		if(FD_ISSET(udpsock,&readfd)) task_add(udprecmsg_process,(void *)usr,pth_pool);
		if(FD_ISSET(tcpsock,&readfd)) task_add(store_tcpusr,(void *)usr,pth_pool);
		list_for_each_entry(pos,&usr->list,list)
		{
			if(FD_ISSET(pos->selfsock,&readfd))
			{
				ret=recv(pos->selfsock,tcpmsg,MSG_LEN,0);
				if(ret<=0)
				{
					del_tcp(pos);
					break;
				}
				struct data *transfer=malloc(sizeof(struct data));
				bzero(transfer,sizeof(struct data));
				strcpy(transfer->msg,tcpmsg);
				transfer->usr=usr;
				transfer->sender=pos;
				task_add(tcprecmsg_process,(void *)transfer,pth_pool);//用户链表，所穿信息，对应用户
				transfer=NULL;
			}
			// if(FD_ISSET(pos->selfsock,&errorfd))
			// {
				// pos->tcp_flag=OFF;
				// task_add(del_tcp,(void *)usr,pth_pool);
			// }
		}	
	}
	return 0;
}