#include "functions.h"

void app_main() {
    init_param();
    pcnt_unit_handle_t unit = init_pin_encoder();
    pid_calculate(unit);
}