#include"thread.h"
#include"threadpool.h"
#include<stdlib.h>
#include<unistd.h>
using namespace std;
pthread_mutex_t lock;
void* add(void * p)
{
    pair<int,int>x=*(static_cast<pair<int,int>*>(p));
    pthread_mutex_lock(&lock);
    cout<<x.first<<"+"<<x.second<<"="<<x.first+x.second<<endl;
    pthread_mutex_unlock(&lock);
}
int main()
{
    
    pthread_mutex_init(&lock,nullptr);
   threadpool x(5,add);
   x.start();
   srand(time(0));
   vector<pair<int,int>>mem;
   for(int i=1;i<=10;i++)
   {
     int a=rand()%10;
     int b=rand()%10;
     mem.push_back({a,b});
     x.push(&mem[i-1]);
     pthread_mutex_lock(&lock);
     cout<<a<<"+"<<b<<"=?"<<endl;
      pthread_mutex_unlock(&lock);
      
      {sleep(5);}
   }
   //return 0;
}