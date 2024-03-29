/* HTTP GET Example using plain POSIX sockets

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_system.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"

#include "dht.h"


#define ONE_WIRE_GPIO 4


static const gpio_num_t dht_gpio = ONE_WIRE_GPIO;
static const dht_sensor_type_t sensor_type = DHT_TYPE_DHT11;
static const char *TAG = "temp_collector";

static void measuring_task(void *pvParameters) {
    

    // gpio_set_direction(ONE_WIRE_GPIO,GPIO_MODE_INPUT);
    // gpio_set_pull_mode(ONE_WIRE_GPIO , GPIO_PULLUP_ONLY);
    int16_t temperature = 0;
    int16_t humidity = 0;

    while(1) {

        if (dht_read_data(sensor_type, dht_gpio, &humidity, &temperature) == ESP_OK) {
                     
            ESP_LOGI(TAG,"Humidity: %d%% Temp: %dC\n", humidity / 10, temperature / 10);
            
        } else {
            ESP_LOGE(TAG,"Could not read data from sensor\n");
        }

        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void app_main(void)
{
    ESP_ERROR_CHECK( nvs_flash_init() );
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    xTaskCreate(&measuring_task, "measuring_task", 4096, NULL, 5, NULL);
}
