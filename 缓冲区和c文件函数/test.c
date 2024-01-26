#include "MyStdio.h"
#define filename "test.txt"
int main()
{
   FILE * tmp=_fopen("test.txt","a");
   const char *arr="hello sb   \n";
   for(int i=1;i<=10;i++){
     _fwrite(arr,strlen(arr),1,tmp);sleep(1);
   }
   _fclose(tmp);
}
