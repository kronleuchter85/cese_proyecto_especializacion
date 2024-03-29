#include <string.h>
#include <stdio.h>
#include <math.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "driver/adc.h"
#include "esp_adc_cal.h"
#include <inttypes.h>


#define DEFAULT_VREF    1100        //Default vref

adc_channel_t channel = ADC_CHANNEL_0;      // ADC1:GPIO36, ADC2:GPIO4
adc_unit_t unit = ADC_UNIT_1;               // ADC2
adc_atten_t atten = ADC_ATTEN_DB_11;        // Full scale 0-3.9V, precision range 150mV-2450mV

esp_adc_cal_characteristics_t *adc_chars;

static const char *TAG = "temp_collector";


void app_main(void)
{

    adc1_config_width(ADC_WIDTH_BIT_12);
    adc1_config_channel_atten((adc1_channel_t)channel, atten);

    //Characterize ADC
    adc_chars = (esp_adc_cal_characteristics_t*) calloc(1, sizeof(esp_adc_cal_characteristics_t));
    esp_adc_cal_value_t val_type = esp_adc_cal_characterize(unit, atten, ADC_WIDTH_BIT_12, DEFAULT_VREF, adc_chars);

    while(1){

        int adc_reading = adc1_get_raw((adc1_channel_t)channel);
        uint32_t voltage = esp_adc_cal_raw_to_voltage(adc_reading, adc_chars);

        double vol = voltage / 1000.0f;
        // double Rt = 10 * vol / (3.3 - vol); //calculate resistance value of thermistor
        // double tempK = 1 / (1 / (273.15 + 25) + log(Rt / 10) / 3950.0); //calculate temperature (Kelvin)
        // double tempC = tempK - 273.15;     //calculate temperature (Celsius)

        ESP_LOGI(TAG, "ADC value : %d ,Voltage : %.2f V\n" , adc_reading, vol);

        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }

  
}
