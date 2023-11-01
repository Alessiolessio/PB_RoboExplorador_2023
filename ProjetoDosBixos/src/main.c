#include "esp_log.h"
#include "h_bridge.h"
#include "pid.h"
#include "encoder.h"

#define DEBUG_H_BRIDGE 1

void app_main(void) {

    pcnt_unit_handle_t unit = init_encoder(ENC_LEFT);
    init_pid(unit);


    #if DEBUG_H_BRIDGE
    //init_gpio();
    //init_pwm();
    
    #endif
}