#include <stdio.h>
#include "Chorno.h"

int main(void)
{
    struct timespec ts; 
    
    clock_gettime(CLOCK_REALTIME, &ts);
}
