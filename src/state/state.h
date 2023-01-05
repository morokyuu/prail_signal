#ifndef MAIN_STATE_HEADER
#define MAIN_STATE_HEADER

#include <stdio.h>

typedef enum{
    UNKNOWN,
    FORWARD,
    REVERSE
} direction_t;

typedef struct{
    int timer_count;
    char sens_state;
    char first_sens_state;
    direction_t direction;
    float speed;
} proc_state_param_t;

void proc_state(proc_state_param_t *p);

#endif // MAIN_STATE_HEADER
