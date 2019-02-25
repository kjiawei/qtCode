#include"server.h"

int main()
{
	char msg[500]={0};
	char *p1="hello";
	char *p2="world";
	strcpy(msg,p1);
	sprintf(msg,"%s %s",msg,p2);
	printf("%s\n",msg);
	return 0;
}