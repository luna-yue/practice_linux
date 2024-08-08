#pragma once
#include <iostream>
#include <vector>
#include <semaphore.h>
#include <pthread.h>

template <class T>
class ringqueue
{
  
     public:
    ringqueue(int sz)
    :q(sz),cap(sz),p_pos(0),c_pos(0){
        sem_init(&datacnt_sem,0,0);
        sem_init(&spacecnt_sem,0,sz);
        pthread_mutex_init(&c_mutex, nullptr);
        pthread_mutex_init(&p_mutex, nullptr);
    }
    void P(sem_t& sem)//信号量--
    {
        sem_wait(&sem);
    }
    void V(sem_t&sem)//信号量++
    {
        sem_post(&sem);
    }
    void Lock(pthread_mutex_t & m)
    {
        pthread_mutex_lock(&m);
    }
    void Unlock(pthread_mutex_t & m)
    {
        pthread_mutex_unlock(&m);
    }
    //两个信号量的和等于cap 当生产者生产满 将阻塞 消费者消费空 也会阻塞
    void push(T tmp)//生产者向环形队列放入数据
    {
        P(spacecnt_sem);
        //在有多个生产者/消费者时，允许他们并发的处理数据/生产数据，但是同一时间访问环形队列的 只能有一个生产者/消费者（二者各一），因而用锁保证安全性
        //并且申请信号量是可以并发的 尽量减少锁的范围
        Lock(p_mutex);
        q[p_pos++]=tmp;
        p_pos%=cap;
        Unlock(p_mutex);
        V(datacnt_sem);
    }
    T pop()//消费者取出数据
    {
        P(datacnt_sem);
        Lock(c_mutex);
        T tmp=q[c_pos++];
        c_pos%=cap;
        Unlock(c_mutex);
        V(spacecnt_sem);
        return tmp;
    }
private:
 std::vector<T>q;
    int cap;
    int p_pos;
    int c_pos;
    sem_t datacnt_sem;
    sem_t spacecnt_sem;
    pthread_mutex_t c_mutex;
    pthread_mutex_t p_mutex;
};