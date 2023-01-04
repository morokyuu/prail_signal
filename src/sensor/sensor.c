#include "sensor.h"

const int PWM_PERIOD = 3300;

const int IRLED_A = 2;
const int IRLED_B = 3;
const int SENS = 0;

struct repeating_timer timer;
volatile bool timer_flag = false;
int tim_count = 0;


//public
void wait_timer(void){
    while(!timer_flag);
    timer_flag = false;
}

bool repeating_timer_callback(struct repeating_timer *t){
    timer_flag = true;
    return true;
}

//public
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

    *sens_state = 0x00;
    if(in_A){
        *sens_state |= SENS_A;
    }
    if(in_B){
        *sens_state |= SENS_B;
    }
}

void init_sensor(void) {

    //sensor
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
    add_repeating_timer_ms(2,repeating_timer_callback,NULL,&timer);
}
