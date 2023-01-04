#include <stdio.h>
#include "pico/stdlib.h"

#include "sensor.h"
#include "state.h"

const int LED_BLUE = 25;
const int LED_GREEN = 16;
const int LED_RED = 17;

int main() {
    //serial
    stdio_init_all();
    printf("hello");

    //GPIO
    gpio_init(LED_BLUE);
    gpio_init(LED_GREEN);
    gpio_init(LED_RED);
    gpio_set_dir(LED_BLUE,GPIO_OUT);
    gpio_set_dir(LED_GREEN,GPIO_OUT);
    gpio_set_dir(LED_RED,GPIO_OUT);
    gpio_put(LED_BLUE,0);
    gpio_put(LED_GREEN,1);
    gpio_put(LED_RED,1);


    //sensor
    init_sensor();
    proc_state_param_t st_param;

    while(1){
        wait_timer();
        printf("loop\n");

        sense(&(st_param.sens_state));
        printf("%d\n",st_param.sens_state);

        proc_state(&st_param);

        int outA = st_param.sens_state & SENS_A;
        int outB = st_param.sens_state & SENS_B;
        gpio_put(LED_BLUE,outA);
        gpio_put(LED_RED,outB);
    }
}
