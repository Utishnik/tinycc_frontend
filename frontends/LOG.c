#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>

char *PathLogFile="LogInsideCompiler.log";


void SetPathLogFile(char *new_path)
{
    if(!new_path) printf("inside compiler error file = %s\nLine = %d\tfunction = %s",__FILE__,__LINE__,__func__);
    PathLogFile=new_path;
}

int not_log_cnter_symbols(char *str,char s)
{
    if(!str) {
        printf("inside compiler error file = %s\nLine = %d\tfunction = %s",__FILE__,__LINE__,__func__);
        return false;
    }  
    int len=strlen(str);
    int res=0;
    for(int i=0;i<len;i++)
        if(str[i]==s)
            ++res;
    return res;
}

bool Log_Write(char *fmt,...)
{
    va_list ap;
    int cnt_arg=not_log_cnter_symbols(fmt,'%');
    if(!cnt_arg) {
        printf("inside compiler error file = %s\nLine = %d\tfunction = %s",__FILE__,__LINE__,__func__);
        return false;
    }
}
