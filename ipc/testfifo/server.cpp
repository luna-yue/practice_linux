 #include <sys/types.h>
 #include <sys/stat.h>
  #include <fcntl.h>
 #include<iostream>
 #include<unistd.h>
 #include<stdio.h>
 using namespace std;
 #define path "./namedpipe"
 int main()
 {
    int ck=mkfifo(path,0666);
      if(ck==-1)
      {
        cout<<"mkfifo fail"<<endl;
        return 0;
      }
    char *buf[1024];
    int fd = open(path,O_RDONLY);
    if(fd==-1)
      {
        cout<<"open fail"<<endl;
        return 0;
      }
    while(1)
    {
        int n=read(fd,buf,sizeof(buf));
        if(n==0)
        break;
        else if(n<0)
        {
            cout<<"read fail"<<endl;
            break;
        }
        
        printf("server get:%s\n");
    }
    cout<<"server quit"<<endl;
    close(fd);
    return 0;
 }