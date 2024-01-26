#pragma once
#include<string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<stdlib.h>
#include<unistd.h>
//#include <cstdlib>
#define maxsize 10
typedef struct FileIo{
 int fileno;
 char outbuffer[maxsize];
 int outpos;
}FILE;
void _fflush(FILE*stream); 
FILE * _fopen(const char* filename,const char *mode);
int _fwrite(const void *ptr,int len,int cnt,FILE* stream);
int _fread(void *ptr,int len,FILE* stream);
void _fclose(FILE* stream);
