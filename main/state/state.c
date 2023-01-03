#include "state.h"

typedef enum{
    NONE,
    EDGE_DETECT,
    BOTH_DETECT,
    THROUGH
} STATE;
STATE state = NONE;

void proc_state(proc_state_param_t p){
    switch(state){
        case NONE:
            p.timer_count = 0;
            if(p.sens_state){
                state = EDGE_DETECT;
                printf("edge = %d\n",p.sens_state);
            }
            break;
        case EDGE_DETECT:
            p.timer_count++;
            if(p.timer_count > 100){
                printf("timeout %d\n",p.timer_count);
                state = NONE;
            }
            break;
        case BOTH_DETECT:
            break;
        case THROUGH:
            break;
        default:
            break;
    }
}
