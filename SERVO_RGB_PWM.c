// Inclusão das bibliotecas
#include <stdio.h>                      // Biblioteca padrão de entrada/saída
#include "pico/stdlib.h"               // Funções básicas do Raspberry Pi Pico
#include "hardware/pwm.h"              // Acesso ao hardware PWM
#include <math.h>                      // Biblioteca matemática (para fabs())

// Definições de pinos e parâmetros
#define SERVO_PIN 26                   // Pino que controla o servo (GP26)
#define LED_R_PIN 14                   // Pino do canal vermelho do LED RGB (GP14)
#define LED_G_PIN 13                   // Pino do canal verde do LED RGB (GP13)
#define LED_B_PIN 12                   // Pino do canal azul do LED RGB (GP12)

#define PWM_CLOCK_DIVIDER 64.0         // Divisor de clock para gerar frequência de 50Hz (servo)
#define PWM_PERIOD_US 20000.0          // Período do PWM em microssegundos (20ms = 50Hz)
#define PWM_TOP_VALUE 39063            // Valor máximo do contador PWM (para ~50Hz com divisor 64)

/*  Cálculo do TOP:

  freq = CLK Base / CLK Div * (TOP + 1)

  -> 50 = 125 * 10^6 / 64 * (TOP + 1)
  -> TOP = 39063

*/

uint slice_servo;                        // Variável para armazenar o slice PWM do servo
uint slice_r, slice_g, slice_b;        // Slices PWM dos canais R, G e B

// Calcula o duty cycle proporcional ao tempo de pulso desejado
static uint16_t calculate_pwm_duty(float pulse_width_us) {
    if (pulse_width_us < 0) pulse_width_us = 0;
    if (pulse_width_us > PWM_PERIOD_US) pulse_width_us = PWM_PERIOD_US;
    return (uint16_t)((pulse_width_us / PWM_PERIOD_US) * PWM_TOP_VALUE);
}

// Aplica o duty cycle calculado no pino especificado
static void set_pwm_pulse(uint slice, uint gpio, float pulse_width_us) {
    uint16_t duty_cycle = calculate_pwm_duty(pulse_width_us);
    pwm_set_gpio_level(gpio, duty_cycle);
}

// Inicializa um pino GPIO para uso com PWM
static void initialize_pwm_pin(uint gpio, uint *slice_num) {
    gpio_set_function(gpio, GPIO_FUNC_PWM);                  // Define função PWM no pino
    *slice_num = pwm_gpio_to_slice_num(gpio);                // Descobre qual slice controla esse pino
    pwm_set_clkdiv(*slice_num, PWM_CLOCK_DIVIDER);           // Define o divisor do clock (64)
    pwm_set_wrap(*slice_num, PWM_TOP_VALUE);                 // Define o valor máximo do contador PWM
    pwm_set_enabled(*slice_num, true);                       // Ativa o PWM nesse slice
}

int main() {
    stdio_init_all(); // Inicializa as interfaces padrão

    // Inicialização dos pinos PWM
    initialize_pwm_pin(SERVO_PIN, &slice_servo);             // Servo (GP26)
    initialize_pwm_pin(LED_R_PIN, &slice_r);                 // LED Vermelho (GP14)
    initialize_pwm_pin(LED_G_PIN, &slice_g);                 // LED Verde (GP13)
    initialize_pwm_pin(LED_B_PIN, &slice_b);                 // LED Azul (GP12)

    sleep_ms(1000);  // Espera 1 segundo antes de iniciar


    // Movimento fixo para 0 graus (pulso ~500us)
    set_pwm_pulse(slice_servo, SERVO_PIN, 500);              // Servo em 0°
    set_pwm_pulse(slice_r, LED_R_PIN, 0);                    // LED vermelho desligado
    set_pwm_pulse(slice_g, LED_G_PIN, 500);                  // LED verde no início (baixa intensidade)
    set_pwm_pulse(slice_b, LED_B_PIN, 0);                    // LED azul desligado
    sleep_ms(3000);                                          // Espera 3s


    // Movimento fixo para 90 graus (pulso ~1470us)
    set_pwm_pulse(slice_servo, SERVO_PIN, 1470);             // Servo em 90°
    set_pwm_pulse(slice_r, LED_R_PIN, 0);                    // LED vermelho desligado
    set_pwm_pulse(slice_g, LED_G_PIN, 0);                    // LED verde desligado
    set_pwm_pulse(slice_b, LED_B_PIN, 1470);                 // LED azul no meio (~meia intensidade)
    sleep_ms(3000);                                          // Espera 3s


    // Movimento fixo para 180 graus (pulso ~2400us) 
    set_pwm_pulse(slice_servo, SERVO_PIN, 2400);             // Servo em 180°
    set_pwm_pulse(slice_r, LED_R_PIN, 2400);                 // LED vermelho no máximo
    set_pwm_pulse(slice_g, LED_G_PIN, 0);                    // LED verde desligado
    set_pwm_pulse(slice_b, LED_B_PIN, 0);                    // LED azul desligado
    sleep_ms(3000);                                          // Espera 3s


    // Movimento suave contínuo de vai-e-volta
    while (true) {
        
        // Movimento crescente: 0° até 180°
        for (float pulse = 500; pulse <= 2400; pulse += 5) {
            set_pwm_pulse(slice_servo, SERVO_PIN, pulse);    // Atualiza posição do servo
            

            // Variação de cores RGB proporcional ao pulso:
            float red = pulse;                      // Vermelho aumenta com o pulso
            float green = 2400 - pulse;             // Verde diminui com o pulso
            float blue = 1470 - fabs(pulse - 1470);        // Azul é mais forte no meio (~90°)

            set_pwm_pulse(slice_r, LED_R_PIN, red);
            set_pwm_pulse(slice_g, LED_G_PIN, green);
            set_pwm_pulse(slice_b, LED_B_PIN, blue);

            sleep_ms(10);  // Espera entre atualizações (animação suave)
        }

        // Movimento decrescente: 180° até 0°
        for (float pulse = 2400; pulse >= 500; pulse -= 5) {
            set_pwm_pulse(slice_servo, SERVO_PIN, pulse);

            float red = pulse;
            float green = 2400 - pulse;
            float blue = 1470 - fabs(pulse - 1470);

            set_pwm_pulse(slice_r, LED_R_PIN, red);
            set_pwm_pulse(slice_g, LED_G_PIN, green);
            set_pwm_pulse(slice_b, LED_B_PIN, blue);

            sleep_ms(10);
        }
    }

    return 0;
}
