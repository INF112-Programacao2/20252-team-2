#include "hospital.h"
#include "paciente.h"
#include <iostream>

Hospital::Hospital(std::string nome, int capacidade)
    : _nome(nome), _capacidade(capacidade), _qtdPacientes(0)
{
    _pacientes = new Paciente[capacidade];
}
Hospital::~Hospital()
{
    delete[] _pacientes;
}
void Hospital::cadastrarPaciente(Paciente *p)
{
    if (_qtdPacientes < _capacidade)
    {
        _pacientes[_qtdPacientes] = *p;
        _qtdPacientes++;
    }
    else
        std::cout << "O hospital esta lotado!" << std::endl;
}
void Hospital::removerPaciente(int idPaciente)
{
    for (int i = 0; i < _qtdPacientes; i++)
    {
        if (_pacientes[i].get_id() == idPaciente)
        {
            for (int j = i; j < _qtdPacientes - 1; j++)
            { // Deleta o paciente escolhido e realoca o vetor para nao perder espaco
                _pacientes[j] = _pacientes[j + 1];
            }
            _qtdPacientes--;
            std::cout << "Paciente de ID: " << idPaciente << " removido com sucesso!" << std::endl;
            return;
        }
    }
    std::cout << "Paciente não encontrado!" << std::endl;
}
Paciente *Hospital::buscarPaciente(int idPaciente)
{
    for (int i = 0; i < _qtdPacientes; i++)
    {
        if (_pacientes[i].get_id() == idPaciente)
        {
            return &_pacientes[i];
        }
    }
    return nullptr; // se nao encontrar
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
    return &_pacientes;
}

void Hospital::listarPacientes()
{
    for (int i = 0; i < _qtdPacientes; i++)
        std::cout << "ID: " << _pacientes[i].get_id() << " NOME: " << _pacientes[i].get_nome() << " IDADE: " << _pacientes[i].get_idade() << " SEXO: " << _pacientes[i].get_sexo() << std::endl;
}

void Hospital::atualizarSensores()
{
    for (int i = 0; i < _qtdPacientes; i++)
    {
        Paciente *p = &_pacientes[i]; // paciente atual

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