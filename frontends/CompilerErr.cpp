#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define LIBTCCAPI

int cnt_symbol_in_str(const char *str,char s)
{
	if(!str)printf("inside compiler error\n line = %d file = %s function = %s",__LINE__,__FILE__,__func__);
	int len=strlen(str);
	int res=0;
	for(int i=0;i<len;i++)
		if(str[i]==s) ++res;
	return res;
}

void Inter_Comp_Err(char *fmt,...)
{
	va_list ap;
	
}

