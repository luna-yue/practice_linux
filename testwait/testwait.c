#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
void run(int x)
{
  for(int i=1;i<=1;i++)
  {
    printf("child %d my id =%d\n",x,getpid());
  }
  if(x==1)
  {
    x/=0;
  }
 // exit(x);
 return;
}
int sb[11];
int main()
{
  for(int i=1;i<=10;i++){
  pid_t id=fork();
  if(id==0)
  {
      run(i);
    exit(i);
  }
  else{
      sb[i]=id;
  }
  }
 // sleep(20);
  for(int i=1;i<=10;i++)
  {
   int status;
  pid_t id= waitpid(sb[i],&status,0);
   printf("%d------\n",i);
   printf("get %d : id =%d\n",WEXITSTATUS(status),id);
  // if(!WIFEXITED(status))
     printf("%d\n",status&0x7F);
  }
  
}
