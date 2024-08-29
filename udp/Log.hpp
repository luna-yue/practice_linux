#pragma once

#include <iostream>
#include <time.h>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define SIZE 1024

#define Info 0
#define Debug 1
#define Warning 2
#define Error 3
#define Fatal 4

#define Screen 1
#define Onefile 2
#define Classfile 3

#define LogFile "log.txt"

class Log
{
public:
 Log()
 {
    printmethod=Screen;
    path="./log/";
 }
 void ch_printmethod(int method)
 {
     
     printmethod=method;
 }
 std::string level_to_string(int level)
 {
    if(level==0)
    return "Info";
    else if(level==1)
    return "Debug";
    else if(level==2)
    return "Warning";
    else if(level==3)
    return "Error";
    else if(level==4)
    return "Fatal";
 }
 void printlog(int level,std::string txt)
 {
    if(printmethod==1)
    {
        std::cout<<txt<<std::endl;
    }
    else if(printmethod==2)
    {
       print_onefile(LogFile,txt);
    }
    else if(printmethod==3)
    {
        std::string filename = LogFile;
        filename += ".";
        filename += level_to_string(level);
        print_onefile(filename,txt);
    }
 }
 void print_onefile(std::string filename,std::string txt)
 {
    std::string logname= path+filename;
    int fd=open(logname.c_str(),O_WRONLY | O_CREAT | O_APPEND, 0666);
    if(fd<0)
    return;
    write(fd,txt.c_str(),txt.size());
    close(fd);
 }
void operator()(int level, const char *format, ...)
    {
        time_t t = time(nullptr);
        struct tm *ctime = localtime(&t);
        char leftbuffer[SIZE];
        snprintf(leftbuffer, sizeof(leftbuffer), "[%s][%d-%d-%d %d:%d:%d]", level_to_string(level).c_str(),
                 ctime->tm_year + 1900, ctime->tm_mon + 1, ctime->tm_mday,
                 ctime->tm_hour, ctime->tm_min, ctime->tm_sec);

        va_list s;
        va_start(s, format);
        char rightbuffer[SIZE];
        vsnprintf(rightbuffer, sizeof(rightbuffer), format, s);
        va_end(s);

        // 格式：默认部分+自定义部分
        char logtxt[SIZE * 2];
        snprintf(logtxt, sizeof(logtxt), "%s %s", leftbuffer, rightbuffer);

        // printf("%s", logtxt); // 暂时打印
        printlog(level, logtxt);
    }
 private:
  std::string path;
  int printmethod;
};