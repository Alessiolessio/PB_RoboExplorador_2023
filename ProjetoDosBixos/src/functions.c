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
        .freq_hz          = LEDC_FREQUENCY, 
        .clk_cfg          = LEDC_AUTO_CLK
    };
    ledc_timer_config(&ledc_timer);

    ledc_channel_config_t ledc1 = {
        .speed_mode     = LEDC_MODE,
        .channel        = LEDC_CHANNEL_1,
        .timer_sel      = LEDC_TIMER,
        .intr_type      = LEDC_INTR_DISABLE,
        .gpio_num       = LEDC_OUTPUT_IO_1,
        .duty           = 0, 
        .hpoint         = 0
    };
    ledc_channel_config(&ledc1);

    ledc_channel_config_t ledc2 = {
        .speed_mode     = LEDC_MODE,
        .channel        = LEDC_CHANNEL_2,
        .timer_sel      = LEDC_TIMER,
        .intr_type      = LEDC_INTR_DISABLE,
        .gpio_num       = LEDC_OUTPUT_IO_2,
        .duty           = 0, 
        .hpoint         = 0
    };
    ledc_channel_config(&ledc2);

    pid_ctrl_config_t controll; 
    pid_ctrl_block_handle_t pid_block; 
    pid_ctrl_parameter_t values = {
      .kd = KD,
      .kp = KP,
      .ki = KI,
      .min_integral = Min_integral,
      .max_integral = Max_integral,
      .min_output = Min_Output,
      .max_output = Max_Output,
      .cal_type = PID_CAL_TYPE_INCREMENTAL,
    };
    controll.init_param = values;
    pid_new_control_block(&controll, &pid_block);
    pid_update_parameters(pid_block, &values);
    return ESP_OK;
}

//Ainda resta fazer
float angular_velocity(void){
  float current_velocity = 0;
  printf("A velocidade atual é: %f", current_velocity);
  return current_velocity;
    return ESP_OK;
}

esp_err_t motor_update_right(float control_motor){
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
  ledc_set_duty(LEDC_MODE, LEDC_CHANNEL_1, control_motor);
  ledc_update_duty(LEDC_MODE, LEDC_CHANNEL_1);
  return ESP_OK;
}

esp_err_t motor_update_left(float control_motor){
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
  ledc_set_duty(LEDC_MODE, LEDC_CHANNEL_2, control_motor);
  ledc_update_duty(LEDC_MODE, LEDC_CHANNEL_2);
  return ESP_OK;
}


/*PRoblemas:
- Precisar do PID BLock em outro escopo (pensar em retornar ele no init_param)*/
esp_err_t pid_calculate(pid_ctrl_block_handle_t pid_block, float velocity_goal_1, float velocity_goal_2){
  float current_valelocity_1 = angular_velocity();
  float current_valelocity_2 = angular_velocity();
  float error_motor_1 = (velocity_goal_1 - current_valelocity_1);
  float error_motor_2 = (velocity_goal_2 - current_valelocity_2);
  float *controll_1 = 0, *controll_2 = 0;

  while (fabs(error_motor_1) > 0.25 || fabs(error_motor_2) > 0.25){
    if(fabs(error_motor_1) > 0.25){
      pid_compute(pid_block, error_motor_1, controll_1);
      motor_update_left(*controll_1);
    }
    if(fabs(error_motor_2) > 0.25){
      pid_compute(pid_block, error_motor_2, controll_2);
      motor_update_left(*controll_2);
    }

    current_valelocity_1 = angular_velocity();
    current_valelocity_2 = angular_velocity();
    error_motor_1 = (velocity_goal_1 - current_valelocity_1);
    error_motor_2 = (velocity_goal_2 - current_valelocity_2);
  }
  printf("Cabô\n");
  return ESP_OK;
}
