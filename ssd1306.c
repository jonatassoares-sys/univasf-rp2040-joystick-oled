#include "ssd1306.h"
#include "font.h"
#include <string.h>

// O buffer de memória que espelha a tela inteira (128 * 64 / 8 bytes = 1024 bytes)
static uint8_t ssd1306_buffer[SSD1306_WIDTH * SSD1306_HEIGHT / 8];

// Função interna para enviar comandos de configuração para o OLED
static void ssd1306_send_cmd(i2c_inst_t *i2c, uint8_t cmd) {
    uint8_t buf[2] = {0x00, cmd}; // 0x00 significa que o próximo byte é um comando
    i2c_write_blocking(i2c, SSD1306_I2C_ADDR, buf, 2, false);
}

// Inicializa o display com a sequência mágica de comandos do datasheet
void ssd1306_init(i2c_inst_t *i2c) {
    uint8_t cmds[] = {
        0xAE,         // Desliga o display
        0xD5, 0x80,   // Configura o clock
        0xA8, 0x3F,   // Multiplex ratio
        0xD3, 0x00,   // Display offset
        0x40,         // Start line (0)
        0x8D, 0x14,   // Liga a bomba de carga (Charge pump)
        0x20, 0x00,   // Modo de memória (Horizontal addressing)
        0xA1,         // Segment remap (Inverte o eixo X)
        0xC8,         // COM scan direction (Inverte o eixo Y)
        0xDA, 0x12,   // COM pin hardware configuration
        0x81, 0xCF,   // Contraste
        0xD9, 0xF1,   // Pre-charge period
        0xDB, 0x40,   // VCOMH deselect level
        0xA4,         // Output follows RAM content
        0xA6,         // Normal display (não invertido)
        0xAF          // Liga o display
    };
    
    for (int i = 0; i < sizeof(cmds); i++) {
        ssd1306_send_cmd(i2c, cmds[i]);
    }
    
    ssd1306_clear();
    ssd1306_show(i2c);
}

// Limpa a tela (preenche o buffer com zeros)
void ssd1306_clear(void) {
    memset(ssd1306_buffer, 0, sizeof(ssd1306_buffer));
}

// Desenha um caractere na posição X, Y usando o font.h
void ssd1306_draw_char(uint8_t x, uint8_t y, char c) {
    if (c < 32 || c > 122) return; // Ignora se não estiver no nosso font.h
    
    uint8_t index = c - 32;
    uint16_t buffer_idx = x + (y / 8) * SSD1306_WIDTH;
    
    for (uint8_t i = 0; i < 5; i++) {
        if (x + i < SSD1306_WIDTH) {
            ssd1306_buffer[buffer_idx + i] = font[index * 5 + i];
        }
    }
}

// Desenha uma frase inteira (loop pelos caracteres)
void ssd1306_draw_string(uint8_t x, uint8_t y, const char *str) {
    uint8_t cursor_x = x;
    while (*str) {
        ssd1306_draw_char(cursor_x, y, *str);
        cursor_x += 6; // 5 pixels da letra + 1 de espaço
        str++;
    }
}

// Envia o buffer inteiro para o display de uma vez só
void ssd1306_show(i2c_inst_t *i2c) {
    // Definir a área que será atualizada (a tela inteira)
    ssd1306_send_cmd(i2c, 0x21); // Set Column Address
    ssd1306_send_cmd(i2c, 0);
    ssd1306_send_cmd(i2c, SSD1306_WIDTH - 1);
    
    ssd1306_send_cmd(i2c, 0x22); // Set Page Address
    ssd1306_send_cmd(i2c, 0);
    ssd1306_send_cmd(i2c, 7);

    // Array para enviar os dados. O primeiro byte (0x40) avisa que são dados (pixels), não comandos
    uint8_t payload[SSD1306_WIDTH * SSD1306_HEIGHT / 8 + 1];
    payload[0] = 0x40; 
    memcpy(&payload[1], ssd1306_buffer, sizeof(ssd1306_buffer));

    i2c_write_blocking(i2c, SSD1306_I2C_ADDR, payload, sizeof(payload), false);
}