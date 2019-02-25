#include <iostream>

extern "C"
{
#include <pthread.h>
#include <unistd.h>
}

using namespace std;

class Pthread
{
public:
    Pthread(void *(*func)(void *)=NULL,void *arg=NULL)
    {
        this->func=func;
        this->arg=arg;
        pthread_attr_init(&attr);
    }
    bool set_attr(int flag);
    bool set_func(void *func(void*),void *arg=NULL);
    bool pthread_start();

private:
    pthread_t id;
    pthread_attr_t attr;
    void *(*func)(void*);
    void *arg;
};

bool Pthread::set_attr(int flag)
{
   int ret;
   ret=pthread_attr_setdetachstate(&this->attr,flag);
   if(ret!=-1)
   {
       cerr<<"pthread_attr_setdetachstate"<<endl;
       return false;
   }
   return true;
}

bool Pthread::set_func(void *func(void *),void *arg)
{
    this->func=func;
    this->arg=arg;
    return true;
}

bool Pthread::pthread_start()
{
    int ret;
    ret=pthread_create(&id,&attr,func,arg);
    if(ret==-1)
    {
        cerr<<"pthread_create"<<endl;
        return false;
    }
    return true;
}

void *coutmath(void *arg)
{
    int i=1;
    while(1)
    {
    sleep(1);
    cout<<"第"<<i++<<"次"<<endl;
    }
}

int main()
{
    Pthread a(coutmath);
    a.pthread_start();
    while(1)
    {
        sleep(1);
        cout<<"我是主线程"<<endl;
    }
    cout << "Hello World!" << endl;
    return 0;
}

