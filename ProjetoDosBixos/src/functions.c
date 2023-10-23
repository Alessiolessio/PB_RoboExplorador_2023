#include "functions.h"

/*Correspondência de pinos -> PONTE H:

Motor Direita: PIO_NUM_18 && PIO_NUM_19;
Motor Esquerda: PIO_NUM_26 && PIO_NUM_27;

*/

esp_err_t init_param(){
    gpio_set_direction(GPIO_NUM_18, GPIO_MODE_OUTPUT);
    gpio_set_direction(GPIO_NUM_19, GPIO_MODE_OUTPUT);
    gpio_set_direction(GPIO_NUM_26, GPIO_MODE_OUTPUT);
    gpio_set_direction(GPIO_NUM_27, GPIO_MODE_OUTPUT);

    ledc_timer_config_t ledc_timer = {
        .speed_mode       = LEDC_MODE,
        .timer_num        = LEDC_TIMER,
        .duty_resolution  = LEDC_DUTY_RES,
        .freq_hz          = LEDC_FREQUENCY,  // Set output frequency at 5 kHz
        .clk_cfg          = LEDC_AUTO_CLK
    };
    ledc_timer_config(&ledc_timer);

    ledc_channel_config_t ledc1 = {
        .speed_mode     = LEDC_MODE,
        .channel        = LEDC_CHANNEL,
        .timer_sel      = LEDC_TIMER,
        .intr_type      = LEDC_INTR_DISABLE,
        .gpio_num       = LEDC_OUTPUT_IO,
        .duty           = 0, 
        .hpoint         = 0
    };
    ledc_channel_config(&ledc1);

    ledc_channel_config_t ledc2 = {
        .speed_mode     = LEDC_MODE,
        .channel        = LEDC_CHANNEL,
        .timer_sel      = LEDC_TIMER,
        .intr_type      = LEDC_INTR_DISABLE,
        .gpio_num       = LEDC_OUTPUT_I1,
        .duty           = 0, 
        .hpoint         = 0
    };
    ledc_channel_config(&ledc2);

    return ESP_OK;
}

esp_err_t motor_update(float setpoint){
    return ESP_OK;
}

esp_err_t motor_update_right(int control_motor){
  if (control_motor > 0){
    gpio_set_level(GPIO_NUM_2, 1);
    gpio_set_level(GPIO_NUM_4, 0);
  }
  else if (control_motor < 0){
    gpio_set_level(GPIO_NUM_2, 0);
    gpio_set_level(GPIO_NUM_4, 1);
  }
  else{
    gpio_set_level(GPIO_NUM_2, 0);
    gpio_set_level(GPIO_NUM_4, 0);
  }
  ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, control_motor);
  ledc_update_duty(LEDC_MODE, LEDC_CHANNEL);
  return ESP_OK;
}

//Duvida: usando ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, control_motor) em ambas as funções, os valores dos PWM, mesmo que em diferentes pinos
//terão sempre o mesmo valor. Devo usar dois canais diferentes?
esp_err_t motor_update_left(int control_motor){
    if (control_motor > 0){
    gpio_set_level(GPIO_NUM_26, 1);
    gpio_set_level(GPIO_NUM_27, 0);
  }
  else if (control_motor < 0){
    gpio_set_level(GPIO_NUM_26, 0);
    gpio_set_level(GPIO_NUM_27, 1);
  }
  else{
    gpio_set_level(GPIO_NUM_26, 0);
    gpio_set_level(GPIO_NUM_27, 0);
  }
  ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, control_motor);
  ledc_update_duty(LEDC_MODE, LEDC_CHANNEL);
  return ESP_OK;
}


