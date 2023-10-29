#include "esp_log.h"
#include "h_bridge.h"
#include "pid.h"
#include "encoder.h"

#define DEBUG_H_BRIDGE 1

void app_main(void) {

    init_encoder(encoder_side(ENC_LEFT), ENC_LEFT);
    pulse_count(encoder_side(ENC_LEFT));

    #if DEBUG_H_BRIDGE
    init_gpio();
    init_pwm();
    init_pid();

    while(1)
    {
        update_motor(LEFT, 4095);
        update_motor(RIGHT, -4095);
        pid_calculate(encoder_side(ENC_LEFT));
    }
    #endif
}