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

