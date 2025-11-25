#include "hospital.h"
#include "paciente.h"
#include "simulador.h" // Necessário para chamar a função simular()
#include <iostream>

Hospital::Hospital(std::string nome, int capacidade)
    : _nome(nome), _capacidade(capacidade), _qtdPacientes(0)
{
    // Aloca um array de PONTEIROS
    _pacientes = new Paciente *[capacidade];

    // Inicializa com nulo para segurança
    for (int i = 0; i < capacidade; i++)
    {
        _pacientes[i] = nullptr;
    }
}

Hospital::~Hospital()
{
    // 1. Deleta os pacientes reais da memória
    for (int i = 0; i < _qtdPacientes; i++)
    {
        delete _pacientes[i];
    }
    // 2. Deleta o array que segurava eles
    delete[] _pacientes;
}

void Hospital::cadastrarPaciente(Paciente *p)
{
    if (_qtdPacientes < _capacidade)
    {
        // O Hospital guarda o endereço original (assume a posse)
        _pacientes[_qtdPacientes] = p;
        _qtdPacientes++;
    }
    else
        std::cout << "O hospital esta lotado!" << std::endl;
}

void Hospital::removerPaciente(int idPaciente)
{
    for (int i = 0; i < _qtdPacientes; i++)
    {
        // Usa seta -> pois é ponteiro
        if (_pacientes[i]->get_id() == idPaciente)
        {
            // Deleta o paciente da memória RAM
            delete _pacientes[i];

            // Reorganiza o vetor para tampar o buraco
            for (int j = i; j < _qtdPacientes - 1; j++)
            {
                _pacientes[j] = _pacientes[j + 1];
            }
            _pacientes[_qtdPacientes - 1] = nullptr; // Zera o último
            _qtdPacientes--;

            std::cout << "Paciente de ID: " << idPaciente << " removido com sucesso!" << std::endl;
            return;
        }
    }
    std::cout << "Paciente nao encontrado!" << std::endl;
}

Paciente *Hospital::buscarPaciente(int idPaciente)
{
    for (int i = 0; i < _qtdPacientes; i++)
    {
        if (_pacientes[i]->get_id() == idPaciente)
        {
            return _pacientes[i]; // Retorna o ponteiro original
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
        Paciente *p = _pacientes[i]; // Acessa via ponteiro

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
    return false;
}