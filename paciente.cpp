#include "paciente.h"
#include <iostream>

Paciente::Paciente()
    : _sensorBatimento(nullptr),
      _sensorOxigenio(nullptr),
      _sensorPressao(nullptr),
      _sensorRespiratorio(nullptr),
      _sensorTemperatura(nullptr){ }

Paciente::Paciente(int id, std::string nome, int idade, std::string sexo)
    : _id(id), _nome(nome), _idade(idade), _sexo(sexo)
{
    _sensorBatimento = new SensorBatimento;
        _sensorBatimento->set_dono(this);

    _sensorOxigenio = new SensorOxigenio;
        _sensorOxigenio->set_dono(this);

    _sensorPressao = new SensorPressao;
        _sensorPressao->set_dono(this);

    _sensorRespiratorio = new SensorRespiratorio;
        _sensorRespiratorio->set_dono(this);
        
    _sensorTemperatura = new SensorTemperatura;
        _sensorTemperatura->set_dono(this);
}
Paciente::~Paciente()
{
    delete _sensorBatimento;
    delete _sensorOxigenio;
    delete _sensorPressao;
    delete _sensorRespiratorio;
    delete _sensorTemperatura;
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
