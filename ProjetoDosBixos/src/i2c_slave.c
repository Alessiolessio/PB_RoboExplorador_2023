#include "i2c_slave.h"

// Inicializa o I2C escravo
static esp_err_t i2c_slave_init(void) {
    
    int i2c_slave_port = I2C_SLAVE_NUM;

    // Configuração da struct do barramento I2C
    i2c_config_t conf_slave = {
        .sda_io_num = I2C_SLAVE_SDA_IO,         
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_io_num = I2C_SLAVE_SCL_IO,          
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .mode = I2C_MODE_SLAVE,
        .slave.addr_10bit_en = 0,
        .slave.slave_addr = I2C_SLAVE_ADDRESS,
    };

    // Configuração ods parâmetros do barramento I2C com base nas configurações definidas na estrutura conf_slave
    esp_err_t err = i2c_param_config(i2c_slave_port, &conf_slave); // Caso dê tudo certo retorn ESP_OK

    // Captura do erro, caso a config dê errado
    if (err != ESP_OK)
    {
        return err;
    }
    
    // Instalar (configurar + inicializar) o driver I2C
    return i2c_driver_install(i2c_slave_port, conf_slave.mode, I2C_SLAVE_RX_BUF_LEN, I2C_SLAVE_TX_BUF_LEN, 0);
}

static void display_data(uint8_t *data, int len) {
    int i;
    for (i = 0; i < len; i++)
    {
        printf("%02x ", data[i]);
        if ((i + 1) % 16 == 0)
        {
            printf("\n");
        }
    }
    printf("\n");
}

static void i2c_read_task(void *pvParameters) {
    uint8_t rx_data[I2C_SLAVE_RX_BUF_LEN];

    int i2c_slave_port = I2C_SLAVE_NUM;

    int size = i2c_slave_read_buffer(i2c_slave_port, rx_data, 5, TIMEOUT_MS / portTICK_PERIOD_MS);

    if (size > 0) {

        ESP_LOGI(TAG, "Read size=%d", size);

        display_data(rx_data, size);

    } else {
        ESP_LOGI(TAG, "Read failed!");
    }

}

static void i2c_write_task(void *pvParameters) {
    uint8_t tx_data[16] = "1"; 

    int i2c_slave_port = I2C_SLAVE_NUM;

    int size = i2c_slave_write_buffer(i2c_slave_port, tx_data, 16, TIMEOUT_MS / portTICK_PERIOD_MS);

    if (size > 0)
    {
        ESP_LOGI(TAG, "Write size=%d", size);
        display_data(tx_data, size);
    }
    else
    {
        ESP_LOGI(TAG, "Write failed");
    }
}

// Função que une as funções de read e write (modularizadas), em sequência
static void i2c_task_com(void *pvParameters) {

    while(1){

        //vTaskDelay(1000 / portTICK_PERIOD_MS);

        //i2c_read_task(NULL);

        vTaskDelay(1000 / portTICK_PERIOD_MS);

        i2c_write_task(NULL);

    }

}

static void i2c_task_controle(void *pvParameters) {


    while(1){
        ESP_LOGI(TAG, "Task 2");

        vTaskDelay(500 / portTICK_PERIOD_MS);

    }

}

// Utilizar o FreeRTOS para distribuir as tarefas entre os cores
static esp_err_t create_tasks(void) {

    ESP_ERROR_CHECK(i2c_slave_init()); // Inicializa o Slave e confere se nenhum erro foi capturado

    i2c_write_queue = xQueueCreate(10, I2C_SLAVE_TX_BUF_LEN);

    // Task 1 (core 0): leitura + escrita de dados
    xTaskCreatePinnedToCore(i2c_task_com, "i2c_task_com", 2048, NULL, 5, NULL, 0);

    // A ordem de execução seria Read --> Write, em que elas seriam coordenadas pelo vTaskDelay(), 
    // que iria barrar o Read

    // Task 2 (core 1): controle do motor e derivados

    //xTaskCreatePinnedToCore(i2c_task_controle, "i2c_task_controle", 2048, NULL, 5, NULL, 1);

    // Caso as tasks sejam criadas, retorna sucesso
    return ESP_OK;
}

void app_main(void) {
    ESP_ERROR_CHECK(create_tasks()); // Utiliza o FreeRTOS para criar as tasks em diferentes cores
}