#include "pid.h"

//pid_ctrl_block_handle_t Global_pidblock_L; 
pid_ctrl_block_handle_t Global_pidblock_R; 
const char *TAG_PID = "PID";

pid_ctrl_block_handle_t init_pid(pid_side_t side){

    pid_ctrl_config_t config_pid; 
    pid_ctrl_block_handle_t pid_block; 

    pid_ctrl_parameter_t values_pid = {
      .kd = PID_SIDE_KD(side),
      .kp = PID_SIDE_KP(side),
      .ki = PID_SIDE_KI(side),
      .min_integral = Min_integral,
      .max_integral = Max_integral,
      .min_output = Min_Output,
      .max_output = Max_Output,
      .cal_type = PID_CAL_TYPE_INCREMENTAL,
    };
    config_pid.init_param = values_pid;

    ESP_ERROR_CHECK(pid_new_control_block(&config_pid, &pid_block));
    ESP_ERROR_CHECK(pid_update_parameters(pid_block, &values_pid));
    return pid_block;
}

/*esp_err_t init_pid(pcnt_unit_handle_t upcnt_unit){

    pid_ctrl_config_t config_pid_L; 
    pid_ctrl_config_t config_pid_R;
    pid_ctrl_block_handle_t pid_block_L; 
    pid_ctrl_block_handle_t pid_block_R;

    pid_ctrl_parameter_t values_pid_L = {
      .kd = KD_L,
      .kp = KP_L,
      .ki = KI_L,
      .min_integral = Min_integral,
      .max_integral = Max_integral,
      .min_output = Min_Output,
      .max_output = Max_Output,
      .cal_type = PID_CAL_TYPE_INCREMENTAL,
    };

    pid_ctrl_parameter_t values_pid_R = {
      .kd = KD_R,
      .kp = KP_R,
      .ki = KI_R,
      .min_integral = Min_integral,
      .max_integral = Max_integral,
      .min_output = Min_Output,
      .max_output = Max_Output,
      .cal_type = PID_CAL_TYPE_INCREMENTAL,
    };

    config_pid_L.init_param = values_pid_L;
    config_pid_R.init_param = values_pid_R;

    ESP_ERROR_CHECK(pid_new_control_block(&config_pid_L, &pid_block_L));
    ESP_ERROR_CHECK(pid_new_control_block(&config_pid_R, &pid_block_R));
    ESP_ERROR_CHECK(pid_update_parameters(pid_block_L, &values_pid_L));
    ESP_ERROR_CHECK(pid_update_parameters(pid_block_R, &values_pid_R));

    float controll_pid_LEFT;
for(int i = 0; i < 10; i++){

   float target_LEFT = 16;
   float current_velocity_LEFT = pulse_count(upcnt_unit) * 0.04;
   ESP_LOGI(TAG_PID, "Velocidade inicial: %f", current_velocity_LEFT);
   float error_motor_LEFT = (target_LEFT - current_velocity_LEFT);
   ESP_LOGI(TAG_PID, "Erro: %f", error_motor_LEFT);

    vTaskDelay(100 / portTICK_PERIOD_MS);
    pid_compute(pid_block_L, error_motor_LEFT, &controll_pid_LEFT);
    ESP_LOGI(TAG_PID, "Velocidade final: %f", controll_pid_LEFT);

    vTaskDelay(100 / portTICK_PERIOD_MS);
}

    return ESP_OK;
}*/

esp_err_t pid_calculate(pcnt_unit_handle_t upcnt_unit_L, pid_ctrl_block_handle_t pid_block_L, pcnt_unit_handle_t upcnt_unit_R, pid_ctrl_block_handle_t pid_block_R){
  
  float controll_pid_LEFT, controll_pid_RIGHT;
  float target_LEFT = 16, target_RIGHT = 22;

for(int i = 0; i < 10; i++){
    float current_velocity_LEFT = pulse_count(upcnt_unit_R) * 0.04;
   float current_velocity_RIGHT = pulse_count(upcnt_unit_L) * 0.02;

  //Recalculate an error
   ESP_LOGI(TAG_PID, "Velocidade inicial : %f", current_velocity_LEFT);
   float error_motor_LEFT = (target_LEFT - current_velocity_LEFT);
   float error_motor_RIGHT = (target_RIGHT - current_velocity_RIGHT);
   ESP_LOGI(TAG_PID, "Erro: %f", error_motor_LEFT);
    
    vTaskDelay(100 / portTICK_PERIOD_MS);

    //Calculate a new PWM Value
    pid_compute(pid_block_L, error_motor_LEFT, &controll_pid_LEFT);
    pid_compute(pid_block_R, error_motor_RIGHT, &controll_pid_RIGHT);
    ESP_LOGI(TAG_PID, "Velocidade final: %f", controll_pid_LEFT);
    /*update_motor(LEFT, controll_pid_LEFT);
    update_motor(RIGHT, controll_pid_RIGHT);*/

    vTaskDelay(100 / portTICK_PERIOD_MS);
}

  /*float target_LEFT = 10;
  //float target_RIGHT = 100;  //Receive the values from ROS
  //int count_frequency = 0;

  float current_velocity_LEFT = pulse_count(upcnt_unit) * 0.04;
  //float current_velocity_RIGHT = pulse_count(upcnt_unit);
  ESP_LOGI(TAG_PID, "Velocidade: %f", current_velocity_LEFT);
  float error_motor_LEFT = (target_LEFT - current_velocity_LEFT);
  //float error_motor_RIGHT = (target_RIGHT - current_velocity_RIGHT);

  float *controll_pid_RIGHT = NULL, *controll_pid_LEFT = NULL;
  //&& target_RIGHT != -1
  //while(target_LEFT != -1){ 

    //for(;count_frequency < 10; count_frequency++){
      vTaskDelay(100 / portTICK_PERIOD_MS);
      //pid_compute(Global_pidblock_L, error_motor_LEFT, controll_pid_LEFT);
      ESP_LOGI(TAG_PID, "Velocidade: %f", *controll_pid_LEFT);

      //update_motor(LEFT, *controll_pid_LEFT);
      
      pid_compute(Global_pidblock_R, error_motor_RIGHT, controll_pid_RIGHT);
      update_motor(RIGHT, *controll_pid_RIGHT);

      //current_velocity_LEFT = pulse_count(upcnt_unit);
      //current_velocity_RIGHT = pulse_count(upcnt_unit);

      //error_motor_LEFT = (target_LEFT - current_velocity_LEFT);
      //error_motor_RIGHT = (target_RIGHT - current_velocity_RIGHT);

      //vTaskDelay(50 / portTICK_PERIOD_MS);

      //}

      //count_frequency = 0;
      //target_RIGHT = 20;
      //target_LEFT = 20;

    //}*/

    return ESP_OK;

  }
  