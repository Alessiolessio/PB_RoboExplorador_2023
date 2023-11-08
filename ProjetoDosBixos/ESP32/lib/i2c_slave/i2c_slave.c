#include "i2c_slave.h"

int valor = 0; // GLobal variable for testing communincation intercores

static esp_err_t i2c_slave_init(void) {
    
    int i2c_slave_port = I2C_SLAVE_NUM;

    i2c_config_t conf_slave = {
        .sda_io_num = I2C_SLAVE_SDA_IO,         
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_io_num = I2C_SLAVE_SCL_IO,          
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .mode = I2C_MODE_SLAVE,
        .slave.addr_10bit_en = 0,
        .slave.slave_addr = I2C_SLAVE_ADDRESS,
    };

    esp_err_t err = i2c_param_config(i2c_slave_port, &conf_slave);

    if (err != ESP_OK) {
        return err;
    }
    
    return i2c_driver_install(i2c_slave_port, conf_slave.mode, I2C_SLAVE_RX_BUF_LEN, I2C_SLAVE_TX_BUF_LEN, 0);
}

static int i2c_read_task(void *params) {

    int x = 0;
    int last_value = 0;

    uint8_t rx_data[I2C_SLAVE_RX_BUF_LEN];

    int size = i2c_slave_read_buffer(I2C_SLAVE_NUM, rx_data, READ_LEN_VALUE, TIMEOUT_MS / portTICK_PERIOD_MS);

    // "Unpacking" valores
    for(int i = 2; i < size; i++){
        x |= (rx_data[i] << 8 * ((READ_LEN_VALUE - 1) - i));
    } 

    if (size > 0) {
        if(last_value != x){
            FLAG_TARGET = true;
        }
        return x;

    } else {
        ESP_LOGI(TAG, "Read failed!");
    }

    return 0;
}

static void i2c_write_task(void *params, int value) {
    uint8_t tx_data[WRITE_LEN_VALUE];

    // "Packing" valores
    for (int i = 0; i < WRITE_LEN_VALUE; i++) {
        tx_data[i] = (value >> 8 * ((WRITE_LEN_VALUE - 1) - i)) & LAST_BYTE_MASK;
    }

    int size = i2c_slave_write_buffer(I2C_SLAVE_NUM, tx_data, WRITE_LEN_VALUE, TIMEOUT_MS / portTICK_PERIOD_MS);

    if (size > 0) {
        printf("Valor escrito: %d \n", value);
    } else {
        ESP_LOGI(TAG, "Escrita falhou!");
    }
    
}

static void i2c_task_com(void *params) {

    while(1){

        vTaskDelay(FREQ_COMMUNICATION / portTICK_PERIOD_MS);

        valor_lido = i2c_read_task(NULL);

        vTaskDelay(FREQ_COMMUNICATION / portTICK_PERIOD_MS);

        i2c_write_task(params, valor);

    }

}

static void i2c_task_controle(void *params) {

    while(1){

        vTaskDelay(FREQ_CONTROL / portTICK_PERIOD_MS);

        valor++;

        printf("Valor lido: %d \n", valor_lido);

    }

}

esp_err_t create_tasks(int parametros, int display) {

    ESP_ERROR_CHECK(i2c_slave_init());

    i2c_write_queue = xQueueCreate(10, I2C_SLAVE_TX_BUF_LEN);

    // Task 1 (core 0): leitura + escrita de dados
    xTaskCreatePinnedToCore(i2c_task_com, "i2c_task_com", 2048, &parametros, 5, NULL, 0);

    // Task 2 (core 1): controle do motor e derivados
    xTaskCreatePinnedToCore(i2c_task_controle, "i2c_task_controle", 2048, NULL, 5, NULL, 1);

    return ESP_OK;
}

static void display_data(uint8_t *data, int len) {
    int i;
    for (i = 2; i < len; i++) {
        printf("%02x ", data[i]);

        if ((i + 1) % 16 == 0) {
            printf("\n");
        }
    }
    printf("\n");
}

