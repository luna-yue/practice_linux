 #include <sys/types.h>
 #include <sys/stat.h>
 #include<sys/ipc.h>
 #include<sys/shm.h>
  #include <fcntl.h>
 #include<iostream>
  #include<unistd.h>
  #include<stdio.h>
  #include<errno.h>
  #include<string.h>
 using namespace std;
 #define path "."
 #define proj_id 1234
 #define sz 8192
 int main()
 {
    key_t key=ftok(path,proj_id);
    if(key==-1)
    {
        cout<<"ftok fail"<<endl;
        return 0;
    }
     int shmid=shmget(key,sz,IPC_CREAT|IPC_EXCL|0666);
     if(shmid==-1)
     {
        cout<<"shmget fail"<<endl;
        printf("%s\n",strerror(errno));
     }
     cout<<shmid<<endl;
   char *buf= (char*) shmat(shmid,nullptr,0);
    // cout<<buf<<endl;
    printf("%x",buf);
     while(1)
     {
        cout<<"enter:(q to quit):";
        fgets(buf,sz-1,stdin);
       
     }
     shmdt(buf);

 }