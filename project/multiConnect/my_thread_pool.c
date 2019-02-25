#include "myhead.h"

#define MAX_TASK_NUM	1000
#define MAX_ACTIVE_THREADS	20

//决定任务的节点:任务是由节点
struct task{
	void *(*handler)(void *arg);//代表任务的函数指针
	void *arg;//传递给函数指针的参数
	struct task *next;
};

//线程池结构体  重点：如何分析并封装
//理解：三者的关系->线程(thread_pool),线程实现任务(task),新增节点
typedef struct thread_pool{
	pthread_t *id;//用于存放多个线程的id号，不是int型,数组或指针
	unsigned task_num;//任务链表中有效任务数量
	pthread_mutex_t lock;//互斥锁与条件变量协调对任务链表的访问
	pthread_cond_t cond;
	unsigned active_pthread;//活跃线程的数量  不用int,unsigned保证输入的线程数量为正
	bool pool_state;//判断线程池是否存在的标志位
	struct task *head;//任务链表头
}thread_pool;

void closemutex(void *arg){//解锁
	pthread_mutex_unlock((pthread_mutex_t *)arg);
}

//线程处理函数:扣出节点并分析指针指向的任务,从头节点的下一个有效节点
//思路步骤：知道表头,扣下来后还要增加有效任务节点
//防止意外中断死锁用push-减当中被取消了
//lock&unlock之间代码就是临界区资源
//链表尾部添加任务,头节点下一处理任务
void *thread_fun(void *arg){
	thread_pool *pool=(thread_pool *)arg;
	//传什么参数,参数arg是初始化好的线程池
	struct task *q;//指向处理任务节点(被取出来包括的那个节点)
	while(1)
	{
		//调用函数防止死锁
		pthread_cleanup_push(closemutex,(void *)&pool->lock);
		pthread_mutex_lock(&pool->lock);
		
		//有效任务为0,线程池关闭(wait阻塞),直到添加任务后task不为0，调用signal唤醒
		while(pool->task_num == 0 && pool->pool_state==true){
			pthread_cond_wait(&pool->cond, &pool->lock);
		}
		//任务链表中没有任务并且线程池也关闭了
		if(pool->task_num==0 && pool->pool_state==false){
			pthread_mutex_unlock(&pool->lock);//记住
			pthread_exit(NULL);
		}
		//处理任务
		q = pool->head->next;
		pool->head->next = q->next;	
		pool->task_num --;
		
		pthread_mutex_unlock(&pool->lock);
		pthread_cleanup_pop(0);
	
		pthread_setcancelstate(PTHREAD_CANCEL_DISABLE,NULL);//记住
		(q->handler)(q->arg);//传入arg调用handler，再通过函数指针调用指向的函数
		pthread_setcancelstate(PTHREAD_CANCEL_ENABLE,NULL);//记住
		free(q); 
	}
	pthread_exit(NULL);
}

//初始化线程池:初始化结构体,创建线程
//法一 申请堆空间，新变量去设置;法二：返回地址，指针改变相当于重新初始化
bool pool_init(thread_pool *mypool,unsigned int threadnum){
	pthread_mutex_init(&mypool->lock,NULL);	
	pthread_cond_init(&mypool->cond,NULL);

	mypool->id = malloc(MAX_ACTIVE_THREADS * sizeof(pthread_t));
	mypool->task_num = 0;//任务数量
	mypool->active_pthread = threadnum;
	mypool->pool_state = true;
	mypool->head = malloc(sizeof(struct task));
	mypool->head->next = NULL;
	
	if(mypool->head == NULL || mypool->id == NULL){
		perror("申请空间失败");return false;
	}
	
	//创建threadnum个线程并封装进thread_pool
	int i;
	for(i=0;i < mypool->active_pthread;i++){
		if(pthread_create(&((mypool->id)[i]),NULL,thread_fun,(void *)mypool)!=0)//成功返回0
		{perror("创建线程出错");return false;}
	}
	return true;
}

//添加任务:节点+参数,head要共享
//与thread_fun是竞争关系
////////////////////////////////////////////2.函数指针 3.给函数指针的参数：有写没空
/* struct task */bool task_add(thread_pool *mypool,void *(*p)(void *arg),
								void *argument){
	//先准备好新的任务节点（封装）
	struct task *new = malloc(sizeof(struct task));
	//判断是否添加成功
	if(new == NULL){perror("申请空间失败");return false;}
	new->handler = p;//&((*handler)(void *arg)) = (*p)(void *):
	new->arg = argument;
	new->next = NULL;//malloc(sizeof(struct task));	
	pthread_mutex_lock(&mypool->lock);//为什么上锁
	if(mypool->task_num >= MAX_TASK_NUM){//超过就释放
		pthread_mutex_unlock(&mypool->lock);
		fprintf(stderr,"任务超过最大数\n");
		free(new);
		return false;
	}
	//往任务链表尾部插入新的任务节点
	/* mypool->head->next = new; */
	struct task *tmp =mypool->head;
	while(tmp->next != NULL){
		tmp = tmp->next;
	}
	tmp->next = new;
	mypool->task_num++;//当前任务数量加1
	//唤醒（解除阻塞）并上锁,为什么
	pthread_mutex_unlock(&mypool->lock);
	pthread_cond_signal(&mypool->cond);
	//pthread_cond_broadcast(&mypool->cond);//以广播形式通知所有的线程解除阻塞->销毁用
	
	//统计任务链表中有效任务的变量?
	return true;//new 为什么不是返回新增的任务
}

////////////////////////////////
//新增线程
//返回:实际加了多少
//模仿，需要记忆
////////////////////////////////
int thread_add(thread_pool *mypool,unsigned additional){
	if(additional == 0){return 0;}//判断新增的参数是否为0
	//声明新增后总的线程数变量,新增
	unsigned total_threads = mypool->active_pthread + additional;
	
	int i,actual_increment = 0;//实际增加
	for(i=mypool->active_pthread;//这时的i不是从0开始了
	i<total_threads&&i<MAX_ACTIVE_THREADS;i++){
		if(pthread_create(&((mypool->id)[i]),NULL,thread_fun,(void *)mypool)!=0){//语句合并
			perror("添加线程失败");
			if(actual_increment == 0){return -1;}break;
		}
		actual_increment++;
/*获取新增线程的属性
	调用pthread_create()生成
	更新: 活跃线程数量  id   总的*/
	}
	mypool->active_pthread += actual_increment;
	return actual_increment;
}

////////////////////////////////
//删除线程
//对传进来的参数进行判断，为0，就不用操作了
////////////////////////////////
int del_thread(thread_pool *mypool,unsigned int delnum){
	if(delnum==0){return mypool->active_pthread;}
	//定义剩余线程变量
	int remain_threads= mypool->active_pthread-delnum;
	remain_threads=remain_threads>0 ?remain_threads:1;//剩余线程是否大于0,至少保留1个!
	
	//用上面剩余变量和线程id控制删除,注意下标要减1
	int i;
	for(i=mypool->active_pthread-1;i>remain_threads-1;i--){
		errno = pthread_cancel(mypool->id[i]);//errno是系统定义的吗
			if(errno != 0) break;
	}
	//对操作结果进行判断，循环变量仍在最后一位则退出，否则返回存余线程数?
	if(i == mypool->active_pthread - 1)
		return -1;
	else{
		mypool->active_pthread = i+1;//局部变量i怎么理解
		return i+1;
	}
}

////////////////////////////////
//线程池销毁
////////////////////////////////
/* int */bool thread_pool_destroy(thread_pool *mypool){//函数返回值用了bool后面的return 就要跟false或true
	//销毁  锁 条件变量  指针id 释放线程池结构体指针mypool
	mypool->pool_state = false;//关闭线程池
	pthread_cond_broadcast(&mypool->cond);//之前没想到是这里用以广播形式通知所有的线程解除阻塞
	int i;
	for(i=0;i<mypool->active_pthread;i++){
		errno = pthread_join(mypool->id[i],NULL);
		if(errno != 0){
			printf("回收线程 id[%d] 错误:%s\n",i,strerror(errno));//之前没想到竟然返回那么多东西,销毁失败还能隔开的吗
		}else{
			printf("[%u] 已回收\n",(unsigned)mypool->id[i]);//用结构体指针显示已销毁的线程数吧
		}
	}
	
	free(mypool->head);
	free(mypool->id);
	free(mypool);
	//mypool->task_num = 0;
	return true;
}

void *fun1(void *arg){
	int n = (int)arg;
	
	printf("[%u][%s]==>新增任务将在%d秒内完成...\n",(unsigned)pthread_self(),__FUNCTION__,n);//__FUNCTION__为所属函数
	sleep(n);
	printf("[%u][%s]==>新增任务完成!\n",(unsigned)pthread_self(),__FUNCTION__);
	return NULL;
}

void *fun2(void *arg){
	int i = 0;
	while(1){
		sleep(1);
		printf("%d秒\n",++i);
	}
}

int main(void){
	pthread_t a;
	pthread_create(&a,NULL,fun2,NULL);
	//1.准备并初始化线程池
	thread_pool *main = malloc(sizeof(thread_pool));
	pool_init(main,2);//第二个参数为需要初始化的线程个数

	//2.投掷任务  //往任务链表添加任务
	printf("新增3个任务\n");
	task_add(main,fun1,(void *)(rand()%10));//第三个参数为传给线程处理函数的参数?  线程池功能函数
	task_add(main,fun1,(void *)(rand()%10));
	task_add(main,fun1,(void *)(rand()%10));
	
	//3.测试当前线程池线程数量
	printf("当前线程数量:%d\n",del_thread(main,0));
	
	sleep(9);
	//4.再次投掷任务
	printf("再新增2个任务\n");
	task_add(main,fun1,(void *)(rand()%10));
	task_add(main,fun1,(void *)(rand()%10));
	
	//5.再次添加线程
	int threadnum=2;//线程数量
	thread_add(main,threadnum);
	
	sleep(5);
	
	//6.移除线程
	printf("从线程池移除3个线程,""移除后线程数量:%d\n",del_thread(main,3));//移除后还剩3?
	
	//7.销毁线程池
	thread_pool_destroy(main);
	
	return 0;
	
}