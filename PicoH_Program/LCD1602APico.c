#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

#define RS 2
#define E  3
#define D4 4
#define D5 5
#define D6 6
#define D7 7

void lcd_send_nibble(uint8_t data) {
    gpio_put(D4, (data >> 0) & 1);
    gpio_put(D5, (data >> 1) & 1);
    gpio_put(D6, (data >> 2) & 1);
    gpio_put(D7, (data >> 3) & 1);
    
    gpio_put(E, 1);
    sleep_us(1);
    gpio_put(E, 0);
    sleep_us(100);
}

void lcd_send_byte(uint8_t data, bool is_cmd) {
    gpio_put(RS, is_cmd ? 0 : 1);
    lcd_send_nibble(data >> 4);
    lcd_send_nibble(data & 0x0F);
    sleep_ms(2);
}

void lcd_init() {
    gpio_init(RS);
    gpio_init(E);
    gpio_init(D4);
    gpio_init(D5);
    gpio_init(D6);
    gpio_init(D7);

    gpio_set_dir(RS, GPIO_OUT);
    gpio_set_dir(E, GPIO_OUT);
    gpio_set_dir(D4, GPIO_OUT);
    gpio_set_dir(D5, GPIO_OUT);
    gpio_set_dir(D6, GPIO_OUT);
    gpio_set_dir(D7, GPIO_OUT);

    sleep_ms(50);
    lcd_send_nibble(0x03);
    sleep_ms(5);
    lcd_send_nibble(0x03);
    sleep_us(150);
    lcd_send_nibble(0x03);
    sleep_ms(5);
    lcd_send_nibble(0x02); // Set 4-bit mode

    lcd_send_byte(0x28, 1); // 4-bit, 2 lines, 5x8 dots
    lcd_send_byte(0x0C, 1); // Display ON, Cursor OFF
    lcd_send_byte(0x06, 1); // Entry mode: move right
    lcd_send_byte(0x01, 1); // Clear display
    sleep_ms(2);
}

void lcd_write_char(char c) {
    lcd_send_byte(c, 0);
}

void lcd_write_string(const char *str) {
    while (*str) {
        lcd_write_char(*str++);
    }
}

void lcd_set_cursor(uint8_t row, uint8_t col) {
    uint8_t address = (row == 0) ? (0x00 + col) : (0x40 + col);
    lcd_send_byte(0x80 | address, 1);
}

// Reduce CPU speed to 10 MHz
// void reduceCPU(){
//     set_sys_clock_khz(10000, true);
// }

// void increaseCPU(){
//     set_sys_clock_khz(125000, true);
// }

// int main() {
//     stdio_init_all();
//     lcd_init();

//     char letter = 'a';
    

//     while (1) {

//         lcd_set_cursor(0, 0);  // Move to Line 1, Column 0
//     lcd_write_string("Hello, Pico!");

//     lcd_set_cursor(1, 0);  // Move to Line 2, Column 0
        

//         lcd_write_char(letter);

//         letter++;
        
//         sleep_ms(1000);
//     }
// }

