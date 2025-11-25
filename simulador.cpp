#include "simulador.h"
#include "hospital.h" // AQUI podemos incluir o hospital.h sem erro
#include <iostream>
#include <cstdlib>
#include <chrono>

std::mutex mtxHospital; // Definição real do Mutex

void simular(Paciente *p, Sensor *sensor)
{
    double var = (sensor->get_max() - sensor->get_min()) / 10;
    double v = sensor->get_valor();
    double ruido = ((rand() % 100) / 100.0 - 0.5) * var;
    double normal = (sensor->get_min() + sensor->get_max()) / 2.0;
    double homeostase = (normal - v) * 0.05;

    sensor->set_valor(v + ruido + homeostase);

    if (sensor->alerta())
    {
        // Alerta Visual em Vermelho
        std::cout << "\n\033[1;31m[ALERTA]\033[0m Paciente: " << p->get_nome()
                  << " | " << sensor->get_unidade() << ": " << sensor->get_valor() << std::endl;
    }
}

// --- Gerenciador ---
GerenciadorSimulacao::GerenciadorSimulacao() : _ativo(false) {}

GerenciadorSimulacao::~GerenciadorSimulacao()
{
    parar();
}

void GerenciadorSimulacao::iniciar(Hospital *h)
{
    if (_ativo)
        return;
    if (!h)
    {
        std::cout << "Erro: Hospital nulo." << std::endl;
        return;
    }

    _ativo = true;
    _threadSimulacao = std::thread(&GerenciadorSimulacao::loop, this, h);
    std::cout << ">>> Simulacao iniciada (2o plano) <<<" << std::endl;
}

void GerenciadorSimulacao::parar()
{
    if (!_ativo)
        return;
    _ativo = false;
    if (_threadSimulacao.joinable())
        _threadSimulacao.join();
    std::cout << ">>> Simulacao parada <<<" << std::endl;
}

bool GerenciadorSimulacao::estaRodando() const { return _ativo; }

void GerenciadorSimulacao::loop(Hospital *h)
{
    while (_ativo)
    {
        {
            std::lock_guard<std::mutex> lock(mtxHospital); // Bloqueia acesso
            if (h)
                h->atualizarSensores();
        }
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}