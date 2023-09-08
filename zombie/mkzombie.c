#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
int main()
{
 // printf("begin:%d\n",getpid());
  pid_t id=fork();
  if(id==0)
  {
   //bin while(1)
    {//srvleep(3);
    printf("child%d\n",getpid());
    exit(0);
    }
    
  }
  else if(id>0)
  {
    printf("p%d",getpid());
    while(1)
    {sleep(5);
      
     // exit(0);
    }
    sleep(1000);
  }
}
