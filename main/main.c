#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "soc/soc_caps.h"
#include "esp_log.h"

#include <math.h>
#include "main.h"
#include "array_tools.h"
#include "adc_tools.h"


void app_main(void)
{
    adc_init();
    //int num_readings = 0;
    //int sum_readings = 0;
    while (1) {

        // GET MULTIPLE READINGS FROM ADC. FIND MEDIAN. TRANSLATE TO TEMP FAHR.
        uint32_t i_read_adc = 0;
        int adc_readings[ADC_NUM_READINGS];

        // Read adc. Put mv readings into array
        while(i_read_adc < ADC_NUM_READINGS) {
            adc_readings[i_read_adc] = read_adc() - ADJUST_MV_READING;

            vTaskDelay(pdMS_TO_TICKS(20));
            i_read_adc++;
        }

        int median_reading = find_median(adc_readings, ADC_NUM_READINGS);
        /*
        num_readings ++; 
        sum_readings += median_reading;
        float ave = sum_readings / num_readings;
        */

        // Voltage divider
        float Vs = 3.3;
        float Vin = median_reading * 0.001;
        float Rs = 10000.0;     // Resistor in series with thermistor
        float r_thermistor = (Rs*Vin)/(Vs-Vin);

        // Translate resistance to deg Cels
        float temp_cels_thermistor = (1.0/ ( (log(r_thermistor/Rs)/3892.0) + (1.0/298.0) ) ) - 273.0;
        float temp_fahr = ((temp_cels_thermistor * 9.0) / 5.0) + 32.0;
        ESP_LOGI(TAG, "ResTherm: %f   VoltR: %d  Temp F: %f",r_thermistor, median_reading, temp_fahr);
        //ESP_LOGI(TAG,  "Volt: %d  Average: %f   Num Reading: %d", median_reading, ave, num_readings);
    }

    adc_teardown();
}
