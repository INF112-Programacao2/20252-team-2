#include "simulador.h"
#include "hospital.h"
#include <iostream>
#include <cstdlib>
#include <chrono>

std::mutex mtxHospital;

// MUDANÇA: Agora retorna string. Se estiver tudo bem, retorna string vazia "".
std::string simular(Paciente *p, Sensor *sensor)
{
    double var = (sensor->get_max() - sensor->get_min()) / 10;
    double v = sensor->get_valor();
    double ruido = ((rand() % 100) / 100.0 - 0.5) * var;
    double normal = (sensor->get_min() + sensor->get_max()) / 2.0;
    double homeostase = (normal - v) * 0.05;

    sensor->set_valor(v + ruido + homeostase);

    if (sensor->alerta())
    {
        std::cout << std::endl;

        std::cout << "\033[31m"
                  << "====================  A L E R T A  ====================\n"
                  << "\033[0m";

        std::cout << "\033[31m"
                  << "+------------------------------------------------------+\n"
                  << "|                     ALERTA CRITICO                   |\n"
                  << "+------------------------------------------------------+\n"
                  << "\033[0m";

        std::cout << "  Paciente  : " << p->get_nome() << " Id:" << p->get_id() << "\n"
                  << "  Parametro: " << sensor->get_unidade() << "\n"
                  << "  Valor     : " << "\033[1;31m" << sensor->get_valor() << "\033[0m\n";

        std::cout << "\033[31m"
                  << "+======================================================+\n"
                  << "\033[0m\n";
    }
    return ""; // Sem alerta
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
        return;
    _ativo = true;
    _threadSimulacao = std::thread(&GerenciadorSimulacao::loop, this, h);
}

void GerenciadorSimulacao::parar()
{
    if (!_ativo)
        return;
    _ativo = false;
    if (_threadSimulacao.joinable())
        _threadSimulacao.join();
}

bool GerenciadorSimulacao::estaRodando() const { return _ativo; }

std::vector<std::string> GerenciadorSimulacao::pegarAlertas()
{
    std::lock_guard<std::mutex> lock(_mtxAlertas);
    std::vector<std::string> alertas = _bufferAlertas;
    _bufferAlertas.clear();
    return alertas;
}

void GerenciadorSimulacao::loop(Hospital *h)
{
    while (_ativo)
    {
        {
            std::lock_guard<std::mutex> lock(mtxHospital);
            if (h)
            {

                Paciente **lista = h->get_pacientes();
                int qtd = h->get_qtdPacientes();

                for (int i = 0; i < qtd; i++)
                {
                    Paciente *p = lista[i];
                    std::string msg;

                    if (p->get_sensorBatimento())
                    {
                        msg = simular(p, p->get_sensorBatimento());
                        if (!msg.empty())
                        {
                            std::lock_guard<std::mutex> lockAlertas(_mtxAlertas);
                            _bufferAlertas.push_back(msg);
                        }
                    }

                    if (p->get_sensorOxigenio())
                    {
                        msg = simular(p, p->get_sensorOxigenio());
                        if (!msg.empty())
                        {
                            std::lock_guard<std::mutex> lockAlertas(_mtxAlertas);
                            _bufferAlertas.push_back(msg);
                        }
                    }
                    // ... etc
                }
            }
        }
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}