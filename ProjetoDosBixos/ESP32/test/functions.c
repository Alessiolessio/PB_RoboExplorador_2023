#include "functions.h"

/*Correspondência de pinos -> PONTE H:

Motor Direita: GPIO_NUM_2 && GPIO_NUM_4;
Encoder Direita: GPIO_NUM_14 && GPIO_NUM_15;
Motor Esquerda: GPIO_NUM_19 && GPIO_NUM_21;
Encoder Esquerda: GPIO_NUM_16 && GPIO_NUM_17;

*/

/**
 * @brief Definition of global variables
 * @details 
*/

static const char *TAG = "Testing angular velocity";

motor LEFT_MOTOR_INFORMATION = {
  .gpio_1      = GPIO_NUM_21,
  .gpio_2      = GPIO_NUM_19,
  .pwm_channel = LEFT_CHANNEL
};
motor RIGHT_MOTOR_INFORMATION = {
  .gpio_1      = GPIO_NUM_2,
  .gpio_2      = GPIO_NUM_4,
  .pwm_channel = RIGHT_CHANNEL
};
pid_ctrl_block_handle_t B1; 
pid_ctrl_block_handle_t B2; 
int pulse_count = 0;
int event_count = 0;
float current_velocity = 0;
QueueHandle_t queue;


esp_err_t init_param(){
    init_gpio();
    init_pwm();
    init_pid();
    return ESP_OK;
}

esp_err_t init_gpio(){
    gpio_set_direction(GPIO_NUM_2, GPIO_MODE_OUTPUT);
    gpio_set_direction(GPIO_NUM_4, GPIO_MODE_OUTPUT);
    gpio_set_direction(GPIO_NUM_34, GPIO_MODE_OUTPUT);
    gpio_set_direction(GPIO_NUM_35, GPIO_MODE_OUTPUT);

    gpio_set_direction(LEFT_ENCODER_1, GPIO_MODE_INPUT);
    gpio_set_direction(LEFT_ENCODER_2, GPIO_MODE_INPUT);
    gpio_set_direction(RIGHT_ENCODER_1, GPIO_MODE_INPUT);
    gpio_set_direction(RIGHT_ENCODER_2, GPIO_MODE_INPUT);
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
    //B1 and B2 are uset as parameters to the functions.
    B1 = pid_block_1;
    B2 = pid_block_2;
    pid_update_parameters(pid_block_1, &values_1);
    pid_update_parameters(pid_block_2, &values_2);
    return ESP_OK;
}

pcnt_unit_handle_t init_encoder(){
  //Attatching encoder GPIO pins.
  //DANDO DEFINED BUT NOT USED
    /*const rotary_encoder_config_t left_encoder_pins = {
      .pin_a = LEFT_ENCODER_1,
      .pin_b = LEFT_ENCODER_2,
    };
    const rotary_encoder_config_t right_encoder_pins = {
      .pin_a = RIGHT_ENCODER_1,
      .pin_b = RIGHT_ENCODER_2,
    };*/

    pcnt_unit_config_t unit_config = {
        .high_limit = PCNT_HIGH_LIMIT,
        .low_limit = PCNT_LOW_LIMIT,
    };
    pcnt_unit_handle_t pcnt_unit = NULL;
    ESP_ERROR_CHECK(pcnt_new_unit(&unit_config, &pcnt_unit));

    ESP_LOGI(TAG, "set glitch filter");
    pcnt_glitch_filter_config_t filter_config = {
        .max_glitch_ns = 1000,
    };
    ESP_ERROR_CHECK(pcnt_unit_set_glitch_filter(pcnt_unit, &filter_config));

    ESP_LOGI(TAG, "install pcnt channels");
    pcnt_chan_config_t chan_a_config = {
        .edge_gpio_num  = LEFT_ENCODER_1,
        .level_gpio_num = LEFT_ENCODER_2,
    };
    pcnt_channel_handle_t pcnt_chan_a = NULL;
    ESP_ERROR_CHECK(pcnt_new_channel(pcnt_unit, &chan_a_config, &pcnt_chan_a));
    pcnt_chan_config_t chan_b_config = {
        .edge_gpio_num = LEFT_ENCODER_2,
        .level_gpio_num = LEFT_ENCODER_1,
    };
    pcnt_channel_handle_t pcnt_chan_b = NULL;
    ESP_ERROR_CHECK(pcnt_new_channel(pcnt_unit, &chan_b_config, &pcnt_chan_b));

    pcnt_chan_config_t chan_c_config = {
        .edge_gpio_num  = RIGHT_ENCODER_1,
        .level_gpio_num = RIGHT_ENCODER_2,
    };
    pcnt_channel_handle_t pcnt_chan_c = NULL;
    ESP_ERROR_CHECK(pcnt_new_channel(pcnt_unit, &chan_c_config, &pcnt_chan_c));
    pcnt_chan_config_t chan_d_config = {
        .edge_gpio_num = RIGHT_ENCODER_2,
        .level_gpio_num = RIGHT_ENCODER_1,
    };
    pcnt_channel_handle_t pcnt_chan_d = NULL;
    ESP_ERROR_CHECK(pcnt_new_channel(pcnt_unit, &chan_d_config, &pcnt_chan_d));

    ESP_LOGI(TAG, "set edge and level actions for pcnt channels");
    ESP_ERROR_CHECK(pcnt_channel_set_edge_action(pcnt_chan_a, PCNT_CHANNEL_EDGE_ACTION_DECREASE, PCNT_CHANNEL_EDGE_ACTION_INCREASE));
    ESP_ERROR_CHECK(pcnt_channel_set_level_action(pcnt_chan_a, PCNT_CHANNEL_LEVEL_ACTION_KEEP, PCNT_CHANNEL_LEVEL_ACTION_INVERSE));
    ESP_ERROR_CHECK(pcnt_channel_set_edge_action(pcnt_chan_b, PCNT_CHANNEL_EDGE_ACTION_INCREASE, PCNT_CHANNEL_EDGE_ACTION_DECREASE));
    ESP_ERROR_CHECK(pcnt_channel_set_level_action(pcnt_chan_b, PCNT_CHANNEL_LEVEL_ACTION_KEEP, PCNT_CHANNEL_LEVEL_ACTION_INVERSE));
    ESP_ERROR_CHECK(pcnt_channel_set_edge_action(pcnt_chan_c, PCNT_CHANNEL_EDGE_ACTION_DECREASE, PCNT_CHANNEL_EDGE_ACTION_INCREASE));
    ESP_ERROR_CHECK(pcnt_channel_set_level_action(pcnt_chan_c, PCNT_CHANNEL_LEVEL_ACTION_KEEP, PCNT_CHANNEL_LEVEL_ACTION_INVERSE));
    ESP_ERROR_CHECK(pcnt_channel_set_edge_action(pcnt_chan_d, PCNT_CHANNEL_EDGE_ACTION_INCREASE, PCNT_CHANNEL_EDGE_ACTION_DECREASE));
    ESP_ERROR_CHECK(pcnt_channel_set_level_action(pcnt_chan_d, PCNT_CHANNEL_LEVEL_ACTION_KEEP, PCNT_CHANNEL_LEVEL_ACTION_INVERSE));

    ESP_LOGI(TAG, "add watch points and register callbacks");
    int watch_points[] = {PCNT_LOW_LIMIT, -50, 0, 50, PCNT_HIGH_LIMIT};
    for (size_t i = 0; i < sizeof(watch_points) / sizeof(watch_points[0]); i++) {
        ESP_ERROR_CHECK(pcnt_unit_add_watch_point(pcnt_unit, watch_points[i]));
    }
    pcnt_event_callbacks_t cbs = {
        .on_reach = example_pcnt_on_reach,
    };
    QueueHandle_t queue = xQueueCreate(15, sizeof(int));
    ESP_ERROR_CHECK(pcnt_unit_register_event_callbacks(pcnt_unit, &cbs, queue));

    ESP_LOGI(TAG, "enable pcnt unit");
    ESP_ERROR_CHECK(pcnt_unit_enable(pcnt_unit));
    ESP_LOGI(TAG, "clear pcnt unit");
    ESP_ERROR_CHECK(pcnt_unit_clear_count(pcnt_unit));
    ESP_LOGI(TAG, "start pcnt unit");
    ESP_ERROR_CHECK(pcnt_unit_start(pcnt_unit));

    ESP_ERROR_CHECK(gpio_wakeup_enable(LEFT_ENCODER_1, GPIO_INTR_LOW_LEVEL));
    ESP_ERROR_CHECK(gpio_wakeup_enable(RIGHT_ENCODER_1, GPIO_INTR_LOW_LEVEL));
  return pcnt_unit;
}

  static bool example_pcnt_on_reach(pcnt_unit_handle_t unit, const pcnt_watch_event_data_t *edata, void *user_ctx){
    BaseType_t high_task_wakeup; // 
    QueueHandle_t queue = (QueueHandle_t)user_ctx;
    xQueueSendFromISR(queue, &(edata->watch_point_value), &high_task_wakeup);

    return (high_task_wakeup == pdTRUE);
  }
  
  float angular_velocity(pcnt_unit_handle_t pcnt_unit){
    if (xQueueReceive(queue, &event_count, pdMS_TO_TICKS(100))) {
        printf("watch point counter: %d\n", event_count);
    } else {
        ESP_ERROR_CHECK(pcnt_unit_get_count(pcnt_unit, &pulse_count));
        printf("Pulse count: %d\n", pulse_count);
    }
    current_velocity = pulse_count;
    printf("A velocidade atual é: %f\n", current_velocity);
    //Reset pulsecount
    if(pulse_count == PCNT_HIGH_LIMIT || pulse_count == PCNT_LOW_LIMIT){
      pcnt_unit_clear_count(pcnt_unit);
    }
    return current_velocity;
}

esp_err_t motor_update(float control_motor, gpio_num_t GPIO1, gpio_num_t GPIO2, int pwm_channel){
  if (control_motor > 0){
    gpio_set_level(GPIO1, 1);
    gpio_set_level(GPIO2, 0);
  }
  else if (control_motor < 0){
    gpio_set_level(GPIO1, 0);
    gpio_set_level(GPIO2, 1);
  }
  else{
    gpio_set_level(GPIO1, 0);
    gpio_set_level(GPIO2, 0);
  }
  ledc_set_duty(LEDC_MODE, pwm_channel, control_motor);
  ledc_update_duty(LEDC_MODE, pwm_channel);
  return ESP_OK;
}


esp_err_t pid_calculate(pcnt_unit_handle_t upcnt_unit){
  float target_1 = 100;
  float target_2 = 100;  //Recebe os valores do ROS
  int count = 0;
  float current_velocity_1 = angular_velocity(upcnt_unit);
  float current_velocity_2 = angular_velocity(upcnt_unit);
  float error_motor_1 = (target_1 - current_velocity_1);
  float error_motor_2= (target_2 - current_velocity_2);
  float *controll_1 = NULL, *controll_2 = NULL;

 while(target_1 != -1 && target_2 != -1){ //Definindo um valor de parada (recebido pelo ROS))
    for(;count < 10; count++){
      pid_compute(B1, error_motor_1, controll_1);
      motor_update(*controll_1, GPIO_NUM_19, GPIO_NUM_21, LEDC_CHANNEL_1);
      pid_compute(B2, error_motor_2, controll_2);
      motor_update(*controll_2, GPIO_NUM_19, GPIO_NUM_21, LEDC_CHANNEL_1);

      current_velocity_1 = angular_velocity(upcnt_unit);
      current_velocity_2 = angular_velocity(upcnt_unit);
      error_motor_1 = (target_1 - current_velocity_1);
      error_motor_2 = (target_2 - current_velocity_2);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      }
      count = 0;
      target_1 = 20;
      target_2 = 20;
    }
    return ESP_OK;
  }
  
