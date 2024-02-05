/* BSD Socket API Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <string.h>
#include <sys/param.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "esp_netif.h"
#include "protocol_examples_common.h"

#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include <lwip/netdb.h>

#include "joystick_service.h"
#include "robot_position_state.h"

#define HOST_IP_ADDR CONFIG_EXAMPLE_IPV4_ADDR

#define PORT CONFIG_EXAMPLE_PORT

static const char *TAG = "example";
// static const char *payload = "Message from ESP32 ";

static const char * MESSAGE_FORWARD = "MOVING_FORWARD";
static const char * MESSAGE_BACKWARD = "MOVING_BACKWARD";
static const char * MESSAGE_LEFT = "ROTATE_LEFT";
static const char * MESSAGE_RIGHT = "ROTATE_RIGHT";
static const char * MESSAGE_STOP = "STOP";



static void udp_client_task(void *pvParameters){
    char rx_buffer[128];
    char host_ip[] = HOST_IP_ADDR;
    int addr_family = 0;
    int ip_protocol = 0;

    while (1) {

        struct sockaddr_in dest_addr;
        dest_addr.sin_addr.s_addr = inet_addr(HOST_IP_ADDR);
        dest_addr.sin_family = AF_INET;
        dest_addr.sin_port = htons(PORT);
        addr_family = AF_INET;
        ip_protocol = IPPROTO_IP;

        int sock = socket(addr_family, SOCK_DGRAM, ip_protocol);
        if (sock < 0) {
            ESP_LOGE(TAG, "Unable to create socket: errno %d", errno);
            break;
        }

        // Set timeout
        struct timeval timeout;
        timeout.tv_sec = 10;
        timeout.tv_usec = 0;
        setsockopt (sock, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof timeout);

        ESP_LOGI(TAG, "Socket created, sending to %s:%d", HOST_IP_ADDR, PORT);


        while (1) {

            char * payload = NULL;
            int i;
            int err;
            int times = 1000;

            // payload = MESSAGE_FORWARD;
            // err = sendto(sock, payload, strlen(payload), 0, (struct sockaddr *)&dest_addr, sizeof(dest_addr));
            // if (err < 0) {
            //     ESP_LOGE(TAG, "Error occurred during sending: errno %d", errno);
            //     break;
            // }

            payload = MESSAGE_FORWARD;
            for(i=0; i<times ; i++){
                err = sendto(sock, payload, strlen(payload), 0, (struct sockaddr *)&dest_addr, sizeof(dest_addr));
                if (err < 0) {
                    ESP_LOGE(TAG, "Error occurred during sending: errno %d", errno);
                    break;
                }
                ESP_LOGI(TAG, "Mensaje enviado [%s]", payload);
                vTaskDelay(5 / portTICK_PERIOD_MS);
                
            }

            payload = MESSAGE_STOP;
            for(i=0; i<times ; i++){
                err = sendto(sock, payload, strlen(payload), 0, (struct sockaddr *)&dest_addr, sizeof(dest_addr));
                if (err < 0) {
                    ESP_LOGE(TAG, "Error occurred during sending: errno %d", errno);
                    break;
                }

                ESP_LOGI(TAG, "Mensaje enviado [%s]", payload);
                vTaskDelay(5 / portTICK_PERIOD_MS);
            }

            payload = MESSAGE_BACKWARD;
            for(i=0; i<times ; i++){
                err = sendto(sock, payload, strlen(payload), 0, (struct sockaddr *)&dest_addr, sizeof(dest_addr));
                if (err < 0) {
                    ESP_LOGE(TAG, "Error occurred during sending: errno %d", errno);
                    break;
                }

                ESP_LOGI(TAG, "Mensaje enviado [%s]", payload);
                vTaskDelay(5 / portTICK_PERIOD_MS);
            }

            payload = MESSAGE_STOP;
            for(i=0; i<times ; i++){
                err = sendto(sock, payload, strlen(payload), 0, (struct sockaddr *)&dest_addr, sizeof(dest_addr));
                if (err < 0) {
                    ESP_LOGE(TAG, "Error occurred during sending: errno %d", errno);
                    break;
                }

                ESP_LOGI(TAG, "Mensaje enviado [%s]", payload);
                vTaskDelay(5 / portTICK_PERIOD_MS);
            }

            payload = MESSAGE_LEFT;
            for(i=0; i<times ; i++){
                err = sendto(sock, payload, strlen(payload), 0, (struct sockaddr *)&dest_addr, sizeof(dest_addr));
                if (err < 0) {
                    ESP_LOGE(TAG, "Error occurred during sending: errno %d", errno);
                    break;
                }

                ESP_LOGI(TAG, "Mensaje enviado [%s]", payload);
                vTaskDelay(5 / portTICK_PERIOD_MS);
            }

            payload = MESSAGE_STOP;
            for(i=0; i<times ; i++){
                err = sendto(sock, payload, strlen(payload), 0, (struct sockaddr *)&dest_addr, sizeof(dest_addr));
                if (err < 0) {
                    ESP_LOGE(TAG, "Error occurred during sending: errno %d", errno);
                    break;
                }

                ESP_LOGI(TAG, "Mensaje enviado [%s]", payload);
                vTaskDelay(5 / portTICK_PERIOD_MS);
            }

            payload = MESSAGE_RIGHT;
            for(i=0; i<times ; i++){
                err = sendto(sock, payload, strlen(payload), 0, (struct sockaddr *)&dest_addr, sizeof(dest_addr));
                if (err < 0) {
                    ESP_LOGE(TAG, "Error occurred during sending: errno %d", errno);
                    break;
                }

                ESP_LOGI(TAG, "Mensaje enviado [%s]", payload);
                vTaskDelay(5 / portTICK_PERIOD_MS);
            }

            payload = MESSAGE_STOP;
            for(i=0; i<times ; i++){
                err = sendto(sock, payload, strlen(payload), 0, (struct sockaddr *)&dest_addr, sizeof(dest_addr));
                if (err < 0) {
                    ESP_LOGE(TAG, "Error occurred during sending: errno %d", errno);
                    break;
                }

                ESP_LOGI(TAG, "Mensaje enviado [%s]", payload);
                vTaskDelay(5 / portTICK_PERIOD_MS);
            }


            // int err = sendto(sock, payload, strlen(payload), 0, (struct sockaddr *)&dest_addr, sizeof(dest_addr));
            // if (err < 0) {
            //     ESP_LOGE(TAG, "Error occurred during sending: errno %d", errno);
            //     break;
            // }
            // ESP_LOGI(TAG, "Message sent");

            // struct sockaddr_storage source_addr;
            // socklen_t socklen = sizeof(source_addr);
            // int len = recvfrom(sock, rx_buffer, sizeof(rx_buffer) - 1, 0, (struct sockaddr *)&source_addr, &socklen);
            // if (len < 0) {
            //     ESP_LOGE(TAG, "recvfrom failed: errno %d", errno);
            // }
            // else {
            //     rx_buffer[len] = 0; 
            //     ESP_LOGI(TAG, "Received %d bytes from %s: [%s]", len, host_ip , rx_buffer);
            //     if (strncmp(rx_buffer, "OK: ", 4) == 0) {
            //         ESP_LOGI(TAG, "Received expected message, reconnecting");
            //         break;
            //     }
            // }

            // vTaskDelay(2000 / portTICK_PERIOD_MS);

        }

        if (sock != -1) {
            ESP_LOGE(TAG, "Shutting down socket and restarting...");
            shutdown(sock, 0);
            close(sock);
        }
    }
    vTaskDelete(NULL);
}


void joystick_task(void * args){

    joystick_initialize();

    float reading_x ;
    float reading_y ;

    while (1) {

        joystick_get_reading(&reading_x , &reading_y);

        robot_position_state_update(reading_x , reading_y);

        ESP_LOGI("POC Joystick", " (%.2f , %.2f) ", reading_x , reading_y);

        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}


void app_main(void)
{
    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    /* This helper function configures Wi-Fi or Ethernet, as selected in menuconfig.
     * Read "Establishing Wi-Fi or Ethernet Connection" section in
     * examples/protocols/README.md for more information about this function.
     */
    ESP_ERROR_CHECK(example_connect());

    xTaskCreate(udp_client_task, "udp_client", 4096, NULL, 5, NULL);
}