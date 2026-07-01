#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/i2c.h"
#include "ssd1306.h"

// Pinos da BitDogLab
#define I2C_PORT i2c1
#define I2C_SDA_PIN 14
#define I2C_SCL_PIN 15
#define JOYSTICK_X_PIN 26

int main() {
    stdio_init_all();

    // 1. Inicializa o barramento I2C
    i2c_init(I2C_PORT, 400 * 1000); // Frequência de 400 kHz
    gpio_set_function(I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA_PIN);
    gpio_pull_up(I2C_SCL_PIN);

    // Inicializa o display OLED
    ssd1306_init(I2C_PORT);

    // 2. Inicializa o conversor Analógico-Digital (ADC)
    adc_init();
    adc_gpio_init(JOYSTICK_X_PIN);
    adc_select_input(0); // Seleciona o canal 0, que corresponde ao GPIO 26

    // Variáveis de armazenamento
    uint16_t adc_value;
    float voltage;
    char buffer[32];

    while (true) {
        // Coleta o valor do ADC (vai de 0 a 4095)
        adc_value = adc_read();
        
        // Converte para a tensão correspondente em Volts
        voltage = adc_value * (3.3f / 4095.0f);

        // Formata o texto que vai para a tela
        sprintf(buffer, "TENSAO: %.2f V", voltage);
        
        // Limpa a tela, desenha o novo texto e envia para o OLED
        ssd1306_clear();
        ssd1306_draw_string(0, 0, "LEITURA EIXO X:");
        ssd1306_draw_string(0, 20, buffer);
        ssd1306_show(I2C_PORT);

        // Tempo de amostragem para atualização dos dados [cite: 34]
        sleep_ms(500);
    }
}