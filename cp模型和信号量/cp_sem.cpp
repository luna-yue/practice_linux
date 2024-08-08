#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <unistd.h>
#include <pthread.h>
#include<map>
#include"ringqueue.h"
using namespace std;
map<pthread_t,int>mem;
int cnt=0;
pthread_mutex_t coutlock;
void* producer(void* args)
{
    
    ringqueue<int>* q=static_cast<ringqueue<int>*>(args);
    while(1)
    {
        int tmp=cnt++;
        q->push(tmp);
        pthread_mutex_lock(&coutlock);
        cout<<"produce:>"<<tmp<<"   producerid:>"<<mem[pthread_self()]<<'\n';
        pthread_mutex_unlock(&coutlock);
        sleep(1);

    }
}
void* consumer(void *args)
{
    ringqueue<int>* q=static_cast<ringqueue<int>*>(args);
    while(1)
    {
        int tmp=q->pop();
         pthread_mutex_lock(&coutlock);
        cout<<"consume:>"<<tmp<<"   consumerid:>"<<mem[pthread_self()]<<'\n';
         pthread_mutex_unlock(&coutlock);
        sleep(1);
    }
}

int main()
{
    //cout<<1<<endl;
    pthread_mutex_init(&coutlock,nullptr);
   ringqueue<int>q(5);
   vector<pthread_t>cons;
   vector<pthread_t>prod;
   
   for(int i=1;i<=5;i++)
   {
    pthread_t tmp;
    pthread_create(&tmp,nullptr,consumer,&q);
    mem[tmp]=i;
    cons.push_back(tmp);
   }
   for(int i=1;i<=3;i++)
   {
     pthread_t tmp;
     pthread_create(&tmp,nullptr,producer,&q);
     mem[tmp]=i;
     prod.push_back(tmp);
   }
   for(int i=0;i<prod.size();i++)
   {
    pthread_join(prod[i],nullptr);
   }
   for(int i=0;i<cons.size();i++)
   {
    pthread_join(cons[i],nullptr);
   }
   
}