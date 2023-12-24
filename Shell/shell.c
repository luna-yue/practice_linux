#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<assert.h>
#define maxx 1024
char *argv[maxx];
char command[maxx];
int argc;
char nowpwd[maxx];
int lastexit=0;
void interact()
{
  
 // argc=0;
 // gets(buf);
 //bin char argv[argc++]
  //while(tmp)
  getcwd(nowpwd,maxx);//得到当前的路径
  printf("[%s@%s %s]$ ",nowpwd,getenv("USER"),getenv("HOSTNAME"));
  fgets(command,maxx,stdin);
 //procrintf("%s\n",command);
  command[strlen(command)-1]='\0';
}
int cut()
{
  int p=0;
 // printf("%s\n",command);
  char *tmp=strtok(command," ");
  while(tmp)
  {
    argv[p++]=tmp;
    tmp=strtok(NULL," ");
  }
  argv[p]=NULL;
  argc=p;
  //runeturn p;
  
 // for(int i=0;i<p;i++)
   // printf("%s\n",argv[i]);
  return p;
  
}
int buildrun()
{
  //int flag=0;
  if(argc==2&&strcmp(argv[0],"cd")==0)
  {
     chdir(argv[1]);
     getcwd(nowpwd,maxx);
    sprintf(getenv("PWD"),"%s",nowpwd);
     return 1;
  }
  else if(argc==2&&strcmp(argv[0],"echo")==0)
  {
    if(*argv[1]=='$')
    {
      char *op=getenv(argv[1]+1);
      if(op)
      printf("%s\n",op);
    }
    else
    {
        printf("%s\n",argv[1]);
    }
   return 1;

  }
  return 0;
}
void run()
{

  pid_t id=fork();
  if(id==0)
  {
  //  printf("%d\n",argc);
    execvp(argv[0],argv);
    exit(0);
  }
  else if(id<0)
  {
    perror("fail fork");
    return;
  }
  else{
    int status=0;
   pid_t rid= waitpid(id,&status,0);
    if(rid==id)
    {
      lastexit=WEXITSTATUS(status);
    }
    return;
  }
}
int main()
{
  while(1)
  {
   // run();
   // 得到命令
   interact();
   // 对得到的命令行字符串进行切割 存在argc中
  int now= cut();
  if(now==0)
    continue;
   //处理命令（分为内建和非内建）
 int c=  buildrun();
 if(!c)
   run();
  }
}
