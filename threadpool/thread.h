#pragma once
#include<pthread.h>
#include<string>
#include<stdio.h>
#include<string>
#include<iostream>
using namespace std;
template<class T,class ARGS>
class thread
{
public:
     thread(std::string _name,ARGS _arguments,T (*_func)(ARGS))
     :name(_name),arguments(_arguments),func(_func)
     {
        //printf("gouzao done\n");
     }
     //使用静态的原因是 非成员函数隐含一个this 参数，与pthread_create 的要求不符
     static void* Handler(void* args)
     {
        //printf("start start\n");
        thread<T,ARGS>* p = static_cast<thread<T,ARGS>*>(args);
       (p->func)(p->arguments);
        //printf("start done\n");
        return nullptr;
     }
     void start()
     {
       // printf("start start");
        pthread_create(&id,nullptr,Handler,this);
        isrunning=1;
        cout<<name<<" is running."<<endl;
     }
     void join()
     {
        if(!isrunning)
        {
            return ;
        }
        pthread_join(id,nullptr);
        cout<<name<<" join finished"<<endl;
     }
     string whoami()
     {
      return name;
     }
private:
     std::string name;
     pthread_t id;
     int isrunning;
     ARGS arguments;
     //T args;
     T (*func)(ARGS);
};