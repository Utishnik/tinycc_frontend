#ifndef LOCAL_VAR
#define LOCAL_VAR

#include "tcc.h"

//#define MAX_TEMP_LOCAL_VARIABLE_NUMBER 8 tcc original variable
/*list of temporary local variables on the stack in current function. */
static struct temp_local_variable {
	int location; //offset on stack. Svalue.c.i
	short size;
	short align;
};
temp_local_variable *arr_temp_local_vars;

#endif LOCAL_VAR