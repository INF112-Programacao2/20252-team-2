⚕️ Sistema de Monitoramento de Sinais Vitais Hospitalares

Este projeto visa simular e gerenciar o monitoramento contínuo de sinais vitais de pacientes em um ambiente hospitalar, utilizando uma arquitetura orientada a objetos em C++.

💡 Sobre o Projeto

O Sistema de Monitoramento Hospitalar permite o cadastro e a gestão de pacientes, associando a cada um um conjunto de sensores para leitura de dados vitais (Batimento, Temperatura, Oxigênio, etc.). O sistema simula a flutuação desses sinais e emite alertas de emergência quando os valores ultrapassam os limites de segurança pré-definidos. A simulação da variação dos sinais é feita através de cálculos que incluem ruído aleatório e uma tendência de retorno à homeostase.


📌 Funcionalidades Principais

Gestão de Pacientes 🧑‍⚕️: Cadastro, busca e remoção de pacientes no hospital.

Monitoramento por Sensores 📊: Cada paciente possui um conjunto de sensores virtuais para leituras específicas.

Simulação Dinâmica 📈: Atualização periódica dos valores dos sensores, simulando flutuações reais (baseado em ruído e homeostase).

Alerta Crítico 🚨: Notificação imediata quando um valor excede a faixa de segurança (_min a _max).

Estrutura Modular 🧩: Uso de herança (Sensor base) para facilitar a adição de novos tipos de sinais vitais.

💻Como Executar
 1. Baixe o arquivo.zip em https://github.com/INF112-Programacao2/20252-team-2.git

    Windows
 2. Compile o projeto
    <img width="1289" height="137" alt="image" src="https://github.com/user-attachments/assets/8a4c1bed-0426-4e4a-924d-ea6e6653fb1a" />

        gcc -c sqlite3.c -o sqlite3.o
    
    <img width="1283" height="121" alt="image" src="https://github.com/user-attachments/assets/20ec524b-8b7d-4030-b5b4-5a79cb1daea4" />

        g++ *.cpp sqlite3.o -o hospital_app.exe
    
    <img width="1278" height="138" alt="image" src="https://github.com/user-attachments/assets/42e472ef-3b0d-46f8-9b9b-ec348c6e9f3a" />

        .\hospital_app.exe

    Linux
 2. Compile o projeto
    <img width="1273" height="101" alt="image" src="https://github.com/user-attachments/assets/c5ef61a6-d751-449d-8e2f-ed3534415c5d" />   

        gcc -c sqlite3.c -o sqlite3.o
    
    <img width="1273" height="112" alt="image" src="https://github.com/user-attachments/assets/ede47394-4a1b-4203-b672-1654556aca0b" />

        g++ *.cpp sqlite3.o -o hospital_app -pthread -ldl
    
    ✳-pthread: Permite o uso de threads (para a simulação e para o próprio SQLite)
    
    ✳-ldl: Significa "Link Dynamic Loader". O SQLite precisa disso no Linux para carregar extensões, mesmo que não use extensões
    
    <img width="1279" height="124" alt="image" src="https://github.com/user-attachments/assets/c61da461-607e-4205-857d-c9cfac90d0f2" />

        ./hospital_app






