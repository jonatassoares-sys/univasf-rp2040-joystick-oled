# Monitoramento de Joystick Analógico com Display OLED via Pico SDK e RP2040

Este repositório contém a documentação e o desenvolvimento completo da Atividade Prática de Laboratório realizada para a disciplina **Microcontroladores e Microprocessadores** (Código: **ELET0021**). O projeto foi desenvolvido sob a orientação do **Prof. Dr. Ricardo Menezes Prates** no Colegiado Acadêmico de Engenharia Elétrica da **Universidade Federal do Vale do São Francisco (UNIVASF)**, referente ao período letivo **2026.1** (Turma **E5**).

O objetivo principal do sistema é realizar a coleta, o monitoramento e a exibição em tempo real dos dados de tensão equivalentes ao sinal de um joystick analógico, utilizando os recursos internos do microcontrolador **RP2040** (especificamente o Conversor Analógico-Digital e a interface de comunicação $I^2C$) embarcados na plataforma educacional **BitDogLab**.

---

## Especificações do Hardware e Conexões

O projeto foi implementado utilizando os recursos físicos da ferramenta educacional **BitDogLab**, composta por:

1.**Microcontrolador:** Raspberry Pi Pico W (baseado no chip RP2040).
2. **Entrada Analógica (Periférico A):** Joystick Analógico (Plugin 13x13mm Multi-Dir ROHS).
3. **Saída Visual (Periférico B):** Display OLED de 0,96 polegadas com resolução de 128x64 pixels.

### Arquitetura de Conexões Internas (Mapeamento de Pinos)
* **Eixo X do Joystick:** Conectado a um dos canais analógicos do **ADC (Conversor Analógico-Digital)** nativo do RP2040. O ADC possui resolução nativa de 12 bits (valores discretos entre `0` e `4095`).
* **Display OLED:** Comunicando-se diretamente com o microcontrolador através do barramento **$I^2C$** utilizando os pinos seriais de dados (`SDA`) e clock (`SCL`).

---

##  Requisitos Funcionais e Detalhamento do Projeto

O firmware foi projetado e otimizado para atender estritamente aos seguintes critérios técnicos determinados no escopo do projeto[cite: 32]:

***Coleta de Dados:** O sistema realiza a leitura contínua do sinal analógico presente exclusivamente no **eixo X do joystick**.
***Processamento e Conversão:** O valor digital bruto de 12 bits lido pelo ADC é convertido matematicamente para o nível de tensão correspondente na escala real de **0V a 3.3V**.
* **Amostragem Temporal:** A taxa de atualização dos dados e renderização na tela do display OLED ocorre rigorosamente a cada **500 ms** (Tempo de amostragem requerido).
* **Plotagem de Curva (Etapa Opcional Implementada):** Além da exibição numérica do valor de tensão atual, o display OLED apresenta uma **curva dinâmica de comportamento** , gerando um gráfico em tempo real com o histórico das flutuações e movimentações do joystick.

---

##  Ambiente de Desenvolvimento e Diretrizes de Software

A construção lógica do software obedeceu às seguintes exigências de engenharia:
**Ambiente de Desenvolvimento:** Programado e gerenciado através do **VS Code (Visual Studio Code)**.
* **Linguagem:** Escrita puramente em **Linguagem C** integrando as APIs do ecossistema **Pico SDK**.
**Simulação Integrada:** Arquivo de projeto e conexões (`diagram.json`) totalmente compatível com o simulador **Wokwi** integrado de forma nativa ao VS Code.
**Versionamento:** Registro de histórico e controle de modificações utilizando o **Git** e hospedado de forma pública no **GitHub**.

---

##  Demonstração em Vídeo (Vídeo Ensaio)

Como etapa mandatória para a conclusão e avaliação da prática , foi produzido um vídeo ensaio focado na explicação técnica da solução, demonstração do código-fonte e validação dos resultados com duração máxima de 5 minutos[cite: 45].


---

##  Desenvolvedores e Identificação do Grupo

*Jônatas de Sousa Soares da Cruz** 
  * *Curso:* Engenharia Elétrica — UNIVASF 
  
 **Natan Éder Valeriano** 
  *Curso:* Engenharia Elétrica — UNIVASF 
   

**Instituição:** Universidade Federal do Vale do São Francisco (UNIVASF) 
**Componente Curricular:** Microcontroladores e Microprocessadores (ELET0021)
**Período Letivo e Turma:** 2026.1 — Turma E5 
**Orientador Técnico:** Prof. Dr. Ricardo Menezes Prates 
**Data Limite de Submissão:** 30/06/2026 
---

## Como Executar o Projeto

### 1. Clonar e Configurar o Repositório
Abra o seu terminal e execute o comando abaixo para clonar o projeto:
```bash
git clone [https://github.com/jonatassoares-sys/univasf-rp2040-joystick-oled.git](https://github.com/jonatassoares-sys/univasf-rp2040-joystick-oled.git)
cd univasf-rp2040-joystick-oled
