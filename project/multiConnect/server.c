#include "myhead.h"
#include "my_thread_pool.c"
//服务器 UDP与飞秋通信(协议)-广播

#define IPMSG_BR_ENTRY 0x00000001UL  // 广播登录
static listp feiqhead = NULL;//飞秋在线客户的链表头
thread_pool *fhead;//接收飞秋信息的线程池链表头
int serversocket;//飞秋通信socket

typedef struct usrlist//在线客户端信息
{
	char ipbuf[16];//保存客户端IP
	unsigned short someport;//保存客户端端口号
	int somesock;//保存新的文件描述符
	int socktype;//tcp还是udp套接字
	struct usrlist *next;
	struct list_head mylist;
}ulist,*listp;

listp create_list()// 创建内核链表
{
	listp head = malloc(sizoef(ulist));
	INIT_LIST_HEAD(&(head->mylist));
	return head;
}

/* listp create_node()//添加新节点
{
	listp new = malloc(sizoef(ulist));
	//???
	return new;
} */

int insert_tail(listp head,listp new)// 尾插函数
{
	list_add_tail(&new->mylist,&head->mylist);
	return 0;
}

char *get_list(listp feiqhead)//获取用户信息列表
{
	listp q = sizeof(ulist);//指向feiqhead的循环指针
	listp retFq = create_list();//回传get_list节点
	//遍历链表,找到目标客户端
	list_for_each_entry(q,feiqhead->mylist,fhead->mylist)
	{
		if(q->next !=NULL)
			retFq->mylist.ipbuf = feiqhead->mylist.ipbuf;
	}
	//rbuf分割后的部分内容+需要发给飞秋客户端的信息(sbuf)
	return retFq;
}

/* void parseIP()//解析ip地址
{
	
} */

int parse(char *rbuf,struct sockaddr_in client)//解析收到的飞秋信息
{                            //client作用:回复飞秋信息
	char *str = rbuf;//下面分割字符串需要取址
	/*接收飞秋回复的分段信息*/
	int version;//程序版本号
	int data_pack;//数据包序列号
	char user[16];//用户名
	char host[16];//主机名
	int command;//命令码
	char contents_command[512];//命令内容get_list send_msg
	char msg_ip_addr[16];//ip地址,发信息来的飞秋客户端
	char contents_msg[512];//飞秋客户端发来的信息
	
	char *q;
	int count = 1;
	char send_msg[4096] = "1:2:jerry:administrator:";
	//q = atoi(rbuf); //换成单个atoi
		while((q=strsep(&str,":"))!=NULL))
		{
			switch(count++)
			{
				case 1:version = atoi(q);//飞秋版本号 
					printf("version = %d\n",version);
					break;
				case 2: data_pack = atoi(q) ; //数据包序列号
					printf("data_pack = %d\n",data_pack);
					break;
				case 3: strcpy(user,token); //用户(登陆)名
					printf("user = %s\n",user);
					break;
				case 4:strcpy(host,token);//主机
					/* if(q != 2425)//判断是否为飞秋客户端端口号
					{
						printf("不是飞秋端口号!\n");
					} */
					printf("host = %s\n",host);
					break;
				case 5://命令,飞秋自动回复288
				{	command = atoi(q);
					printf("command = %d\n",commond);
					if(q == 288)//刚才有收到服务端发送的内容
					if(sendto(serversocket,"1:2:3:5:33",16,0,(struct sockaddr*)&clientaddr,(socklen_t)(sizeof(clientaddr)))==-1)
							perror("sendto feiq failed!");
						break;
					/* bzero(sbuf,200);scanf("%s",sbuf); */
				}		//发消息给飞秋客户端,内容选择默认,只需发33即应答成功
				case 6://解析出来是自己定义命令 ip地址
				{	
					strcpy(contents_command,token);
					if(!strcmp(q,"get_list"))//strcmp(q,"send_msg")==0
					{
						/*以飞秋协议格式发送在线列表*/
						char buf_usr_list[4096]; /*= "xxx:xxx:xxx:xx::xxxx:send_list"*/
						sprintf(buf_usr_list, "%d:%d:%s:%s:%d:send_list", version, data_pack, user, host, command);
						ulist p = feiqhead;
						break;
					}	
					if(strcmp(q,"send_msg")==0)//获取在线用户信息并发给飞秋客户端
					{
						break;
					}
					break;
				}	
				case 7://解析ip地址并保存-转送 
					strcpy(msg_ip_addr,token);
					break;
				case 8://解析并发出真正信息给客户端 发给飞秋的
					break;
					char answer_string2[200];//list_info//get_list的回传
					int getIp;
					retFq = get_list(feiqhead);
					getIp = retFq->mylist.ipbuf;
					answer_string2 = sprintf(getIp);//rbuf分割后的部分内容+需要发给飞秋客户端的信息(sbuf)
					//拼接12345发给飞秋客户端(客户端会自动添加)
					sendto(serversock,answer_string2,200,0,(struct sockaddr *)&feiqaddr,socklen);//根据socktype来选择函数
			}
		}
}

void *recv_udp_feiq(void *arg)//获取飞秋连接信息-tcp点播
{	
	char *rbuf = (char *)arg; 
	while(1)//不断接收
	{
		recvfrom(rbuf,(struct sockaddr*)&clientaddr,50,0,(struct sockaddr *)&feiqaddr,&socklen);
		//printf("%s\n",rbuf);
		parse(rbuf);
		//将某个飞秋客户端信息添加到用户链表中
	}
	pthread_close(0);//NULL
}

int main(int argc,char **argv)
{
	//tcp发送txt文件
	//tcp广播未实现,点播
	
	//初始化线程池
	fhead= pool_init();//接收飞秋信息的链表头
	feiqhead = malloc(sizeof(ulist));//create_list();//飞秋在线客户的链表头初始化,初始化UDP
	pool_init(fhead,10);//为接收飞秋信息准备10个线程
	
	feiqhead->next = NULL;
	
	int ret;//判断线程创建
	char *ssbuf;//连接飞秋后第一次发送的内容-连接信息
	char rbuf[200];//连接飞秋后第一次回传的内容
	ssbuf = "1:2:jerry:administrator:success";
	//char buf[16]="1:2:3:5:1:pengsir";保存飞秋连接信息
	int b;//判断绑定是否成功
	
	socklen = sizeof(struct sockaddr_in);
	struct sockaddr_in serveraddr;
	struct sockaddr_in feiqaddr;
	bzero(&serveraddr,socklen);
	bzero(&feiqaddr,socklen);
	
	int newsocket;
	//创建一个线程接收飞秋连接通信接收(即时复习)
	pthread_t myid;
	
	//设置服务端sock
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(2425);//飞秋通信端口
	serveraddr.sin_addr.s_addr = inet_addr("192.168.1.255");//htonl(INADDR_ANY);
	
	//1.创建飞秋通信相关socket
	int serversock,feiqsock;
	serversock = socket(AF_INET,SOCK_DGRAM,0);//udp与飞秋通信
	if(serversock == -1){perror("serversock create failed!\n");return -1;}
	
	int sinsize = 1,on = 1;
	setsockopt(serversock,SOL_SOCKET,SO_REUSEADDR,&sinsize,sizeof(int));//取消端口绑定限制
	setsockopt(serversock,SOL_SOCKET,SO_BROADCAST,&on,sizeof on);//广播
	
	b = bind(serversock,(struct sockaddr *)&serveraddr,socklen);//2.飞秋通信bind
	if(b == -1){perror("bind failed!\n");return -1;}
	
	//下面这句作用是什么
	serveraddr.sin_addr.s_addr = inet_addr("192.168.1.255");
	
	while(1)
	{
		//3.发送一条上线通知给飞秋客户端
		sendto(serversock,ssbuf,200,0,(struct sockaddr *)&feiqaddr,socklen);//根据socktype来选择函数
		//把接收飞秋信息的任务交给线程池去完成
		
		//发一条给自己以过滤get_list
		//sendto(serversock,ssbuf,200,0,(struct sockaddr *)&serveraddr,socklen);
		//连接上飞秋获取第一次回传的内容
		recvfrom(serversock,rbuf,200,0,(struct sockaddr *)&feiqaddr,&socklen);
		
		
		
		ret = pthread_create(&myid,NULL,recv_udp_feiq,NULL);
		if(ret == -1){perror("create pthread failed!\n");return -1;}
		
		//task_add(fhead,recv_udp_feiq,rbuf);
		//task_add要10个吗,如何判断需要添加多少任务和线程
	}
	
	//销毁线程池
	thread_pool_destroy(fhead);
	//关闭socket
	close(serversock);close(feiqsock);
	return 0;
}

/*tcp
socket()
bind()
listen()
while(1)
{
	accept()
	add_task(recv_tcp,);//recv_tcp接收某个客户端发送来的信息
	tcp客户端功能:1.发信息send:ip  地址:端口:真正的信息
	服务器通过判断ip遍历链表是做tcp通信还是飞秋
	2.收发文件 
	3.获取在线用户
	
	feiq：send_msg:ip地址:真正的信息 发送信息  
	get_list 获取用户链表
}*/

/*开发板*/