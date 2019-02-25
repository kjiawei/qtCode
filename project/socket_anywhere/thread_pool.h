#ifndef _THREAD_POOL_H_
#define _THREAD_POOL_H_

struct task
{
	void *(*handler)(void *);
	void *arg;
	struct task *next;
};

struct thread_pool
{
	int effect_task;
	int ing_pth;
	int thread_on_num;
	bool on_off;
	pthread_t arr_id[100];
	pthread_t current_id;
	pthread_mutex_t lock1;
	pthread_cond_t cond1;
	struct task *task_head;
};

extern struct task *task_create();
extern struct task *task_del(struct task *head,struct task *del);
extern struct task task_add(void *(*func)(void *),void *arg,struct thread_pool *mypool);
extern void *execute(void *arg);
extern int thread_pool_init(struct thread_pool *mypool,struct task *head);
#endif
