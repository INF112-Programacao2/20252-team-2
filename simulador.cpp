#include "simulador.h"
#include "hospital.h"
#include <iostream>
#include <cstdlib>
#include <chrono>

std::mutex mtxHospital;

#include <sstream>

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
        std::stringstream ss;

        ss << "\033[31m" << "(!) ALERTA CRITICO: " << "\033[0m"
           << "Paciente " << p->get_nome() << " (ID: " << p->get_id() << ") - "
           << sensor->get_tipo() << ": "
           << "\033[1;31m" << sensor->get_valor() << " " << sensor->get_unidade() << "\033[0m";

        return ss.str();
    }
    return "";
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