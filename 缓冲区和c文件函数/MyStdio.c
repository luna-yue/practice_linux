#include"MyStdio.h"
#define buffermode 3 // 1 行刷新，2，满后刷新 ，3 即刻刷新
#define quanxian 0666
FILE* _fopen(const char* filename,const char *mode)
{
   if(filename==NULL)
    return NULL;
   int fd=-1;
   if(strcmp(mode,"w")==0){
      fd=open(filename,O_WRONLY|O_CREAT|O_TRUNC,quanxian);
   }
   else if(strcmp(mode,"a")==0)
   {
     fd=open(filename,O_WRONLY|O_CREAT|O_APPEND,quanxian);
   }
   else if(strcmp(mode,"r")==0)
   {
     fd=open(filename,O_RDONLY);
   }
   if(fd==-1)
     return NULL;
   FILE* tmp=(FILE*)malloc(sizeof(FILE));
   //tmp->outbuffer=malloc(maxsize);
   tmp->fileno=fd;
   return tmp;
}
void _fflush(FILE *stream)
{
  if(stream->outpos!=0)
  {
    write(stream->fileno,stream->outbuffer,stream->outpos);
    stream->outpos=0;
  }
}
void _fclose(FILE* stream)
{
  if(stream==NULL)
    return ;
  if(stream->outpos!=0)
  {
   _fflush(stream);
  }
  //frese(stream->outbuffer);
  free(stream);
}
int _fwrite(const void *ptr,int len,int cnt,FILE* stream)
{
 if(buffermode==1){//行刷新
  for(int i=0;i<cnt;i++)
  {
      memcpy(stream->outbuffer+stream->outpos,ptr,len);
     stream-> outpos+=len;
      if(stream->outpos!=0&&stream->outbuffer[stream->outpos-1]=='\n')
      {   _fflush(stream),stream->outpos=0;}
  }
 }
  else if(buffermode==2)//满后刷新
  {
    for(int i=0;i<cnt;i++){
      if(len+stream->outpos>maxsize)
       _fflush(stream);
      if(len+stream->outpos>maxsize)
      return -1;
     // stream->outpos+=len;
    memcpy(stream->outbuffer+stream->outpos,ptr,len);
    stream->outpos+=len;
    }  
    if(stream->outpos==maxsize)
      _fflush(stream),stream->outpos=0;
  }
  else if(buffermode==3)
  {
    for(int i=0;i<cnt;i++){
         //in if(len+outpos>maxsize)
           // fflush(stream);
         // stream->outpos+=len;
        memcpy(stream->outbuffer+stream->outpos,ptr,len);
        stream->outpos+=len;
          _fflush(stream),stream->outpos=0;
  }
 }
 return cnt*len;
}
int  _fread(void *ptr,int len,FILE* stream)
{
  if(stream==NULL)
    return 0;
  read(stream->fileno,ptr,len);
  return len;
}

