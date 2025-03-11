#ifndef LCD_H
#define LCD_H

#include <stdio.h>
#include "pico/stdlib.h"

// Define LCD GPIO Pins
#define RS 2
#define E  3
#define D4 4
#define D5 5
#define D6 6
#define D7 7

// Function prototypes
void lcd_init();
void lcd_send_byte(uint8_t data, bool is_cmd);
void lcd_write_char(char c);
void lcd_write_string(const char *str);
void lcd_set_cursor(uint8_t row, uint8_t col);

// void reduceCPU();
// void increaseCPU();

#endif // LCD_H