#include "myhead.h"
//ubuntu客户端
int main(int argc,char **argv)
{
	int b;//判断绑定是否成功
	int con;//判断con是否成功
	struct sockaddr_in myaddr;
	bzero(&myaddr,socklen);
	socklen = sizeof(struct sockaddr_in);
	int serversocket,newsocket;
	//char buf[16]="1:2:3:5:1:pengsir";//保存飞秋连接信息
	char sbuf[200];
	
	//设置服务端sock
	myaddr.sin_family = AF_INET;
	myaddr.sin_port = htons(2425);//飞秋通信端口
	myaddr.sin_addr.s_addr = inet_addr("192.168.1.255");//htonl(INADDR_ANY);不能绑定自己ip
	
	//创建socket
	int mysock,newsock;
	mysock = socket(AF_INET,SOCK_DGRAM,0);//udp与飞秋通信
	if(mysock == -1){perror("mysock create failed!\n");return -1;}
	
	int sinsize = 1;
	setsockopt(mysock, SOL_SOCKET, SO_REUSEADDR, &sinsize, sizeof(int));
	
	//b = bind(mysock,(struct sockaddr *)&myaddr,socklen);//2425
	//if(b == -1){perror("bind failed!\n");return -1;}
	
	while(1)
	{
		bzero(sbuf,200);
		newsock = accept(mysock,(struct sockaddr*)&feiqaddr,&socklen);//接收飞秋
		sendto(mysock,sbuf,200,0,(struct sockaddr *)&myaddr,socklen);//根据socktype来选择函数
		//把接收飞秋信息的任务交给线程池去完成
	}
	
	//关闭socket
	close(mysock);close(newsock);
	return 0;
}