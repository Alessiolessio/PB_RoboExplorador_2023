#ifndef FUNCTIONS_H
	#define FUNCTIONS_H

	#include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
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
        #define LEDC_OUTPUT_IO          (18) // Define the output GPIO for PWM
        #define LEDC_OUTPUT_I1          (19) // Define the output GPIO for PWM
        #define LEDC_CHANNEL            LEDC_CHANNEL_0
        #define LEDC_DUTY_RES           LEDC_TIMER_13_BIT 
        #define LEDC_DUTY               (4096) 
        #define LEDC_FREQUENCY          (5000) 
    /**
     * @}
    */

    
    /**
     * @brief This function is responsible to initialize every pin used in the program.
     * @param Void.
     * @return ESP_OK.
    */
    esp_err_t init_param(void);

    /**
     * @brief This function calculate the current velocity 
     *         value (using the encoder interruption), then use a PID logic to set a new value to the PWM.
     *
     * @param setpoint The velocity expected by the ROS input. 
     * @details The setpoint value (velocity) is given by ROS. 
     * @return ESP_OK.
    */
    esp_err_t motor_update(float setpoint);

    /**
     * @brief
     * @param
     * @return
    */
    esp_err_t motor_update_right(int control_motor);

    /**
     * @brief
     * @param
     * @return
    */
    esp_err_t motor_update_left(int control_motor);

#endif