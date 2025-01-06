# Sistema de Controle de Esteira com Sensor de Opacidade

[![License](https://img.shields.io/badge/License-MIT-green)](https://opensource.org/licenses/MIT)
[![STM32](https://img.shields.io/badge/STM32-F103-blue)](https://www.st.com/en/microcontrollers-microprocessors/stm32f103.html)
[![C Code](https://img.shields.io/badge/Language-C-orange)](https://en.wikipedia.org/wiki/C_(programming_language))

Este repositório contém o código de um sistema embarcado utilizando um microcontrolador STM32F10x, responsável pelo controle de uma esteira. O sistema é equipado com um sensor de opacidade e um display LCD para mostrar informações em tempo real.

## Descrição

O sistema foi projetado para controlar uma esteira que transporta objetos. A funcionalidade principal é detectar se os objetos que passam pela esteira são opacos ou não, e contar quantos de cada tipo passaram por ela. A contagem é exibida em tempo real em um display LCD, e o comportamento da esteira é ajustado conforme o tipo de objeto detectado. O código é escrito em linguagem C e executado em um microcontrolador STM32F10x.

### Funcionalidades Principais

- **Controle da Esteira**: A esteira é ativada automaticamente quando um objeto é detectado e desliga após a passagem de um número determinado de itens.
- **Detecção de Opacidade**: O sistema verifica se o objeto detectado pelo sensor de opacidade é opaco ou não.
- **Contagem de Objetos**: O número de objetos opacos e não opacos que passaram pela esteira é contado e exibido no LCD.
- **Exibição em LCD**: O número total de objetos opacos e não opacos é mostrado em tempo real no display LCD.
- **Temporização e Interrupções**: O sistema utiliza um temporizador para gerar interrupções, permitindo que o contador de objetos e as informações exibidas no LCD sejam atualizados periodicamente.

## Como Funciona

1. **Inicialização**: 
   O sistema inicia configurando os pinos GPIO do microcontrolador para controlar a esteira e LEDs de status (indicando se o objeto é opaco ou não), bem como o sensor de opacidade. Além disso, é configurado um temporizador para gerar interrupções a cada segundo, permitindo a atualização periódica dos dados no display LCD.

2. **Processo de Detecção e Contagem**:
   - Quando um objeto passa pelo sensor, o sistema verifica se ele é opaco ou não.
   - Se o objeto for opaco, o LED verde é aceso e o contador de objetos opacos é incrementado. Se o objeto não for opaco, o LED azul é aceso e o contador de objetos não opacos é incrementado.
   - Após a detecção, o número total de objetos (opacos e não opacos) é atualizado no display LCD.

3. **Controle da Esteira**:
   - A esteira é acionada automaticamente quando um objeto é detectado.
   - Após a passagem de 20 objetos, a esteira é desligada.
   - O sistema exibe mensagens no LCD indicando o status da esteira, como "Esteira Vazia" ou "Objeto na Esteira", conforme o caso.

4. **Interrupções e Atualização Periódica**:
   - O temporizador configurado no sistema gera interrupções a cada segundo, o que permite a atualização periódica da tela LCD com as informações mais recentes sobre a contagem de objetos.
   - Durante essas interrupções, as contagens de objetos opacos e não opacos são exibidas no LCD, e o sistema também limpa os indicadores de status quando necessário.

## Estrutura do Sistema

O sistema é composto pelos seguintes componentes principais:

- **Microcontrolador STM32F10x**: Responsável pelo controle do sistema, incluindo a leitura dos sensores, controle da esteira, e exibição das informações no LCD.
- **Sensor de Opacidade**: Detecta se um objeto que passa pela esteira é opaco ou não.
- **Display LCD**: Exibe as informações em tempo real, como a contagem de objetos opacos e não opacos, e o status da esteira.
- **LEDs de Status**: Indicam visualmente se o objeto detectado é opaco ou não opaco.

## Como Usar

### Pré-requisitos

- **Hardware**: Um microcontrolador STM32F10x, um display LCD (geralmente LCD 16x2) e um sensor de opacidade.
- **Software**: Um ambiente de desenvolvimento compatível com STM32, como o STM32CubeIDE ou KEIL.

### Passos para Execução

1. **Clonando o Repositório**:
   - Clone este repositório usando o comando:
     ```bash
     git clone https://github.com/username/SistemaEsteiraOpacidade.git
     ```

2. **Configuração do Ambiente de Desenvolvimento**:
   - Abra o projeto no seu ambiente de desenvolvimento preferido (STM32CubeIDE ou KEIL).

3. **Compilação e Upload**:
   - Compile o código e faça o upload para o microcontrolador STM32F10x.

4. **Conexão do Hardware**:
   - Conecte o display LCD, o sensor de opacidade e os LEDs de status ao microcontrolador conforme o diagrama de pinagem.

5. **Operação**:
   - Após a inicialização, o sistema começará a operar automaticamente, exibindo no LCD o status da esteira e as contagens de objetos opacos e não opacos.

## Contribuições

Contribuições são bem-vindas! Se você tiver sugestões ou melhorias para o código, sinta-se à vontade para abrir uma *issue* ou enviar um *pull request*.

## Licença

Este projeto está licenciado sob a **MIT License**. Consulte o arquivo [LICENSE](LICENSE) para mais detalhes.

---

Se você tiver dúvidas ou sugestões, não hesite em abrir uma *issue* ou enviar uma mensagem.
