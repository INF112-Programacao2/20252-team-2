🏥 Sistema de Monitoramento Vital Integrado

O Contexto:
Este software simula um ambiente de gestão hospitalar focado no monitoramento intensivo de sinais vitais. O objetivo do sistema é gerenciar a internação de pacientes e acompanhar, em tempo real, a estabilidade fisiológica de cada indivíduo. Diferente de um cadastro estático, o sistema modela a dinamicidade do corpo humano, onde variáveis biológicas oscilam constantemente devido a fatores externos e internos.
O Funcionamento:

O núcleo da aplicação consiste em um Hospital com capacidade limitada de leitos, onde o usuário atua como administrador. Ao cadastrar um Paciente, o sistema automaticamente inicializa um conjunto de Sensores especializados (Batimento Cardíaco, Temperatura, Pressão Arterial, Oxigenação e Frequência Respiratória).

A grande inovação do código reside na lógica de Simulação. O sistema não apenas armazena dados, mas calcula variações contínuas nos sensores através de dois conceitos matemáticos implementados:

Ruído: Uma variação aleatória que simula a interferência do ambiente ou instabilidade momentânea.

Homeostase: Um mecanismo de correção automática que tenta trazer os valores de volta ao equilíbrio.

A cada ciclo de verificação, os sensores comparam os valores atuais com as faixas de segurança predefinidas (mínimo e máximo). Se a oscilação combinada do ruído superar a capacidade de homeostase e ultrapassar os limites críticos (como uma saturação de oxigênio abaixo de 95% ou temperatura acima de 38°C), o método alerta() é acionado, notificando imediatamente sobre o estado de emergência.
