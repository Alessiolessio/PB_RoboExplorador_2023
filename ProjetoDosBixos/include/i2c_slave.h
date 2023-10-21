#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "esp_log.h"
#include "driver/i2c.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"

static const char *TAG = "i2c-teste";

// Definição dos parâmetros do barramento I2C
#define I2C_SLAVE_NUM I2C_NUM_0
#define I2C_SLAVE_SCL_IO 22 // Pino SLC da ESP32
#define I2C_SLAVE_SDA_IO 21 // Pino SDA da ESP32
#define I2C_SLAVE_TX_BUF_LEN 256
#define I2C_SLAVE_RX_BUF_LEN 256
#define I2C_SLAVE_ADDRESS 0x08

#define TIMEOUT_MS 1000
#define LAST_BYTE_MASK 0xFF

static QueueHandle_t i2c_write_queue = NULL;

// Protótipo de funções:
static esp_err_t i2c_slave_init(void);
static void display_data(uint8_t *data, int len);
static int i2c_read_task(void *params);
char *int_to_string(int value);
static void i2c_write_task(void *params, int value);
static void i2c_task_com(void *pvParameters);
static void i2c_task_controle(void *pvParameters);
static esp_err_t create_tasks(int parametros);