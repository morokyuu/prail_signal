
#include "pico/stdlib.h"
#include "hardware/pwm.h"

int main() {
    //const uint LED_PIN = PICO_DEFAULT_LED_PIN;
    //gpio_set_function(0,LED_PIN);
    gpio_set_function(0,GPIO_FUNC_PWM);
    gpio_set_function(1,GPIO_FUNC_PWM);

    uint slice_num = pwm_gpio_to_slice_num(0);
    pwm_set_wrap(slice_num,10);

    int duty=0;
    for(;;){
        pwm_set_chan_level(slice_num, PWM_CHAN_A, duty);
        pwm_set_chan_level(slice_num, PWM_CHAN_B, 4);
        pwm_set_enabled(slice_num, true);
        sleep_ms(400);
        duty++;
        if(duty > 10){
            duty = 0;
        }
    }


}
