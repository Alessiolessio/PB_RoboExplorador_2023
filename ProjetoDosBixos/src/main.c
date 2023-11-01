#include "esp_log.h"
#include "h_bridge.h"
#include "pid.h"
#include "encoder.h"

#define DEBUG_H_BRIDGE 1

void app_main(void) {

    init_gpio();
    //int pid(PID_SIDE(PID_LEFT));
    //init_pwm();
    pcnt_unit_handle_t unit1 = init_encoder(ENC_LEFT);
    pcnt_unit_handle_t unit2 = init_encoder(ENC_RIGHT);
    init_pid(unit1);
    //pid_calculate(unit1, unit2);

    #if DEBUG_H_BRIDG
    
    #endif
}