#ifndef PRAIL_SENSOR_HEADER
#define PRAIL_SENSOR_HEADER

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

#define SENS_A 0x01
#define SENS_B 0x02

void init_sensor(void);
void sense(char *sens_state);

#endif //PRAIL_SENSOR_HEADER
