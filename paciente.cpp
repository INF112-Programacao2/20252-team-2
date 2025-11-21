#include "paciente.h"
#include <iostream>

Paciente::Paciente() {}

Paciente::Paciente(int id, std::string nome, int idade, std::string sexo)
    : _id(id), _nome(nome), _idade(idade), _sexo(sexo)
{
    _sensorBatimento = new SensorBatimento;
}
Paciente::~Paciente()
{
}
int Paciente::get_id()
{
    return _id;
}
std::string Paciente::get_nome()
{
    return _nome;
}
int Paciente::get_idade()
{
    return _idade;
}
std::string Paciente::get_sexo()
{
    return _sexo;
}
SensorPressao *Paciente::get_sensorPressao()
{
    return _sensorPressao;
}
SensorTemperatura *Paciente::get_sensorTemperatura()
{
    return _sensorTemperatura;
}
SensorOxigenio *Paciente::get_sensorOxigenio()
{
    return _sensorOxigenio;
}
SensorBatimento *Paciente::get_sensorBatimento()
{
    return _sensorBatimento;
}
SensorRespiratorio *Paciente::get_sensorRespiratorio()
{
    return _sensorRespiratorio;
}
