#include "i2c_slave.h"
#include "esp_log.h"

void app_main(void) {

    int parametro_teste = 1;

    ESP_ERROR_CHECK(create_tasks(parametro_teste, 0));
}
