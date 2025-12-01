#include "hospital.h"
#include "paciente.h"
#include "simulador.h"
#include <iostream>
#include <stdexcept>

Hospital::Hospital(std::string nome, int capacidade)
    : _capacidade(capacidade), _nome(nome), _qtdPacientes(0) // <--- Troquei a ordem
{
    // ... resto do código igual ...
    _pacientes = new Paciente *[capacidade];
    for (int i = 0; i < capacidade; i++)
    {
        _pacientes[i] = nullptr;
    }
}

Hospital::~Hospital()
{
    for (int i = 0; i < _qtdPacientes; i++)
    {
        delete _pacientes[i];
    }
    delete[] _pacientes;
}

void Hospital::cadastrarPaciente(Paciente *p)
{

    if (_qtdPacientes >= _capacidade)
    {
        throw std::runtime_error("O hospital esta lotado! Nao e possivel aceitar novos pacientes.");
    }

    _pacientes[_qtdPacientes] = p;
    _qtdPacientes++;
}

void Hospital::removerPaciente(int idPaciente)
{
    for (int i = 0; i < _qtdPacientes; i++)
    {
        if (_pacientes[i]->get_id() == idPaciente)
        {
            delete _pacientes[i];

            for (int j = i; j < _qtdPacientes - 1; j++)
            {
                _pacientes[j] = _pacientes[j + 1];
            }
            _pacientes[_qtdPacientes - 1] = nullptr;
            _qtdPacientes--;

            std::cout << "Paciente de ID: " << idPaciente << " removido com sucesso!" << std::endl;
            return;
        }
    }

    throw std::runtime_error("Paciente nao encontrado no sistema.");
}

Paciente *Hospital::buscarPaciente(int idPaciente)
{
    for (int i = 0; i < _qtdPacientes; i++)
    {
        if (_pacientes[i]->get_id() == idPaciente)
        {
            return _pacientes[i];
        }
    }
    return nullptr;
}

std::string Hospital::get_nome()
{
    return _nome;
}

int Hospital::get_qtdPacientes()
{
    return _qtdPacientes;
}

Paciente **Hospital::get_pacientes()
{
    return _pacientes;
}

void Hospital::listarPacientes()
{
    if (_qtdPacientes == 0)
        std::cout << "Nenhum paciente internado no momento." << std::endl;

    for (int i = 0; i < _qtdPacientes; i++)
        std::cout << "ID: " << _pacientes[i]->get_id()
                  << " NOME: " << _pacientes[i]->get_nome()
                  << " IDADE: " << _pacientes[i]->get_idade()
                  << " SEXO: " << _pacientes[i]->get_sexo() << std::endl;
}

void Hospital::atualizarSensores()
{
    for (int i = 0; i < _qtdPacientes; i++)
    {
        Paciente *p = _pacientes[i];
        if (p->get_sensorPressao())
            simular(p, p->get_sensorPressao());
        if (p->get_sensorTemperatura())
            simular(p, p->get_sensorTemperatura());
        if (p->get_sensorOxigenio())
            simular(p, p->get_sensorOxigenio());
        if (p->get_sensorBatimento())
            simular(p, p->get_sensorBatimento());
        if (p->get_sensorRespiratorio())
            simular(p, p->get_sensorRespiratorio());
    }
}

bool Hospital::tratarPaciente(int id)
{
    Paciente *p = buscarPaciente(id);
    if (p != nullptr)
    {
        p->estabilizar();
        return true;
    }

    throw std::runtime_error("Paciente nao encontrado para tratamento.");
}