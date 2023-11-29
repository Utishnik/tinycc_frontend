#include <stdio.h>
#include <stdlib.h>
//todo stdarg.h для того чтобв было переменное число args

#define  InsideErrPrint(msg) printf("%s\tfile = %s\nfunction = %s\nline = %d\n",msg,__FILE__,__func__,__LINE__);

