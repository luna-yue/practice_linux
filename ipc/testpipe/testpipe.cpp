#include<iostream>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
using namespace std; 
int arr[2];
void writer()
{
   const char *s="hello im cd";
    //int id=getpid();
    /*string tmp;
    while(id)
    {
        tmp+=(id%10);
        id/=10;
    }*/
    //reverse(tmp.begin(),tmp.end());
    //s+=tmp;
    write(arr[1],s,strlen(s));
    return;
}
void reader()
{
  char s[1024];
  read(arr[0],s,1000);
  cout<<"father:"<<getpid()<<s<<endl;
}
int main()
{
   
    pipe(arr);
    int tmp=fork();
    if(tmp==0)
    {
        close(arr[0]);
        writer();
        exit(0);
    }
    close(arr[1]);
    reader();
    close(arr[0]);
    return 0;
}