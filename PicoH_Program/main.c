
#include <dht.h>
#include <pico/stdlib.h>
#include <stdio.h>
#include "LCD1602APico.h"
#include <string.h>
#include "hardware/clocks.h"

// change this to match your setup
static const dht_model_t DHT_MODEL = DHT11;
static const uint DATA_PIN = 15;

// static float celsius_to_fahrenheit(float temperature) {
//     return temperature * (9.0f / 5) + 32;
// }

int main() {
    stdio_init_all();
    lcd_init();

    set_sys_clock_khz(50000, true);

    dht_t dht;//todo delete Fahrenheit
    dht_init(&dht, DHT_MODEL, pio0, DATA_PIN, true /* pull_up */);
    do {
        dht_start_measurement(&dht);
        
        float humidity;
        float temperature_c;
        dht_result_t result = dht_finish_measurement_blocking(&dht, &humidity, &temperature_c);
        if (result == DHT_RESULT_OK) {
            printf("%.1f C %.1f%% humidity\n", temperature_c, humidity);
        } else if (result == DHT_RESULT_TIMEOUT) {
            puts("DHT sensor not responding. Please check your wiring.");
        } else {
            assert(result == DHT_RESULT_BAD_CHECKSUM);
            puts("Bad checksum");
        }


        lcd_set_cursor(0, 0);  // Move to Line 1, Column 0
        lcd_write_string("Temperature:");

        lcd_set_cursor(1, 0);  // Move to Line 2, Column 0

        char value[16];
        sprintf(value,"%14.1f C",temperature_c);
        
        //strcat(value, " C");
        lcd_write_string(value);

        sleep_ms(5000);

        lcd_set_cursor(0, 0);  
        lcd_write_string("Humidity:       ");

        lcd_set_cursor(1, 0);  

        sprintf(value,"%14.1f %%",humidity);

        //strcat(value, "% ");
        lcd_write_string(value);


        sleep_ms(5000);
    } while (true);
}

