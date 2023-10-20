#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include "pid_crtl.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/ledc.h"

#define LEDC_TIMER              LEDC_TIMER_0
#define LEDC_MODE               LEDC_LOW_SPEED_MODE
#define LEDC_OUTPUT_IO          (18) // Define the output GPIO
#define LEDC_CHANNEL            LEDC_CHANNEL_0
#define LEDC_DUTY_RES           LEDC_TIMER_13_BIT 
#define LEDC_DUTY               (2048) 
#define LEDC_FREQUENCY          (5000) 

//Inicialização dos parâmetros ()
esp_err_t init_param(){
    //gpio_set_direction(GPIO_NUM_18, GPIO_MODE_OUTPUT);
    gpio_set_direction(GPIO_NUM_19, GPIO_MODE_OUTPUT);
    return ESP_OK;

    ledc_timer_config_t ledc_timer = {
        .speed_mode       = LEDC_MODE,
        .timer_num        = LEDC_TIMER,
        .duty_resolution  = LEDC_DUTY_RES,
        .freq_hz          = LEDC_FREQUENCY,  // Set output frequency at 5 kHz
        .clk_cfg          = LEDC_AUTO_CLK
    };
    ledc_timer_config(&ledc_timer);
    ledc_channel_config_t ledc = {
        .speed_mode     = LEDC_MODE,
        .channel        = LEDC_CHANNEL,
        .timer_sel      = LEDC_TIMER,
        .intr_type      = LEDC_INTR_DISABLE,
        .gpio_num       = LEDC_OUTPUT_IO,
        .duty           = 0, 
        .hpoint         = 0
    };
    ledc_channel_config(&ledc);
}

void app_main() {
    init_param();
    //gpio_set_level(GPIO_NUM_18, 1);
    gpio_set_level(GPIO_NUM_19, 1);
    while(1){
     //gpio_set_level(GPIO_NUM_18, 1);
     gpio_set_level(GPIO_NUM_19, 1);
     ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, LEDC_DUTY);
     ledc_update_duty(LEDC_MODE, LEDC_CHANNEL);
     vTaskDelay(1);
    }
}