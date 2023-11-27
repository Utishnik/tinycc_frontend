#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>

int not_log_cnter_symbols(char *str,char s)
{
	if(!str) {
		printf("inside compiler error file = %s\nLine = %d\tfunction = %s",__FILE__,__LINE__,__func__);
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
}
