# **CONTROLE DE SERVOMOTOR POR PWM NO RP2040**

Está contido neste repositório o diagrama, código-fonte e demais arquivos referentes a primeira parte da última Prática de Laboratório da matéria de Microcontroladores e Microprocessadores.

## **OBJETIVO**

Este projeto tem como objetivo o controle do ângulo de um servomotor através do módulo PWM, utilizando um Raspberry Pi Pico W e ferramentas de simulação virtual.

## **COMPONENTES UTILIZADOS**

- Microcontrolador Raspberry Pi Pico W;
- 01 Servomotor;
- 01 LED RGB.
- Simulador computacional Wokwi

## **SEQUÊNCIAS DE INSTRUÇÕES**

1. Configuração da GPIO 26 para PWM:
- A frequência de PWM foi configurada para aproximadamente 50Hz (período de 20ms).
- A flange do servomotor foi ajustada inicialmente para a posição de 0 graus com um ciclo ativo de 500µs (2,5% de Duty Cycle).
- O LED Verde é ligado com baixa intensidade.
- O servomotor e o LED RGB aguardam 3 segundos nestas posições.

2. Ajuste da posição do servomotor para 90 graus:
- O ciclo ativo foi ajustado para 1.470µs (7,35% de Duty Cycle).
- A flange do servomotor foi movida para a posição de 90 graus.
- O LED Azul é ligado com meia intensidade.
- Ambos aguardam 3 segundos nestas posições.

3. Movimento do servomotor para 180 graus:
- O ciclo ativo foi ajustado para 1400µs (2,5% de Duty Cycle).
- A flange foi movida para a posição de 180 graus.
- O LED Vermelho é ligado com máxima intensidade.
- Ambos aguardam 3 segundos nestas posições.

4. Movimentação periódica do braço do servomotor entre 0 e 180 graus:
- A movimentação foi feita suavemente, com incremento do ciclo ativo de ±5µs e um atraso de 10ms a cada ajuste de posição.
- O LED RGB foi alternando as cores acessas suavemente produzindo uma espécie de arco-íris, tendo as cores definidas como:
     VERMELHO: Diretamente proporcional ao ângulo do servomotor (máximo em 180 graus)
     VERDE: Inversamente proporcional ao ângulo do servomotor (máximo em 0 graus)
     AZUL: Máximo em 90 graus

## Organização da Equipe
- **Líder de Projeto: João Victor Guimarães** (Codificação e simulação no wokwi)
- **Desenvolvedor 1: João Victor Teixeira** (Escrita do repositório)
- **Desenvolvedor 2: Ryan Farias** (Compilação no VS Code e gravação de vídeo)

---

## **VÍDEO DE FUNCIONAMENTO**

https://www.canva.com/design/DAGtWLygTQk/cJX9Vy5qZN5BNMJtptZzpw/edit?utm_content=DAGtWLygTQk&utm_campaign=designshare&utm_medium=link2&utm_source=sharebutton

## Licença
Este projeto é destinado exclusivamente para fins acadêmicos na disciplina **ELET0021 — Microcontroladores e Microprocessadores**.

---
