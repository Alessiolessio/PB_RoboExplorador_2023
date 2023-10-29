#include "encoder.h"

pcnt_unit_handle_t right_encoder;
pcnt_unit_handle_t left_encoder;
const char *TAG_ENCODER = "Encoder";

pcnt_unit_handle_t encoder_side(encoder_side_t encoder) {

    return encoder == ENC_LEFT ? left_encoder : right_encoder;
}

void init_encoder(pcnt_unit_handle_t encoder, encoder_side_t cha_encoder){ 
    
    ESP_LOGI(TAG_ENCODER, "Install pcnt unit");
    pcnt_unit_config_t unit_config = {
        .high_limit = PCNT_HIGH_LIMIT,
        .low_limit = PCNT_LOW_LIMIT,
    };
    pcnt_unit_handle_t selected_encoder = NULL;
    ESP_ERROR_CHECK(pcnt_new_unit(&unit_config, &selected_encoder));

    ESP_LOGI(TAG_ENCODER, "Set glitch filter");
    pcnt_glitch_filter_config_t filter_config = {
        .max_glitch_ns = 1000,
    };
    ESP_ERROR_CHECK(pcnt_unit_set_glitch_filter(selected_encoder, &filter_config));

    ESP_LOGI(TAG_ENCODER, "Install pcnt channels");
    pcnt_chan_config_t chan_a_config = {
        .edge_gpio_num = ENCODER_INPUT_A(cha_encoder),
        .level_gpio_num = ENCODER_INPUT_B(cha_encoder),
    };
    pcnt_channel_handle_t pcnt_chan_a = NULL;
    ESP_ERROR_CHECK(pcnt_new_channel(selected_encoder, &chan_a_config, &pcnt_chan_a));
    pcnt_chan_config_t chan_b_config = {
        .edge_gpio_num = ENCODER_INPUT_B(cha_encoder),
        .level_gpio_num = ENCODER_INPUT_A(cha_encoder),
    };
    pcnt_channel_handle_t pcnt_chan_b = NULL;
    ESP_ERROR_CHECK(pcnt_new_channel(selected_encoder, &chan_b_config, &pcnt_chan_b));

    ESP_LOGI(TAG_ENCODER, "Set edge and level actions for pcnt channels");
    ESP_ERROR_CHECK(pcnt_channel_set_edge_action(pcnt_chan_a, PCNT_CHANNEL_EDGE_ACTION_DECREASE, PCNT_CHANNEL_EDGE_ACTION_INCREASE));
    ESP_ERROR_CHECK(pcnt_channel_set_level_action(pcnt_chan_a, PCNT_CHANNEL_LEVEL_ACTION_KEEP, PCNT_CHANNEL_LEVEL_ACTION_INVERSE));
    ESP_ERROR_CHECK(pcnt_channel_set_edge_action(pcnt_chan_b, PCNT_CHANNEL_EDGE_ACTION_INCREASE, PCNT_CHANNEL_EDGE_ACTION_DECREASE));
    ESP_ERROR_CHECK(pcnt_channel_set_level_action(pcnt_chan_b, PCNT_CHANNEL_LEVEL_ACTION_KEEP, PCNT_CHANNEL_LEVEL_ACTION_INVERSE));

    ESP_LOGI(TAG_ENCODER, "Add watch points and register callbacks");
    int watch_points[] = {PCNT_LOW_LIMIT, -50, 0, 50, PCNT_HIGH_LIMIT};
    for (size_t i = 0; i < sizeof(watch_points) / sizeof(watch_points[0]); i++) {
        ESP_ERROR_CHECK(pcnt_unit_add_watch_point(selected_encoder, watch_points[i]));
    }
    pcnt_event_callbacks_t cbs = {
        .on_reach = pcnt_on_reach,
    };

    ESP_LOGI(TAG_ENCODER, "Enable pcnt unit");
    ESP_ERROR_CHECK(pcnt_unit_enable(selected_encoder));
    
    ESP_LOGI(TAG_ENCODER, "Clear pcnt unit");
    ESP_ERROR_CHECK(pcnt_unit_clear_count(selected_encoder));

    ESP_LOGI(TAG_ENCODER, "Start pcnt unit");
    ESP_ERROR_CHECK(pcnt_unit_start(selected_encoder));
}

bool pcnt_on_reach(pcnt_unit_handle_t unit, const pcnt_watch_event_data_t *edata, void *user_ctx) {
    BaseType_t high_task_wakeup;
    QueueHandle_t queue = (QueueHandle_t)user_ctx;

    xQueueSendFromISR(queue, &(edata->watch_point_value), &high_task_wakeup);

    return (high_task_wakeup == pdTRUE);
}

float pulse_count(pcnt_unit_handle_t encoder){

    pcnt_event_callbacks_t cbs = {
        .on_reach = pcnt_on_reach,
    };

    QueueHandle_t queue = xQueueCreate(10, sizeof(int));
    ESP_ERROR_CHECK(pcnt_unit_register_event_callbacks(encoder, &cbs, queue));

    int pulse_count = 0;
    int event_count = 0;

    while (1) {
        if (xQueueReceive(queue, &event_count, pdMS_TO_TICKS(1000))) {
            ESP_LOGI(TAG_ENCODER, "Watch point event, count: %d", event_count);
        } else {
            ESP_ERROR_CHECK(pcnt_unit_get_count(encoder, &pulse_count));
            ESP_LOGI(TAG_ENCODER, "Pulse count: %d", pulse_count);
        }
    }
}