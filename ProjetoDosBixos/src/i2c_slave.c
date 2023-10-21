#include "i2c_slave.h"

int valor = 0; 

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
    if (err != ESP_OK) {
        return err;
    }
    
    // Instalar (configurar + inicializar) o driver I2C
    return i2c_driver_install(i2c_slave_port, conf_slave.mode, I2C_SLAVE_RX_BUF_LEN, I2C_SLAVE_TX_BUF_LEN, 0);
}

// Função para printar os dados na tela
static void display_data(uint8_t *data, int len) {
    int i;
    for (i = 2; i < len; i++) {
        printf("%02x ", data[i]);

        if ((i + 1) % 16 == 0) { // A cada 16 elementos quebramos uma linha (melhorar vizualização)
            printf("\n");
        }
    }
    printf("\n");
}

// Função para a leitura dos valores enviados da Master
static int i2c_read_task(void *params) {

    int x = 0;

    uint8_t rx_data[I2C_SLAVE_RX_BUF_LEN];

    int size = i2c_slave_read_buffer(I2C_SLAVE_NUM, rx_data, 6, TIMEOUT_MS / portTICK_PERIOD_MS);

    for(int i = 2; i < size; i++){
        x |= (rx_data[i] << 8*(5-i));
    } 

    if (size > 0) {
        //printf("Valor lido: %d \n", x);
        valor = x;
        return x;

    } else {
        ESP_LOGI(TAG, "Read failed!");
    }

    return 0;
}

// Tranforma o int para uma string
char *int_to_string(int value) {
    char *str = (char *)malloc(12);  // Espaço suficiente para armazenar um inteiro com sinal de 32 bits
    snprintf(str, 12, "%d", value);
    return str;
}

// Função para converter um inteiro para uma sequência de caracteres (string)
static void i2c_write_task(void *params, int value) {
    // Converte a sequência de caracteres (string) em uint8_t
    uint8_t tx_data[4];

    for (int i = 0; i < 4; i++) {
        tx_data[i] = (value >> 8 * (3 - i)) & LAST_BYTE_MASK;
    }

    int size = i2c_slave_write_buffer(I2C_SLAVE_NUM, tx_data, 4, TIMEOUT_MS / portTICK_PERIOD_MS);

    if (size > 0) {
        //printf("Valor escrito: %d \n", value);
    } else {
        ESP_LOGI(TAG, "Escrita falhou!");
    }
    
}

// Função que une as funções de read e write (modularizadas), em sequência
static void i2c_task_com(void *params) {

    int x = 0;

    while(1){

        vTaskDelay(1000 / portTICK_PERIOD_MS);

        x = i2c_read_task(NULL);

        vTaskDelay(1000 / portTICK_PERIOD_MS);

        i2c_write_task(params, x);

    }

}

static void i2c_task_controle(void *params) {

    while(1){

        ESP_LOGI(TAG, "Task 2:  %d\n", valor);

        vTaskDelay(2000 / portTICK_PERIOD_MS);

    }

}

// Utiliza o FreeRTOS para distribuir as tarefas entre os cores 0 e 1
static esp_err_t create_tasks(int parametros) {

    ESP_ERROR_CHECK(i2c_slave_init()); // Inicializa o Slave e confere se nenhum erro foi capturado

    i2c_write_queue = xQueueCreate(10, I2C_SLAVE_TX_BUF_LEN);

    // Task 1 (core 0): leitura + escrita de dados
    xTaskCreatePinnedToCore(i2c_task_com, "i2c_task_com", 2048, &parametros, 5, NULL, 0);

    // Task 2 (core 1): controle do motor e derivados

    xTaskCreatePinnedToCore(i2c_task_controle, "i2c_task_controle", 2048, NULL, 5, NULL, 1);

    // Caso as tasks sejam criadas, retorna sucesso
    return ESP_OK;
}

void app_main(void) {

    int parametro_teste = 1;

    ESP_ERROR_CHECK(create_tasks(parametro_teste)); // Utiliza o FreeRTOS para criar as tasks em diferentes cores
}