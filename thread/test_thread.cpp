#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <unistd.h>
#include <pthread.h>
#define NUM 10
using namespace std;
void* runthread(void * arg)
{
    pthread_t id=pthread_self();
    cout<<"thread_id:>"<<id<<" "<<*(int*)arg<<"st"<<endl;
    //if(*(int*)arg==3)
    //{pthread_detach(pthread_self());sleep(5);cout<<"3 done"<<endl;}
    return nullptr;
}
int main()
{
    cout<<1<<endl;
    vector<int>rk(NUM);

    vector<pthread_t>thread_ids;
    for(int i=0;i<NUM;i++)
    {
        rk[i]=i;
        pthread_t tmp;
        pthread_create(&tmp,nullptr,runthread,&(rk[i]));
        //cout<<i<<" "<<tmp<<endl;
        thread_ids.push_back(tmp);
        
    }
    sleep(1);
    int x=4;
    for(int i=0;i<x;i++)
    pthread_detach(thread_ids[i]);
    cout<<x<<endl;
    for(int i=0;i<NUM;i++)
    {
        int n=pthread_join(thread_ids[i],nullptr);
         printf("n = %d, who = %d, why: %s\n", n, i, strerror(n));

    }
    return 0;
}