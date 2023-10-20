#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include "pid_crtl.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

//Inicialização dos parâmetros ()
esp_err_t init_gpio(){
    gpio_set_direction(GPIO_NUM_18, GPIO_MODE_OUTPUT);
    gpio_set_direction(GPIO_NUM_19, GPIO_MODE_OUTPUT);
    return ESP_OK;
}

void app_main() {
    init_gpio();
    gpio_set_level(GPIO_NUM_18, 1);
    gpio_set_level(GPIO_NUM_19, 1);
    while(1){
     gpio_set_level(GPIO_NUM_18, 1);
     gpio_set_level(GPIO_NUM_19, 1);
     vTaskDelay(1);
    }
}