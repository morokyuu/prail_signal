#ifndef MAIN_STATE_HEADER
#define MAIN_STATE_HEADER

#include <stdio.h>

typedef struct{
    int timer_count;
    char sens_state;
} proc_state_param_t;

void proc_state(proc_state_param_t *p);

#endif // MAIN_STATE_HEADER
