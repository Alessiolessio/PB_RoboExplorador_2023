#include "functions.h"

/*Correspondência de pinos -> PONTE H:

Motor Direita: GPIO_NUM_2 && GPIO_NUM_4;
Motor Esquerda: GPIO_NUM_26 && GPIO_NUM_27;

*/
MOTOR RIGHT_MOTOR, LEFT_MOTOR;
pid_ctrl_block_handle_t B1; 
pid_ctrl_block_handle_t B2; 
esp_err_t init_gpio(void);
esp_err_t init_pwm(void);
esp_err_t init_pid(void);

esp_err_t init_gpio(){
    gpio_set_direction(GPIO_NUM_2, GPIO_MODE_OUTPUT);
    gpio_set_direction(GPIO_NUM_4, GPIO_MODE_OUTPUT);
    gpio_set_direction(GPIO_NUM_26, GPIO_MODE_OUTPUT);
    gpio_set_direction(GPIO_NUM_27, GPIO_MODE_OUTPUT);
    RIGHT_MOTOR.gpio_1 = GPIO_NUM_2;
    RIGHT_MOTOR.gpio_2 = GPIO_NUM_4;
    RIGHT_MOTOR.pwm_channel = RIGHT_CHANNEL;
    LEFT_MOTOR.gpio_1 = GPIO_NUM_26;
    LEFT_MOTOR.gpio_2 = GPIO_NUM_27;
    LEFT_MOTOR.pwm_channel = LEFT_CHANNEL;
    return ESP_OK;
}

esp_err_t init_pwm(){
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
    return ESP_OK;
}

esp_err_t init_pid(){
    pid_ctrl_config_t config_1; 
    pid_ctrl_config_t config_2;
    pid_ctrl_block_handle_t pid_block_1; 
    pid_ctrl_block_handle_t pid_block_2;
    pid_ctrl_parameter_t values_1 = {
      .kd = KD_1,
      .kp = KP_1,
      .ki = KI_1,
      .min_integral = Min_integral,
      .max_integral = Max_integral,
      .min_output = Min_Output,
      .max_output = Max_Output,
      .cal_type = PID_CAL_TYPE_INCREMENTAL,
    };
    pid_ctrl_parameter_t values_2 = {
      .kd = KD_2,
      .kp = KP_2,
      .ki = KI_2,
      .min_integral = Min_integral,
      .max_integral = Max_integral,
      .min_output = Min_Output,
      .max_output = Max_Output,
      .cal_type = PID_CAL_TYPE_INCREMENTAL,
    };
    config_1.init_param = values_1;
    config_2.init_param = values_2;
    pid_new_control_block(&config_1, &pid_block_1);
    pid_new_control_block(&config_2, &pid_block_2);
    B1 = pid_block_1;
    B2 = pid_block_2;
    pid_update_parameters(pid_block_1, &values_1);
    pid_update_parameters(pid_block_2, &values_2);
    return ESP_OK;
}

esp_err_t init_param(){
    init_gpio();
    init_pwm();//Redundante ao PID
    init_pid();
    return ESP_OK;
}

//Ainda resta fazer
float angular_velocity(void){
  float current_velocity = 0;
  printf("A velocidade atual é: %f", current_velocity);
  return current_velocity;
}

esp_err_t motor_update(float control_motor, MOTOR* ports){
  if (control_motor > 0){
    gpio_set_level(ports->gpio_1, 1);
    gpio_set_level(ports->gpio_2, 0);
  }
  else if (control_motor < 0){
    gpio_set_level(ports->gpio_1, 0);
    gpio_set_level(ports->gpio_2, 1);
  }
  else{
    gpio_set_level(ports->gpio_1, 0);
    gpio_set_level(ports->gpio_2, 0);
  }
  ledc_set_duty(LEDC_MODE, ports->pwm_channel, control_motor);
  ledc_update_duty(LEDC_MODE, ports->pwm_channel);
  return ESP_OK;
}

/*Problemas:
- Precisar do PID BLock em outro escopo (pensar em retornar ele no init_param)*/
esp_err_t pid_calculate(){
  float target_1 = 100;
  float target_2 = 100;  //Recebe os valores do ROS
  int count = 0;
  float current_velocity_1 = angular_velocity();
  float current_velocity_2 = angular_velocity();
  float error_motor_1 = (target_1 - current_velocity_1);
  float error_motor_2= (target_2 - current_velocity_2);
  float *controll_1 = NULL, *controll_2 = NULL;

 while(target_1 != -1 && target_2 != -1){ //Definindo um valor de parada (recebido pelo ROS))
    for(;count < 20; count++){
      pid_compute(B1, error_motor_1, controll_1);
      motor_update(*controll_1, &RIGHT_MOTOR);
      pid_compute(B2, error_motor_2, controll_2);
      motor_update(*controll_2, &LEFT_MOTOR);

      current_velocity_1 = angular_velocity();
      current_velocity_2 = angular_velocity();
      error_motor_1 = (target_1 - current_velocity_1);
      error_motor_2 = (target_2 - current_velocity_2);
      vTaskDelay(100 / portTICK_PERIOD_MS);
      }
      count = 0;
      //FUNÇAO GET target
    }
    return ESP_OK;
  }
  
