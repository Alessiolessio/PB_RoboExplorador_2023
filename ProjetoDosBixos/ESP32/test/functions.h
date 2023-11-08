#ifndef FUNCTIONS_H
	#define FUNCTIONS_H

	#include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    #include <math.h>
    #include "pid_ctrl.h"
    #include "driver/gpio.h"
    #include "freertos/FreeRTOS.h"
    #include "freertos/task.h"
    #include "freertos/queue.h"
    #include "driver/ledc.h"
    #include "driver/pulse_cnt.h"
    #include "esp_log.h"

    /**
     * @brief This struct integrates the GPIOs and the PWM ports to easly pass then to the update_motor function
    */
    typedef struct motor_information motor;
    struct motor_information{
        gpio_num_t gpio_1;
        gpio_num_t gpio_2;
        int pwm_channel;
        };

    /**
     *  @brief This struct integrates the GPIOs and the count value for each encoder 
    */
    typedef struct {
        gpio_num_t  pin_a;    
        gpio_num_t pin_b;                 
    }rotary_encoder_config_t;  

    /**
     * @brief Definitions of PWM parameters.
    */
        #define LEDC_TIMER              LEDC_TIMER_0
        #define LEDC_MODE               LEDC_HIGH_SPEED_MODE
        #define LEDC_OUTPUT_IO_1        (18) // Define the output GPIO for PWM
        #define LEDC_OUTPUT_IO_2        (19) // Define the output GPIO for PWM
        #define LEFT_CHANNEL           LEDC_CHANNEL_1
        #define RIGHT_CHANNEL          LEDC_CHANNEL_0
        #define LEDC_DUTY_RES            LEDC_TIMER_13_BIT 
        #define LEDC_DUTY               (4096) 
        #define LEDC_FREQUENCY          (5000) 

    /**
     * @brief Definition of PID parameters.
    */

        #define KI_1 5 //Integrativo (Soma o estado anterior para auxliar o crescimento de convergência)
        #define KD_1 5 //Derivativo (Caso a velocidade inicie seu declínio, a derivada do gráfico de V se torna negativa - decrescente - e os valores somados por KD auxiliam nessa queda)
        #define KP_1 3 //Proporcional (Determina o grau de crescimento do meu parâmetro desejado - Velocidade)
        #define KI_2 5
        #define KP_2 5
        #define KD_2 5
        #define Max_Output 500
        #define Min_Output 1
        #define Max_integral 200
        #define Min_integral 1


    /**
     * @brief Definition of Encoder parameters.
    */
        #define PCNT_HIGH_LIMIT 100
        #define PCNT_LOW_LIMIT  -100
        #define LEFT_ENCODER_1 GPIO_NUM_25
        #define LEFT_ENCODER_2 GPIO_NUM_27
        #define RIGHT_ENCODER_1 GPIO_NUM_25
        #define RIGHT_ENCODER_2 GPIO_NUM_27

    /**
     * @}
    */

    /**
     * @name Functions
     * @{
        */
        /**
         * @brief This functions are responsible to initialize every pin used in the program.
         * @param Void.
         * @details the function "init_pin_encoder" calls the function "init encoder" and returns the unit that will be used latter"
         * @return ESP_OK.
        */
        esp_err_t init_param(void);
        //{
            esp_err_t init_gpio(void);
            esp_err_t init_pwm(void);
            esp_err_t init_pid(void);
            pcnt_unit_handle_t init_encoder(void);
        //}

        /**
         * @brief This function calculate the current velocity 
         *         value (using the encoder interruption).
         *
         * @param Void.  
         * @return Current_velocity.
        */
        float angular_velocity(pcnt_unit_handle_t upcnt_unit);

        /**
         * @brief
         * @param
         * @return
        */
        static bool example_pcnt_on_reach(pcnt_unit_handle_t unit, const pcnt_watch_event_data_t *edata, void *user_ctx);

        /**
         * @brief This functions receive a value from the PID logic and update the PWM and the respective motor rotation direction.
         * @param control_motor Calculated by PID functions based on setpoint and error values.
         * @details Setpoint is given by ROS and each motor has one individual value.
         * @return ESP_OK.
        */
        esp_err_t motor_update(float control_motor, gpio_num_t GPIO1, gpio_num_t GPIO2, int pwm_channel);


        /**
         * @brief This is the main function. It calculates an error based on the difference between current velocity value and the goal one. Then it calculates the output for both right and left motors PWMs.
         * 
         * @param[in] pcnt_unit_handle_t Encoder configuration values. 
         * @details The setpoints values (velocity) are given by ROS. 
         * @return ESP_OK.
        */
        esp_err_t pid_calculate(pcnt_unit_handle_t upcnt_unit);
    /**
     * @}
    */
#endif