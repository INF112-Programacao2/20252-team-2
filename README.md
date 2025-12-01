# ⚕️ Sistema de Monitoramento de Sinais Vitais Hospitalares


---

## 💡 Sobre o Projeto

O **Sistema de Monitoramento de Sinais Vitais Hospitalares** é uma solução de software de alto desempenho desenvolvida em **C++**, projetada para emular a infraestrutura digital de uma Unidade de Terapia Intensiva (UTI).

Este projeto transcende um simples cadastro de pacientes. Ele atua como um **Simulador de Biofeedback em Tempo Real**, onde cada paciente cadastrado torna-se uma entidade ativa no sistema, equipada com sensores virtuais que operam de forma autônoma e concorrente à interface do usuário.

O sistema foi arquitetado para resolver um problema clássico de sistemas críticos: **como processar dados fisiológicos de múltiplos pacientes simultaneamente, garantindo integridade e persistência, sem travar a operação administrativa.**

### 🧠 O "Motor" de Simulação Fisiológica
O coração deste projeto é seu algoritmo de geração de dados. Diferente de sistemas básicos que utilizam apenas números aleatórios, nossa *engine* simula o comportamento biológico real através de conceitos de **Homeostase e Variabilidade Estocástica**:

* **Tendência ao Equilíbrio:** Os sensores possuem um "Set Point" (ponto ideal fisiológico). Se a temperatura de um paciente sobe, o algoritmo calcula vetores de tendência para trazê-la de volta ao normal, simulando a resposta imunológica ou medicamentosa.
* **Ruído Natural:** Introduzimos flutuações e ruídos randômicos nos dados para imitar a imprecisão natural de sensores reais e a variabilidade imprevisível do corpo humano.
* **Eventos Críticos:** O sistema permite que os valores rompam a inércia e "escapem" do controle, simulando quadros de risco (como febre alta ou hipóxia), o que dispara imediatamente a lógica de alertas.

### 🏗️ Arquitetura e Engenharia de Software

### 1. SQL e SQLite (A Memória Permanente)
O que é: SQL (Structured Query Language) é a linguagem usada para conversar com bancos de dados. O SQLite é o "motor" que usamos: ele é um banco de dados leve que guarda tudo em um único arquivo (dados_hospital.db) dentro da pasta do projeto, sem precisar de servidor.

Quando e Por que usamos: No começo, o programa guardava os pacientes apenas na memória RAM (variáveis e vetores).

O Problema: Quando o programa fecha (ou se ele travasse), todos os dados sumiam.

A Solução: Usamos o SQL para Persistência de Dados.

INSERT: Para salvar o paciente no arquivo assim que ele é criado.
SELECT: Para ler o arquivo e recriar os pacientes na RAM quando o programa abre.
DELETE: Para remover do arquivo quando você deleta no menu.

### 2. Thread (std::thread) (O Multitarefa)
O que é: Uma Thread (fio de execução) permite que o seu programa faça duas coisas ao mesmo tempo.

Quando e Por que usamos: Para que a simulação rodasse continuamente, atualizando sensores e gerando alertas, enquanto o usuário utiliza o menu.

O Problema: O comando cin (que lê o teclado) trava o programa. O código para e fica esperando o usuário digitar. Se a simulação estivesse no mesmo fluxo (single-thread), os sensores parariam de funcionar até digitar algo.

A Solução: Criamos uma Segunda Thread (background).

Thread 1 (Principal/Main): Cuida do Menu, do cin e do cout.

Thread 2 (Simulação): Fica num loop infinito calculando batimentos e temperatura, dorme 2 segundos, e calcula de novo.

### 3. Mutex (std::mutex) (A Tranca de Segurança)
O que é: Mutex vem de Mutual Exclusion (Exclusão Mútua). É uma "trava" ou "chave" que protege uma variável compartilhada.

Quando e Por que usamos: Assim que adicionamos a Thread, criamos um perigo grave chamado Race Condition (Condição de Corrida).

O Problema (O Crash): Imagine que a Thread de Simulação está lendo o Paciente 1 para ver a temperatura. No exato mesmo milissegundo, você vai no Menu (Thread Principal) e deleta o Paciente 1.

A Simulação vai tentar ler uma memória que acabou de ser apagada.

Resultado: O programa fecha sozinho (Segmentation Fault/Crash).

A Solução: Usamos o Mutex (mtxHospital) para obrigar as threads a respeitarem a vez uma da outra.

Quando você vai deletar, você "tranca a porta" (lock).

Se a simulação tentar entrar para ler, ela vê a porta trancada e espera você terminar.

Assim que termina, "destranca" (unlock), e a simulação entra.

### 4. Atomic (std::atomic) (O Interruptor Rápido)
O que é: É uma variável especial que é "à prova de threads" para operações simples (como mudar de true para false), sem precisar de toda a burocracia pesada de um Mutex.

Quando e Por que usamos: Precisávamos de um jeito de dizer para a Thread da Simulação parar de rodar quando o programa fechar ou quando o usuário escolher "Parar Simulação".

O Problema: Se usássemos uma variável bool comum, poderia haver conflito de leitura/escrita entre as threads (uma tentando ler enquanto a outra muda o valor), embora menos grave que o caso do Mutex.

A Solução: Usamos std::atomic<bool> _ativo.

O Main diz: _ativo = false.

A Thread da Simulação lê while (_ativo) e percebe instantaneamente que mudou, encerrando o loop com segurança.

---

### 🔍 Visão Geral dos Sensores Virtuais

O sistema utiliza **Polimorfismo** para instanciar diferentes tipos de sensores que herdam de uma classe base, mas possuem comportamentos biofísicos distintos:

| Sensor Virtual | Unidade | Comportamento Simulado | Faixa Segura (Ref.) |
| :--- | :---: | :--- | :---: |
| **Oxímetro** 🅾 | `% SpO2` | Simula a saturação de oxigênio no sangue. Quedas bruscas acionam alerta de Hipóxia. | 95% - 100% |
| **Batimento Cardíaco** ❤️ | `BPM` | Monitora a frequência cardíaca. Variações rápidas indicam Taquicardia ou Bradicardia. | 60 - 120 BPM |
| **Termômetro** 🌡️ | `°C` | Acompanha a temperatura corporal com **inércia térmica** (mudanças lentas e graduais). | 35.0°C - 38.0°C |
| **Frequência Resp.** 🌬️ | `rpm` | Monitora ciclos de inspiração/expiração. Correlacionado com níveis de ansiedade simulada. | 12 - 24 rpm |
| **Pressão Arterial** 🩸 | `mmHg` | Sensor composto (Sistólica/Diastólica). Simula a tensão vascular e o débito cardíaco. | 60 - 110 mmHg |

---

## 📌 Funcionalidades Principais

| Funcionalidade | Descrição |
| :--- | :--- |
| **Gestão de Pacientes** 🧑‍⚕️ | Cadastro, busca e remoção de pacientes no banco de dados do hospital. |
| **Monitoramento por Sensores** 📊 | Cada paciente possui sensores virtuais individuais para leituras específicas. |
| **Simulação Dinâmica** 📈 | Atualização periódica (em tempo real) dos valores, simulando a fisiologia real. |
| **Alerta Crítico** 🚨 | Notificação automática quando um valor excede a faixa de segurança (`_min` a `_max`). |
| **Estrutura Modular** 🧩 | Uso de **Herança** e **Polimorfismo** (Classe base `Sensor`) para facilitar a escalabilidade. |

---

## 🛠️ Tecnologias Utilizadas

* **Linguagem:** C++ (Standard 11 ou superior recomendado)
* **Banco de Dados:** SQLite3
* **Conceitos:** Programação Orientada a Objetos (POO), Multithreading.

---

## 💻 Como Executar

Siga os passos abaixo para compilar e rodar o projeto em sua máquina.

### 1. Clonar ou Baixar o Repositório
Você pode baixar o arquivo `.zip` ou clonar via git:
```bash
git clone https://github.com/INF112-Programacao2/20252-team-2.git
cd 20252-team-2
````

### 2. Compilar e Rodar

#### Escolha seu sistema operacional abaixo e siga os comandos na ordem:

## Windows (MinGW/G++)
#### Compile o arquivo objeto do banco de dados (C):
```bash
PowerShell

gcc -c sqlite3.c -o sqlite3.o
```
#### Compile o sistema hospitalar (C++):
```bash
PowerShell

g++ *.cpp sqlite3.o -o hospital_app.exe
```
#### Execute o programa:
```bash
PowerShell

.\hospital_app.exe
```
## 🐧 Linux (GCC)
#### Compile o arquivo objeto do banco de dados (C):
```bash
Bash

gcc -c sqlite3.c -o sqlite3.o
```
#### Compile o sistema hospitalar (C++): Nota: As flags -pthread e -ldl são obrigatórias no Linux para threads e SQLite.
```bash
Bash

g++ *.cpp sqlite3.o -o hospital_app -pthread -ldl
```
#### ✳-pthread: Permite o uso de threads (para a simulação e para o próprio SQLite)
#### ✳-ldl: Significa "Link Dynamic Loader". O SQLite precisa disso no Linux para carregar extensões, mesmo que não use extensões
#### Execute o programa:
```bash
Bash

./hospital_app
```
