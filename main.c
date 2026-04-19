#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define LED 4
#define LED1 2
#define LED2 15
#define BOTAO 5

int estado_sistema = 0; // 0 = desligado | 1 = rodando | 2 = pausado
int estado_anterior = 1;

void ler_botao() {
    int estado_atual = gpio_get_level(BOTAO);

    if (estado_anterior == 1 && estado_atual == 0) {
        if (estado_sistema == 0) {
          estado_sistema = 1;
          printf("SISTEMA ATIVADO\n"); 
        }      

             else if (estado_sistema == 1) {
              estado_sistema = 2;
              printf("SISTEMA PAUSADO\n");
            }

              else {
                estado_sistema = 1;
                printf("SISTEMA RETOMADO\n");
              }

vTaskDelay(pdMS_TO_TICKS(200));
    }
    estado_anterior = estado_atual;
}

void desligar_todos() {
    gpio_set_level(LED, 0);
    gpio_set_level(LED1, 0);
    gpio_set_level(LED2, 0);
}

void ligar_todos(){
    gpio_set_level(LED, 1);
    gpio_set_level(LED1, 1);
    gpio_set_level(LED2, 1);
}

void piscar_ambos(int vezes, int delay_ms) { //Quando o num for múltiplo de 4 todos os leds piscam
    desligar_todos();

    for (int i = 0; i < vezes; i++) {
        ler_botao();
        if (estado_sistema != 1) return;
        ligar_todos();
        vTaskDelay(pdMS_TO_TICKS(delay_ms));

          ler_botao();
          if (estado_sistema != 1) return;
          desligar_todos();
          vTaskDelay(pdMS_TO_TICKS(delay_ms));
    }
}

void piscar(int vezes, int delay_ms) { //Quando o num for ímpar led Branco pisca
    desligar_todos();

    for (int i = 0; i < vezes; i++) {
      ler_botao();
      if (estado_sistema != 1) return;
      gpio_set_level(LED2, 1);
      vTaskDelay(pdMS_TO_TICKS(delay_ms));

        ler_botao();
        if (estado_sistema != 1) return;
        gpio_set_level(LED2, 0);
        vTaskDelay(pdMS_TO_TICKS(delay_ms));
    }
}

void piscar_alternado(int vezes, int delay_ms) { //Quando o num for par piscará leds Azul e Roxo
    desligar_todos();

    for (int i = 0; i < vezes; i++) {
    ler_botao();
    if (estado_sistema != 1) return;
    gpio_set_level(LED, 1);
    gpio_set_level(LED1, 0);
    vTaskDelay(pdMS_TO_TICKS(delay_ms));

      ler_botao();
      if (estado_sistema != 1) return;
      gpio_set_level(LED, 0);
      gpio_set_level(LED1, 1);
      vTaskDelay(pdMS_TO_TICKS(delay_ms));
    }
    desligar_todos();
}

void corrida_de_luz(int vezes, int delay_ms) { //Todos os leds vão piscar quando C == 20
    desligar_todos();

    for (int i = 0; i < vezes; i++) {
          ler_botao();
          if (estado_sistema != 1) return;
          gpio_set_level(LED, 1);
          vTaskDelay(pdMS_TO_TICKS(delay_ms));

            ler_botao();
            if (estado_sistema != 1) return;
            gpio_set_level(LED1, 1);
            vTaskDelay(pdMS_TO_TICKS(delay_ms));

              ler_botao();
              if (estado_sistema != 1) return;
              gpio_set_level(LED2, 1);
              vTaskDelay(pdMS_TO_TICKS(delay_ms));

                ler_botao();
                if (estado_sistema != 1) return;
                gpio_set_level(LED, 0);
                vTaskDelay(pdMS_TO_TICKS(delay_ms));

                  ler_botao();
                  if (estado_sistema != 1) return;
                  gpio_set_level(LED1, 0);
                  vTaskDelay(pdMS_TO_TICKS(delay_ms));

                    ler_botao();
                    if (estado_sistema != 1) return;
                    gpio_set_level(LED2, 0);
                    vTaskDelay(pdMS_TO_TICKS(delay_ms));
    }
    desligar_todos();
}

void app_main() {
    gpio_set_direction(LED, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED1, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED2, GPIO_MODE_OUTPUT);
    gpio_set_direction(BOTAO, GPIO_MODE_INPUT);
    gpio_set_pull_mode(BOTAO, GPIO_PULLUP_ONLY);

    int C = 0; //Contagem

    while (true) {

        ler_botao();

        if (estado_sistema == 1) { //Quando o sistema iniciar
          C++;
          printf("Número: %d\n", C);

            if (C % 4 == 0) {
              printf("Múltiplo de 4\n");
              piscar_ambos(2, 200);
            } 

            else if (C % 2 == 0) {
              printf("Par\n");
              piscar_alternado(2, 200);

            } 

            else {
              printf("Ímpar\n");
              piscar(2, 200);
            }

            if (C == 20) { //Depois da corrida muda o valor de C
                C = 0;
                printf("-------------------------\n");
                printf("Iniciando corrida!\n"); 
                corrida_de_luz(5, 200);
            }

            printf("-------------------------\n");
            vTaskDelay(pdMS_TO_TICKS(1500));
        }

        else if (estado_sistema == 2) { //Quando o sistema for pausado todos os leds acendem
            gpio_set_level(LED, 1);
            gpio_set_level(LED1, 1);
            gpio_set_level(LED2, 1);

            vTaskDelay(pdMS_TO_TICKS(100));
        }

        else {
            desligar_todos();
            vTaskDelay(pdMS_TO_TICKS(100));
        }
    }
}