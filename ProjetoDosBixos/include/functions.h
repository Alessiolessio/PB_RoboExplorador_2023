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
    #include "driver/ledc.h"

    /**
     * @name Types & Constants
     * @{
     * 
     * @brief Definitions of the motors ports.
    */
        #define PIO_NUM_2 Motor_1A
        #define PIO_NUM_4 Motor_1B
        #define PIO_NUM_26 Motor_2A
        #define PIO_NUM_27 Motor_2B

    /**
     * @brief Definitions of PWM parameters.
    */
        #define LEDC_TIMER              LEDC_TIMER_0
        #define LEDC_MODE               LEDC_HIGH_SPEED_MODE
        #define LEDC_OUTPUT_IO_1        (18) // Define the output GPIO for PWM
        #define LEDC_OUTPUT_IO_2        (19) // Define the output GPIO for PWM
        #define LEDC_CHANNEL_1           LEDC_CHANNEL_0
        #define LEDC_CHANNEL_2           LEDC_CHANNEL_1
        #define LEDC_DUTY_RES            LEDC_TIMER_13_BIT 
        #define LEDC_DUTY               (4096) 
        #define LEDC_FREQUENCY          (5000) 

    /**
     * @brief Definition of PID parameters.
    */

        #define KI 5 //Integrativo (Soma o estado anterior para auxliar o crescimento de convergência)
        #define KD 5 //Derivativo (Caso a velocidade inicie seu declínio, a derivada do gráfico de V se torna negativa - decrescente - e os valores somados por KD auxiliam nessa queda)
        #define KP 3 //Proporcional (Determina o grau de crescimento do meu parâmetro desejado - Velocidade)
        #define Max_Output 500
        #define Min_Output 1
        #define Max_integral 200
        #define Min_integral 1

    /**
     * @}
    */

    /**
     * @name Functions
     * @{
        */
        /**
         * @brief This function is responsible to initialize every pin used in the program.
         * @param Void.
         * @return ESP_OK.
        */
        esp_err_t init_param(void);

        /**
         * @brief This function calculate the current velocity 
         *         value (using the encoder interruption).
         *
         * @param Void.  
         * @return Current_velocity.
        */
        float angular_velocity(void);//Nao feita ainda

        /**
         * @brief This functions receive a value from the PID logic and update the PWM and the respective motor rotation direction.
         * @param control_motor Calculated by PID functions based on setpoint and error values.
         * @details Setpoint is given by ROS and each motor has one individual value.
         * @return ESP_OK.
        */
        esp_err_t motor_update_right(float control_motor);
        esp_err_t motor_update_left(float control_motor);


        /**
         * @brief This is the main function. It calculates an error based on the difference between current velocity value and the goal one. Then it calculates the output for both right and left motors PWMs.
         * 
         * @param[in] pid_block PID configuration values. 
         * @param[in] velocity_goal_1 The velocity expected by the ROS input for motor_1. 
         * @param[in] velocity_goal_2 The velocity expected by the ROS input for motor_2. 
         * @details The setpoints values (velocity) are given by ROS. 
         * @return ESP_OK.
        */
        esp_err_t pid_calculate(pid_ctrl_block_handle_t pid_block, float velocity_goal_1, float velocity_goal_2);
    /**
     * @}
    */
#endif