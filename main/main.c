
#include "pico/stdlib.h"
#include "hardware/pwm.h"

const int PWM_PERIOD = 3300;
const int IRLED = 2;

volatile bool timer_flag = false;

bool repeating_timer_callback(struct repeating_timer *t){
    timer_flag = true;
    return true;
}

int main() {

    //GPIO
    gpio_init(1);
    gpio_set_dir(1,GPIO_OUT);
    gpio_put(1,0);

    gpio_init(0);
    gpio_set_dir(0,GPIO_IN);


    //PWM
    gpio_set_function(IRLED,GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(IRLED);
    pwm_config config;
    pwm_config_set_phase_correct(&config, false);
    pwm_config_set_clkdiv_int(&config, 1);
    pwm_config_set_clkdiv_mode(&config, PWM_DIV_FREE_RUNNING);
    pwm_config_set_output_polarity(&config, false, false);
    pwm_config_set_wrap(&config, PWM_PERIOD);
    pwm_init(slice_num,&config,true);

    //timer callback
    struct repeating_timer timer;
    add_repeating_timer_ms(50,repeating_timer_callback,NULL,&timer);

    while(1){
        while(!timer_flag);
        timer_flag = false;


        pwm_set_gpio_level(IRLED, (int)(PWM_PERIOD * 0.5));
        sleep_us(150);
        bool in = gpio_get(0);
        sleep_us(150);
        pwm_set_gpio_level(IRLED, PWM_PERIOD);

        if(in){
            gpio_put(1,0);
        }
        else{
            gpio_put(1,1);
        }
        //tight_loop_contents();
    }


}
