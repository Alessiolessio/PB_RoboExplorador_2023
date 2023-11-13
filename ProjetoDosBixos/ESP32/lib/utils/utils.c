#include "utils.h"

bool FLAG_TARGET = false;

int TARGET_VALUE_L = 0;
int TARGET_VALUE_R = 0;

float ENCODER_READ_L = 0;
float ENCODER_READ_R = 0;

void motor_ctrl(){
    init_gpio();
    init_pwm();

    pid_ctrl_block_handle_t pid_block_left = init_pid(PID_LEFT);
    pid_ctrl_block_handle_t pid_block_right = init_pid(PID_RIGHT);
    pcnt_unit_handle_t encoder_unit_left = init_encoder(ENC_LEFT);
    pcnt_unit_handle_t encoder_unit_right = init_encoder(ENC_RIGHT);

    while(1){
        pid_calculate(encoder_unit_left, pid_block_left, encoder_unit_right, pid_block_right);
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}
