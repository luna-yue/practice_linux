#pragma once
#include<map>
#include<string>
#include<iostream>
#include<pthread.h>
#include<queue>
using namespace std;

class threadpool
{
public:
    threadpool(int x,void* (* _solve)(void*)):cnt(x),solve(_solve){
         pthread_mutex_init(&mutex, nullptr);
        pthread_cond_init(&cond, nullptr);
    }
    static void *handle_task(void * ts)
    {
        threadpool* p =static_cast<threadpool*>(ts);
        while (1)
        {
            pthread_mutex_lock(&(p->mutex));
            while(p->empty())
            {
                pthread_cond_wait(&(p->cond), &(p->mutex));
            }
            void* it=p->data.front();
            p->data.pop();
            pthread_mutex_unlock(&(p->mutex));
            p->solve(it);
            //cout<<"thread"<<" "<<p->mem[pthread_self()]<<" finish a work"<<endl;
        }
        return nullptr;
    }
    void push(void * _data)
    { pthread_mutex_lock(&mutex);
       data.push(_data);
       pthread_cond_signal(&cond);
       pthread_mutex_unlock(&mutex);
    }
    void start()
    {
        for(int i=1;i<=cnt;i++)
        {
            
         pthread_t tmp;
          pthread_create(&tmp,nullptr,handle_task,(void*)this);
          mem[tmp]=i;
        }
    }
   bool empty()
    {
        return data.empty();
    }
private:
    map<pthread_t,int>mem;
    queue<void*>data;
    void* (* solve)(void*);
    int cnt;
     pthread_mutex_t mutex;
    pthread_cond_t cond;
};