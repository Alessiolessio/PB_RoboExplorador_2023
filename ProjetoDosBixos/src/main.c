#include "functions.h"

void app_main() {
    init_param();
    gpio_set_level(GPIO_NUM_2, 1);
    gpio_set_level(GPIO_NUM_4, 1);
    gpio_set_level(GPIO_NUM_26, 1);
    gpio_set_level(GPIO_NUM_27, 1);
    ledc_set_duty(LEDC_MODE, LEDC_CHANNEL_1, LEDC_DUTY);
    ledc_update_duty(LEDC_MODE, LEDC_CHANNEL_1);
    ledc_set_duty(LEDC_MODE, LEDC_CHANNEL_2, LEDC_DUTY);
    ledc_update_duty(LEDC_MODE, LEDC_CHANNEL_2);

    while(1){
     gpio_set_level(GPIO_NUM_2, 1);
     gpio_set_level(GPIO_NUM_4, 1);
     gpio_set_level(GPIO_NUM_26, 1);
     gpio_set_level(GPIO_NUM_27, 1);

     ledc_set_duty(LEDC_MODE, LEDC_CHANNEL_1, LEDC_DUTY);
     ledc_update_duty(LEDC_MODE, LEDC_CHANNEL_1);
     ledc_set_duty(LEDC_MODE, LEDC_CHANNEL_2, LEDC_DUTY);
    ledc_update_duty(LEDC_MODE, LEDC_CHANNEL_2);
    }
}