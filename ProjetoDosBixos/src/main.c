#include "functions.h"

void app_main() {
    init_param();
    gpio_set_direction(GPIO_NUM_19, GPIO_MODE_OUTPUT);
    gpio_set_direction(GPIO_NUM_21, GPIO_MODE_OUTPUT);
    pcnt_unit_handle_t unit = init_encoder();

    while(1){
        for(int i = 1000; i < 4096*2; i += 1000){
            motor_update(i, GPIO_NUM_19, GPIO_NUM_21, LEDC_CHANNEL_1);
            printf("PWM: %d\n", i);
            angular_velocity(unit);
            vTaskDelay(100 / portTICK_PERIOD_MS);
        } 
    }
    
    
    //pid_calculate(unit);
}