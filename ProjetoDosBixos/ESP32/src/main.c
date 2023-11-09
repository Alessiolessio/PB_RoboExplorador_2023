#include "i2c_slave.h"
#include "esp_log.h"
#include "encoder.h"
#include "pid.h"
#include "h_bridge.h"


void app_main(void) {

    init_gpio():
    init_pwm();

    pid_ctrl_block_handle_t pid_block_left = init_pid(PID_LEFT);
    pid_ctrl_block_handle_t pid_block_right = init_pid(PID_RIGHT);
    pcnt_unit_handle_t encoder_unit_left = init_encoder(ENC_LEFT);
    pcnt_unit_handle_t encoder_unit_right = init_encoder(ENC_RIGHT);

    while(){
        pid_calculate(encoder_unit_left, pid_block_left, encoder_unit_right, pid_block_right);
        vTaskDelay(300 / portTICK_PERIOD_MS);
    }


}

