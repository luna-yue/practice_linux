#include<iostream>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<vector>
#include<errno.h>
using namespace std; 
vector<string>work;
int slaveid=0; int arr[2];
struct slave
{
  string name;
  int writefd;
  int id;
  slave(const string&n,int fd,int i)
  :name(n),id(i),writefd(fd){}
};
void workwork()
{
while(1){int cmdcode=0;
   int n=read(arr[0],&cmdcode,sizeof(int));
  // cout<<n<<endl;
   if(n==sizeof(int))
   {
     cout<<"slave:"<<slaveid<<"pid:"<<getpid()<<" "<<work[cmdcode]<<endl;
   }
   if(n==0)
   {
    //cout<<"quit"<<endl;
    break;
   }
}
}
void init(vector<slave>*channel)
{
    work.push_back("work1");
    work.push_back("work2");work.push_back("work3");work.push_back("work4");work.push_back("work5");
  for(int i=1;i<=10;i++)
  {
   
    int tmp=pipe(arr);
    if(tmp!=0)
    {
      cout<<"failed pipe"<<endl;
    }
    int id=fork();
    if(id==0)
    {
        close(arr[1]);
       // dup2(arr[0],0);
       // close(arr[0]);
        slaveid=i-1;
        workwork(); 
        cout<<"slave"<<i<<"exit"<<endl;
        exit(0);
       
    }
    close(arr[0]);
    cout<<"fd"<<arr[1]<<endl;
    string name="slave"+to_string(id);
    channel->push_back(slave(name,arr[1],id));
    //sleep(1);
  }
}

void ctrlslave(vector<slave>&channel)
{
    int n=10;
    srand(time(0));
    for(int i=1;i<=n;i++)
    {
      int wktodo=rand()%5;
      int slaveid=rand()%10;
      cout<<"call:"<<slaveid<<"pid:"<<channel[slaveid].id<<"todo:"<<wktodo+1<<endl;
      int tmp=write(channel[slaveid].writefd,&wktodo,sizeof(int));
      //cout<<tmp<<endl;
      if(tmp==-1)
      {
        cout<<errno<<endl;
      }
    }
}
void killslave(vector<slave>&channel)
{
    for(const auto &e:channel)
    {
      cout<<"close fd "<<e.writefd<<endl;
        close(e.writefd);
       // int statu;
        //cout<<"sb"<<endl;
       //waitpid(e.id,nullptr,0);
    }
    for(const auto &e:channel)
    {
      waitpid(e.id,nullptr,0);
    }
}
void debug(vector<slave>channel)
{
  for(auto&e:channel)
  {
    cout<<e.name<<" "<<e.id<<" "<<e.writefd<<endl;
  }
}
int main()
{
    vector<slave>tmp;
  init(&tmp);
  debug(tmp);
  ctrlslave(tmp);
  //cout<<1<<endl;
  killslave(tmp);
  return 0;
}