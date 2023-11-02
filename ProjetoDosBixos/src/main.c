#include "esp_log.h"
#include "h_bridge.h"
#include "pid.h"
#include "encoder.h"

#define DEBUG_H_BRIDGE 1

void app_main(void) {

    //Param_initialization
    init_gpio();
    init_pwm();
    pcnt_unit_handle_t unit1 = init_encoder(ENC_LEFT);
    pcnt_unit_handle_t unit2 = init_encoder(ENC_RIGHT);
    pid_ctrl_block_handle_t block_pid_right = init_pid(PID_RIGHT);
    pid_ctrl_block_handle_t block_pid_left = init_pid(PID_LEFT);
    
    pid_calculate(unit1, block_pid_left, unit2, block_pid_right);

    #if DEBUG_H_BRIDG
    
    #endif
}