#include "state.h"
#include "sensor.h"

typedef enum{
    NONE,
    EDGE_DETECT,
    BOTH_DETECT,
    THROUGH
} STATE;
STATE state = NONE;

direction_t judge_direction(char first_sens_state){
    if(first_sens_state == SENS_A){
        return FORWARD;
    }
    else if(first_sens_state == SENS_B){
        return REVERSE;
    }
    else{
        return UNKNOWN;
    }
}

void proc_state(proc_state_param_t *p){

    switch(state){
        case NONE:
            p->timer_count = 0;
            p->speed = 0;
            p->direction = UNKNOWN;
            if(p->sens_state){
                p->first_sens_state = p->sens_state;
                printf("EDGE_DETECT = %d\n",p->first_sens_state);
                state = EDGE_DETECT;
            }
            break;
        case EDGE_DETECT:
            if(p->sens_state == p->first_sens_state){
                p->timer_count++;
                if(p->timer_count > 1000){
                    printf("timeout\n");
                    state = NONE;
                }
            }
            else if(p->sens_state == (SENS_A | SENS_B)){
                printf("BOTH_DETECT = %d\n",p->sens_state);
                state = BOTH_DETECT;
            }
            else{
                printf("both not came\n");
                state = NONE;
            }
            break;
        case BOTH_DETECT:
            if((p->sens_state & p->first_sens_state) == 0){
                printf("THROUGH = %d\n",p->timer_count);
                state = THROUGH;
            }
            else{
                p->timer_count++;
            }
            break;
        case THROUGH:
            if(p->sens_state == 0x00){
                p->direction = judge_direction(p->first_sens_state);
                p->speed = 0.020 / (float)(p->timer_count * 0.002);
                state = NONE;
                sleep_ms(100);
            }
            else{
                if(p->timer_count > 1000){
                    printf("through timeout\n");
                    state = NONE;
                }
            }
            break;
        default:
            break;
    }
}
