#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

#include "state.h"

const int PWM_PERIOD = 3300;

const int IRLED_A = 2;
const int IRLED_B = 3;
const int SENS = 0;

const int LED_BLUE = 25;
const int LED_GREEN = 16;
const int LED_RED = 17;

const char SENS_A = 0x01;
const char SENS_B = 0x02;

volatile bool timer_flag = false;
int tim_count = 0;


bool repeating_timer_callback(struct repeating_timer *t){
    timer_flag = true;
    return true;
}

void sense(char *sens_state){
    bool in_A;
    bool in_B;

    pwm_set_gpio_level(IRLED_A, (int)(PWM_PERIOD * 0.5));
    sleep_us(150);
    in_A = gpio_get(SENS);
    pwm_set_gpio_level(IRLED_A, PWM_PERIOD);

    sleep_us(400);

    pwm_set_gpio_level(IRLED_B, (int)(PWM_PERIOD * 0.5));
    sleep_us(150);
    in_B = gpio_get(SENS);
    pwm_set_gpio_level(IRLED_B, PWM_PERIOD);

    if(in_A){
        *sens_state |= SENS_A;
        gpio_put(LED_BLUE,0);
    }
    else{
        gpio_put(LED_BLUE,1);
    }

    if(in_B){
        *sens_state |= SENS_B;
        gpio_put(LED_RED,0);
    }
    else{
        gpio_put(LED_RED,1);
    }
}

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
    gpio_put(LED_RED,0);

    gpio_init(SENS);
    gpio_set_dir(SENS,GPIO_IN);

    //PWM
    uint slice_num = pwm_gpio_to_slice_num(IRLED_A);
    gpio_set_function(IRLED_A,GPIO_FUNC_PWM);
    gpio_set_function(IRLED_B,GPIO_FUNC_PWM);

    pwm_config config;
    pwm_config_set_phase_correct(&config, false);
    pwm_config_set_clkdiv_int(&config, 1);
    pwm_config_set_clkdiv_mode(&config, PWM_DIV_FREE_RUNNING);
    pwm_config_set_output_polarity(&config, false, false);
    pwm_config_set_wrap(&config, PWM_PERIOD);
    pwm_init(slice_num,&config,true);

    //timer callback
    struct repeating_timer timer;
    add_repeating_timer_ms(2,repeating_timer_callback,NULL,&timer);

    proc_state_param_t st_param;

    while(1){
        while(!timer_flag);
        timer_flag = false;

        sense(&(st_param.sens_state));
        printf("%d\n",st_param.sens_state);

        proc_state(st_param);

    }


}
