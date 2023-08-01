 #include <unistd.h>
#include"rooler.h"
#define sign '='
char rooler[105]={0};
char show[7]="\\-/|";
void rool()
{
  int cnt=0;
  int round=0;
  while(cnt<=100)
{ 
    printf("%c%-100s%c%c%c%c%c%d%c\r",'[',rooler,']','[',show[round%4],']','[',cnt,']');
    
    rooler[cnt++]=sign;
  //  printf("%c%c%c\r",'[',show[round%4],']');
    round++;
    fflush(stdout);
    if(cnt<100)
      rooler[cnt]='>';
    usleep(40000);
 }
printf("\n");
}
