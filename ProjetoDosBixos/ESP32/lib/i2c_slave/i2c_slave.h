#ifndef __I2CSLAVE__
#define __I2CSLAVE__

/**
 * @brief Código para comunicação I2C em modo escravo.
 * 
 * Autores: Matheus Paiva Angarola e William Noboru Yoshihara 
 * 
 * Este código configura e inicia o barramento I2C em modo escravo para comunicação
 * com um mestre. Ele lê e escreve dados no barramento I2C, desempacota e empacota valores.
 * O código cria tarefas para leitura e escrita de dados e também para funções de control.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "esp_log.h"
#include "driver/i2c.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "utils.h"

// Definição dos parâmetros do barramento I2C
#define I2C_SLAVE_NUM I2C_NUM_0
#define I2C_SLAVE_SCL_IO 22 // Pino SLC da ESP32
#define I2C_SLAVE_SDA_IO 21 // Pino SDA da ESP32
#define I2C_SLAVE_TX_BUF_LEN 256
#define I2C_SLAVE_RX_BUF_LEN 256
#define I2C_SLAVE_ADDRESS 0x08

// Definição dos valores realmente utilizados na escrita e leitura
#define WRITE_LEN_VALUE 4
#define READ_LEN_VALUE 6
#define TIMEOUT_MS 250 

// Definição de valores para empacotamento de desempacotamento
#define LAST_BYTE_MASK 0xFF

// Definição de frequências utilizadas dentro das tasks
#define FREQ_COMMUNICATION 58
#define FREQ_CONTROL 2000

static QueueHandle_t i2c_write_queue = NULL; 
static const char *TAG = "i2c-teste"; // TAG utilizada para dar display no console

// Protótipo de funções:

/**
 * @brief Inicializa o driver do barramento I2C no modo escravo
 *
 * Esta função inicializa o driver I2C no modo escravo, configurando os pinos SDA e SCL,
 * definindo a configuração do barramento I2C e instalando o driver.
 *
 * @return
 *     - ESP_OK: O driver I2C foi inicializado com sucesso.
 *     - ESP_ERR_INVALID_ARG: Falha na inicialização devido a argumentos inválidos.
 *     - ESP_ERR_NO_MEM: Falha na inicialização devido à falta de memória disponível.
 *     - ESP_FAIL: Outros erros na inicialização do driver I2C.
 */
static esp_err_t i2c_slave_init(void);

/**
 * @brief Tarefa de leitura dos dados do barramento I2C
 *
 * Esta função é executada como uma tarefa e lê os dados do barramento I2C,
 * desempacota os valores lidos e os retorna. Os valores são enviados por outra tarefa.
 *
 * @param params Parâmetros da tarefa (não utilizados).
 * @return O valor lido a partir do barramento I2C.
 */
static int i2c_read_task(void *params);

/**
 * @brief Tarefa de escrita de dados no barramento I2C
 *
 * Esta função é executada como uma tarefa e envia os dados recebidos por outra tarefa
 * para o barramento I2C. Os valores são empacotados antes do envio.
 *
 * @param params Parâmetros da tarefa (não utilizados).
 * @param value O valor a ser escrito no barramento I2C.
 */
static void i2c_write_task(void *params, int value);

/**
 * @brief Tarefa de comunicação e escrita no barramento I2C
 *
 * Esta função é executada como uma tarefa e é responsável por coordenar a comunicação
 * entre a leitura e escrita de dados no barramento I2C. Ela lê os valores, aguarda,
 * e então escreve os valores lidos no barramento.
 *
 * @param params Parâmetros da tarefa (não utilizados).
 */
static void i2c_task_com(void *pvParameters);

/**
 * @brief Tarefa de controle
 *
 * Esta função é executada como uma tarefa e lida com o controle do motor e outros
 * aspectos relacionados. Os valores lidos do barramento I2C são utilizados aqui para
 * controle.
 *
 * @param params Parâmetros da tarefa (não utilizados).
 */
static void i2c_task_controle(void *pvParameters);

/**
 * @brief Cria tarefas para leitura e escrita de dados no barramento I2C
 *
 * Esta função cria as tarefas para leitura e escrita de dados no barramento I2C,
 * além de inicializar o driver do barramento I2C.
 *
 * @param parametros Parâmetros para as tarefas (não utilizados).
 * @param display Flag para controle de exibição.
 * @return
 *     - ESP_OK: As tarefas foram criadas com sucesso.
 *     - Outros códigos de erro em caso de falha.
 */
esp_err_t create_tasks(int parametros, int display);

/**
 * @brief Exibe dados em formato hexadecimal
 *
 * Esta função exibe os dados em formato hexadecimal.
 *
 * @param data Ponteiro para os dados a serem exibidos.
 * @param len Tamanho dos dados.
 */
static void display_data(uint8_t *data, int len);

#endif
