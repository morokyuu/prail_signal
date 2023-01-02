
#include "pico/stdlib.h"
#include "hardware/pwm.h"

int main() {
    gpio_set_function(0,GPIO_FUNC_PWM);
    gpio_set_function(1,GPIO_FUNC_PWM);

    uint slice_num = pwm_gpio_to_slice_num(0);

    pwm_config config;
    pwm_config_set_phase_correct(&config, false);
    pwm_config_set_clkdiv_int(&config, 1);
    pwm_config_set_clkdiv_mode(&config, PWM_DIV_FREE_RUNNING);
    pwm_config_set_output_polarity(&config, false, false);
    pwm_config_set_wrap(&config, 3300);

    pwm_init(slice_num,&config,true);
    pwm_set_gpio_level(0, (int)(3300 * 0.5));
    pwm_set_gpio_level(1, (int)(3300 * 0.8));

    for(;;){
        tight_loop_contents();
    }


}
