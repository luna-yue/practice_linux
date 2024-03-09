 #include <sys/types.h>
 #include <sys/stat.h>
  #include <fcntl.h>
 #include<iostream>
  #include<unistd.h>
 using namespace std;
 #define path "./namedpipe"
 int main()
 {
      
      int fd=open(path,O_WRONLY);
      if(fd==-1)
      {
        cout<<"open fail"<<endl;
        return 0;
      }
      while(1)
      {
        cout<<"enter:(q 退出)"<<endl;
        string s;
        cin>>s;
        if(s=="q")
        {cout<<"client quit"<<endl;break;}
        s+='\0';
        write(fd,s.c_str(),s.size());
        
      }
     // cout<<"client quit"<<endl;
      close(fd);
 }