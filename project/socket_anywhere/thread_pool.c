#include"server.h"
#include"thread_pool.h"
#include"kernel_list.h"

struct task *task_create()
{
	struct task *new=malloc(sizeof(struct task));
	new->handler=NULL;
	new->arg=NULL;
	new->next=NULL;
	return new;
};

struct task *task_del(struct task *head,struct task *del)
{
	while(head->next!=del)
	head=head->next;
	head->next=del->next;
	del->next=NULL;
}

struct task task_add(void *(*func)(void *),void *arg,struct thread_pool *mypool) //添加任务链表函数
{
	struct task *new;
	struct task *tail;
	tail=mypool->task_head;
	new=task_create();
	new->handler=func;
	new->arg=arg;
	new->next=NULL;
	if(mypool->task_head->next==NULL) 
	{
		mypool->task_head->next=new;
	}
	else
	{
		while(tail=tail->next)
		{
			if(tail->next==NULL)
			{
				tail->next=new;
				break;
			}
		}
	}
	mypool->effect_task++;
	pthread_cond_signal(&mypool->cond1);
}	

void *execute(void *arg)                      //功能函数
{
	pthread_t selfid;
	selfid=pthread_self();
	struct thread_pool *mypool=(struct thread_pool *)arg;
	struct task *work_point;
	void (*unlock)(void *)=(void *)pthread_mutex_unlock;
	void *(*work_handle)(void *);
	void *work_arg;
	// struct task *work_task;
	// work_task=mypool->task_head->next;
	while(1)
	{
	pthread_cleanup_push(unlock,(void *)&mypool->lock1);
	pthread_mutex_lock(&mypool->lock1);
	while(mypool->on_off==false || mypool->effect_task==0) 
		{
			pthread_cond_wait(&mypool->cond1,&mypool->lock1);
			if(mypool->on_off==false) 
			{
				mypool->current_id=selfid;
				pthread_exit(0);
			}
			pthread_mutex_unlock(&mypool->lock1); 
		}
	mypool->effect_task--;
	work_handle=mypool->task_head->next->handler;
	work_arg=mypool->task_head->next->arg;
	work_point=task_del(mypool->task_head,mypool->task_head->next);
	mypool->ing_pth++;
	work_handle(work_arg); //执行对应函数功能
	mypool->ing_pth--;
	pthread_mutex_unlock(&mypool->lock1);
	pthread_cleanup_pop(0);
	}
}

int thread_pool_init(struct thread_pool *mypool,struct task *head)      //线程池初始化函数
{
	
	bzero(mypool->arr_id,sizeof(mypool->arr_id));
	int i;
	mypool->on_off=true;
	mypool->task_head=head;
	mypool->effect_task=0;
	mypool->thread_on_num=10;
	pthread_mutex_init(&mypool->lock1,NULL);
	pthread_cond_init(&mypool->cond1,NULL);
	mypool->ing_pth=0;
	for(i=0;i<10;i++)
	{
		pthread_create(&mypool->arr_id[i],NULL,execute,(void *)mypool);
	}
}
