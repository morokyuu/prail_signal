
#include "pico/stdlib.h"
#include "hardware/pwm.h"

int main() {
    //const uint LED_PIN = PICO_DEFAULT_LED_PIN;
    //gpio_set_function(0,LED_PIN);
    gpio_set_function(0,GPIO_FUNC_PWM);
    gpio_set_function(1,GPIO_FUNC_PWM);

    uint slice_num = pwm_gpio_to_slice_num(0);
    pwm_set_wrap(slice_num,10);
    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config,2.f);
    //pwm_config_set_clkdiv_int_frac(&config,255,15);
    pwm_init(slice_num,&config,true);
    pwm_set_gpio_level(0, 65534/2);
    pwm_set_gpio_level(1, 65534/4);

    int duty=0;
    for(;;){
        tight_loop_contents();
    }


}
