#ifndef SSD1306_H
#define SSD1306_H

#include "hardware/i2c.h"
#include <stdint.h>

// Definições padrão do display da BitDogLab
#define SSD1306_I2C_ADDR 0x3C
#define SSD1306_WIDTH 128
#define SSD1306_HEIGHT 64

// Funções que o main.c vai poder usar
void ssd1306_init(i2c_inst_t *i2c);
void ssd1306_clear(void);
void ssd1306_show(i2c_inst_t *i2c);
void ssd1306_draw_char(uint8_t x, uint8_t y, char c);
void ssd1306_draw_string(uint8_t x, uint8_t y, const char *str);

#endif