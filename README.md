# Controlador de LEDs Reativo (FSM) – ESP32

## Descrição
Este projeto é um sistema embarcado desenvolvido para ESP32 que implementa uma Máquina de Estados Finitos (FSM) para controle de LEDs. O sistema utiliza um botão físico para alternar entre diferentes estados de operação, executando padrões de iluminação baseados em um contador interno.

## Funcionalidades

* - Controle de três estados:
* - Desligado
* - Rodando
* - Pausado
* - Controle por botão físico com detecção de mudança de estado
* - Padrões diferentes de LEDs baseados no valor de um contador:
    * Número ímpar
    * Número par
    * Múltiplo de 4
* - Sequência especial de "corrida de luz" ao atingir determinado valor
* - Controle independente de três LEDs

## Estrutura do Sistema

O projeto é baseado em FSM (Finite State Machine), onde o comportamento do sistema muda conforme o estado atual. Cada estado define como os LEDs devem se comportar.

## Tecnologias Utilizadas

* - ESP32
* - FreeRTOS
* - Linguagem C
* - Biblioteca GPIO do ESP-IDF

## Lógica do Projeto

* - O botão alterna entre os estados do sistema
* - Um contador interno define o padrão de LEDs
* - Cada estado executa uma rotina específica de comportamento

## Autor

Desenvolvido para fins de estudo e prática de sistemas embarcados e lógica de máquinas de estados finitos.
