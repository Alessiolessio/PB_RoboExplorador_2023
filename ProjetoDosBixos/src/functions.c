#include "functions.h"

/*Correspondência de pinos -> PONTE H:

Motor Direita: GPIO_NUM_2 && GPIO_NUM_4;
Encoder Direita: GPIO_NUM_14 && GPIO_NUM_15;
Motor Esquerda: GPIO_NUM_26 && GPIO_NUM_27;
Encoder Esquerda: GPIO_NUM_16 && GPIO_NUM_17;

*/

/**
 * @brief Definition of global variables
 * @details 
*/
MOTOR RIGHT_MOTOR, LEFT_MOTOR;
pid_ctrl_block_handle_t B1; 
pid_ctrl_block_handle_t B2; 
int watch_points[] = {PCNT_LOW_LIMIT, -50, 0, 50, PCNT_HIGH_LIMIT};

esp_err_t init_param(){
    init_gpio();
    init_pwm();
    init_pid();
    return ESP_OK;
}

esp_err_t init_gpio(){
    gpio_set_direction(GPIO_NUM_2, GPIO_MODE_OUTPUT);
    gpio_set_direction(GPIO_NUM_4, GPIO_MODE_OUTPUT);
    gpio_set_direction(GPIO_NUM_26, GPIO_MODE_OUTPUT);
    gpio_set_direction(GPIO_NUM_27, GPIO_MODE_OUTPUT);

    gpio_set_direction(LEFT_ENCODER_1, GPIO_MODE_INPUT);
    gpio_set_direction(LEFT_ENCODER_2, GPIO_MODE_INPUT);
    gpio_set_direction(RIGHT_ENCODER_1, GPIO_MODE_INPUT);
    gpio_set_direction(RIGHT_ENCODER_2, GPIO_MODE_INPUT);

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
    //B1 and B2 are uset as parameters to the functions.
    B1 = pid_block_1;
    B2 = pid_block_2;
    pid_update_parameters(pid_block_1, &values_1);
    pid_update_parameters(pid_block_2, &values_2);
    return ESP_OK;
}

pcnt_unit_handle_t init_pin_encoder(){
//Attatching encoder GPIO pins.
  const rotary_encoder_config_t left_encoder_pins = {
    .counter = 0,
    .pin_a = LEFT_ENCODER_1,
    .pin_b = LEFT_ENCODER_2,
  };
  const rotary_encoder_config_t right_encoder_pins = {
    .counter = 0,
    .pin_a = RIGHT_ENCODER_1,
    .pin_b = RIGHT_ENCODER_2,
  };

//Creating the unit and setting up the glitch filter.
  pcnt_unit_config_t unit_config = {
      .high_limit = PCNT_HIGH_LIMIT,
      .low_limit = PCNT_LOW_LIMIT,
  };
  pcnt_unit_handle_t pcnt_unit = NULL;
  pcnt_new_unit(&unit_config, &pcnt_unit);

  pcnt_glitch_filter_config_t filter_config = {
      .max_glitch_ns = 100,
  };
  pcnt_unit_set_glitch_filter(pcnt_unit, &filter_config);

  //Avoiding code repetition pid_compute in pid_calculate.
  init_encoder(&right_encoder_pins, pcnt_unit);
  init_encoder(&left_encoder_pins, pcnt_unit);
  //Add the Watching points used for count the rotations
  for (size_t i = 0; i < sizeof(watch_points) / sizeof(watch_points[0]); i++) { // esse for tava como o erro dentro, acredito q ainda seja coisa de debugar, mas vou ver dps
    ESP_ERROR_CHECK(pcnt_unit_add_watch_point(pcnt_unit, watch_points[i]));
    }

  return pcnt_unit;
}

//DUVIDA: MESMO QUE, AO CHAMAR A FUNÇÃO UMA SEGUNDA VEZ A POSIÇÃO NA MEMORIA DAS VARIAVEIS CANAL 1 E 2 SEJAM DIFERENTES DA PRIMEIRA CHAMADA, CHAMAR PCNT DNV NAO "SUBSTITUIRIA" A CONFIGURAÇÃO DOS CANAIS DO ENCODER DIREITO?
esp_err_t init_encoder(const rotary_encoder_config_t *config, pcnt_unit_handle_t pcnt_unit){
    pcnt_chan_config_t chan_a_config = {
        .edge_gpio_num = config->pin_a,
        .level_gpio_num = config->pin_b,
    };
    pcnt_channel_handle_t pcnt_chan_a = NULL;
    pcnt_new_channel(pcnt_unit, &chan_a_config, &pcnt_chan_a);
    pcnt_chan_config_t chan_b_config = {
        .edge_gpio_num = config->pin_b,
        .level_gpio_num = config->pin_a,
    };
    pcnt_channel_handle_t pcnt_chan_b = NULL;
    pcnt_new_channel(pcnt_unit, &chan_b_config, &pcnt_chan_b);

    return ESP_OK;
    }

  static bool example_pcnt_on_reach(pcnt_unit_handle_t unit, const pcnt_watch_event_data_t *edata, void *user_ctx){
    BaseType_t high_task_wakeup; // 
    QueueHandle_t queue = (QueueHandle_t)user_ctx;
    xQueueSendFromISR(queue, &(edata->watch_point_value), &high_task_wakeup);

    return (high_task_wakeup == pdTRUE);
  }
  
  float angular_velocity(pcnt_unit_handle_t pcnt_unit){
    float current_velocity = 0;

    pcnt_event_callbacks_t cbs = {
        .on_reach = example_pcnt_on_reach, // quando um ponto é atingido ele retirna a função "example_pcnt_on_reach"
    };
    QueueHandle_t queue = xQueueCreate(10, sizeof(int));  
    int pulse_count = 0;
    int event_count = 0;
    while (1) {
        if (xQueueReceive(queue, &event_count, pdMS_TO_TICKS(100))) {
            //printf("watch point counter: %d\n", event_count);
        } else {
            ESP_ERROR_CHECK(pcnt_unit_get_count(pcnt_unit, &pulse_count));
            printf("Pulse count: %d\n", pulse_count);
        }
    }

    printf("A velocidade atual é: %f\n", current_velocity);
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
    for(;count < 20; count++){
      pid_compute(B1, error_motor_1, controll_1);
      motor_update(*controll_1, &RIGHT_MOTOR);
      pid_compute(B2, error_motor_2, controll_2);
      motor_update(*controll_2, &LEFT_MOTOR);

      current_velocity_1 = angular_velocity(upcnt_unit);
      current_velocity_2 = angular_velocity(upcnt_unit);
      error_motor_1 = (target_1 - current_velocity_1);
      error_motor_2 = (target_2 - current_velocity_2);
      vTaskDelay(100 / portTICK_PERIOD_MS);
      }
      count = 0;
      //FUNÇAO GET target
    }
    return ESP_OK;
  }
  
