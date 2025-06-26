# **CONTROLE DE SERVOMOTOR POR PWM NO RP2040**

Está contido neste repositório o diagrama, código-fonte e demais arquivos referentes a primeira parte da última Prática de Laboratório da matéria de Microcontroladores e Microprocessadores.

## **OBJETIVO**

Este projeto tem como objetivo o controle do ângulo de um servomotor através do módulo PWM, utilizando um Raspberry Pi Pico W e ferramentas de simulação virtual.

## **COMPONENTES UTILIZADOS**

- Microcontrolador Raspberry Pi Pico W;
- 01 Servomotor;
- 01 Led.
- Simulador computacional Wokwi

## **FUNCIONALIDADES IMPLEMENTADAS**

1. Configuração da GPIO 22 para PWM:
- A frequência de PWM foi configurada para aproximadamente 50Hz (período de 20ms).
- A flange do servomotor foi ajustada para a posição de 180 graus com um ciclo ativo de 2.400µs (0,12% de Duty Cycle).
- O código aguarda 05 segundos nesta posição.

2. Ajuste da posição do servomotor para 90 graus:
- O ciclo ativo foi ajustado para 1.470µs (0,0735% de Duty Cycle).
- A flange do servomotor foi movida para a posição de 90 graus, aguardando 05 segundos nesta posição.

3. Movimento do servomotor para 0 graus:
- O ciclo ativo foi ajustado para 500µs (0,025% de Duty Cycle).
- A flange foi movida para a posição de 0 graus, aguardando 05 segundos nesta posição.

4. Movimentação periódica do braço do servomotor entre 0 e 180 graus:
- A movimentação foi feita suavemente, com incremento do ciclo ativo de ±5µs e um atraso de 10ms a cada ajuste de posição.

5. Experimento com LED RGB:
- Utilizando a GPIO 12, foi realizado um experimento para observar o comportamento do LED RGB com as variações do ciclo de PWM.
- Foi observado que o LED exibiu mudanças de cor e intensidade em função da variação do PWM, refletindo as alterações de ciclo ativo.

## Organização da Equipe
- **Líder de Projeto:** [VITÓRIA CAVAL5CANTI] — responsável pelo gerenciamento do repositório, estrutura do código e revisão dos pull requests.
- **Desenvolvedor 1:** [LÁISA BIANCA] — responsável pelo movimento do servomotor para 180 e 90 graus.
- **Desenvolvedor 2:** [LAÍSE CAFÉ] — responsável pelo movimento do servomor para 0 graus e o movimento continuo suave.

---

## **VÍDEO EXPLICATIVO**


## Licença
Este projeto é destinado exclusivamente para fins acadêmicos na disciplina **ELET0021 — Microcontroladores e Microprocessadores**.

---
