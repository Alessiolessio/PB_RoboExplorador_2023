#include "functions.h"

void app_main() {
    init_param();
    gpio_set_level(GPIO_NUM_2, 1);
    gpio_set_level(GPIO_NUM_4, 1);
    gpio_set_level(GPIO_NUM_26, 1);
    gpio_set_level(GPIO_NUM_27, 1);
    ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, LEDC_DUTY);
    ledc_update_duty(LEDC_MODE, LEDC_CHANNEL);

    while(1){
     gpio_set_level(GPIO_NUM_2, 1);
     gpio_set_level(GPIO_NUM_4, 1);
     gpio_set_level(GPIO_NUM_26, 1);
     gpio_set_level(GPIO_NUM_27, 1);

     ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, LEDC_DUTY);
     ledc_update_duty(LEDC_MODE, LEDC_CHANNEL);
    }
}