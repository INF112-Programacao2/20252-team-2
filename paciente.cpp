#include "paciente.h"
#include <iostream>

// Construtor padrao
Paciente::Paciente() : _id(0), _nome(""), _idade(0), _sexo(""),
                       _sensorPressao(nullptr), _sensorTemperatura(nullptr),
                       _sensorOxigenio(nullptr), _sensorBatimento(nullptr),
                       _sensorRespiratorio(nullptr)

{
}

// Construtor com parametros
Paciente::Paciente(int id, std::string nome, int idade, std::string sexo)
    : _id(id), _nome(nome), _idade(idade), _sexo(sexo)
{
    _sensorBatimento = new SensorBatimento;
    _sensorOxigenio = new SensorOxigenio;
    _sensorPressao = new SensorPressao;
    _sensorRespiratorio = new SensorRespiratorio;
    _sensorTemperatura = new SensorTemperatura;
}
// Destrutor
Paciente::~Paciente()
{
    delete _sensorBatimento;
    delete _sensorOxigenio;
    delete _sensorPressao;
    delete _sensorRespiratorio;
    delete _sensorTemperatura;
}

// Getters
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

// Estabiliza todos os sensores. Volta o valor para o meio exato entre min e max (Estado perfeito)
void Paciente::estabilizar()
{
    if (_sensorBatimento)
        _sensorBatimento->resetar();
    if (_sensorOxigenio)
        _sensorOxigenio->resetar();
    if (_sensorPressao)
        _sensorPressao->resetar();
    if (_sensorTemperatura)
        _sensorTemperatura->resetar();
    if (_sensorRespiratorio)
        _sensorRespiratorio->resetar();

    std::cout << "Paciente " << _nome << " foi estabilizado. Sinais vitais normalizados." << std::endl;
}