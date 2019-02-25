#include <iostream>
#include<string>
#include <pthread.h>

extern "C"
{
#include<string.h>
#include<pthread.h>
#include <unistd.h>
}

using namespace std;

struct task
{
    void *(*func)(void *);
    void *arg;
    struct task *next;
};

class Pthread_pool
{
public:
    Pthread_pool(int thread_num=1);
    void set_pthread_num(int num);
    void handler();
    void task_add(void *func(void *),void *arh=NULL);
    bool stop_recycl();
    bool threadpool_run();
    int del_thread(int num);
    int add_thread(int num);
    friend void *execute(void *arg);
    ~Pthread_pool();
private:
    bool shutdown;
    int effect_task;
    int effect_thread;
    int thread_num;
    struct task *task_head;
    pthread_t current_id;
    pthread_t arr_id[100];
    pthread_mutex_t lock;
    pthread_cond_t cond;
};

Pthread_pool::Pthread_pool(int thread_num)
{
    effect_task=0;
    shutdown=true;
    this->thread_num=thread_num;
    task_head=new task;
    memset(arr_id,0,sizeof(arr_id));
    pthread_mutex_init(&lock,NULL);
    pthread_cond_init(&cond,NULL);
}

void Pthread_pool::set_pthread_num(int num)
{
    thread_num=num;
}

void Pthread_pool::handler()
{
    pthread_mutex_unlock(&lock);
}

void *execute(void *arg)
{
    Pthread_pool *pool=(Pthread_pool *)arg;
    struct task *p;
    while(1)
    {
       // pthread_cleadup_push(handler,NULL);
        pthread_mutex_lock(&pool->lock);
        while(pool->effect_task==0 && pool->shutdown==false)
        {
            pthread_cond_wait(&pool->cond,&pool->lock);
        }
        if(pool->effect_task==0 && pool->shutdown==true)
        {
           pool->current_id=pthread_self();
            pthread_mutex_unlock(&pool->lock);
            pthread_exit(NULL);
        }
        p=pool->task_head->next;
        pool->task_head->next=p->next;
        pool->effect_task--;
        pthread_mutex_unlock(&pool->lock);
        //pthread_cleanup_pop(0);

        pthread_setcancelstate(PTHREAD_CANCEL_DISABLE,NULL);
        p->func(p->arg);
        pthread_setcancelstate(PTHREAD_CANCEL_ENABLE,NULL);
        delete p;
    }
    pthread_exit(NULL);
}

bool Pthread_pool::threadpool_run()
{
    int i;
    shutdown=false;
    for(i=0;i<thread_num;i++)
    {
        pthread_create(&arr_id[i],NULL,execute,(void *)this);
    }
    cout<<"启动完毕"<<endl;
    return true;
}

bool Pthread_pool::stop_recycl()
{
    int i;
    shutdown=true;
    for(i=0;i<thread_num;i++)
    {
        pthread_join(arr_id[i],NULL);
        thread_num--;
    }
    return true;
}

void Pthread_pool::task_add(void *func(void *),void *arg)
{
    struct task *p=task_head;
    struct task *newtask=new task;
    newtask->func=func;
    newtask->arg=arg;
    newtask->next=NULL;
    if(task_head->next==NULL)   task_head->next=newtask;
    else
    {
        while(p->next!=NULL)    p=p->next;
        p->next=newtask;
    }
    effect_task++;
    pthread_cond_broadcast(&cond);
}

int Pthread_pool::add_thread(int num)		//添加线程函数
{
    int i=0;
    while(1)
    {
        if(num<=0)
        {
            cout<<"输入错误，请重新输入:";
            cin>>num;
        }
        else if(shutdown==true)
        {
            cout<<"线程池已关闭,请重新启动后添加线程"<<endl;
            return -1;
        }
        else break;
    }
    while(arr_id[i]!=0) i++;
    for(;i<i+num;i++)
    {
        pthread_create(&arr_id[i],NULL,execute,(void *)this);
        thread_num++;
    }
    return 0;
}

int Pthread_pool::del_thread(int num)			//删除线程函数
{
    int i=0;
    if(thread_num<num)
    {
        cout<<"需要回收线程大于现有有效线程总数，无法回收\n";
        return -1;
    }
    if(thread_num==0 )
    {
        printf("\n");
        printf("线程总数已经为零\n");
        return -1;
    }
    shutdown=true;
    for(;i<num;i++)
    {
        pthread_cond_signal(&cond);
        usleep(2000);
        pthread_join(current_id,NULL);
        thread_num--;
    }
    shutdown=false;
    return 0;
}

Pthread_pool::~Pthread_pool()
{
    stop_recycl();
}

int main()
{
    cout << "Hello World!" << endl;
    return 0;
}

