#include "sensor.h"
#include <iostream>

Sensor::Sensor(std::string tipo, double valor, std::string unidade, double min, double max)
    : _tipo(tipo), _valor(valor), _unidade(unidade), _min(min), _max(max) {}

Sensor::~Sensor()
{
}
void Sensor::set_tipo()
{
}
double Sensor::get_valor()
{
    return _valor;
}
double Sensor::get_min()
{
    return _min;
}
double Sensor::get_max()
{
    return _max;
}

std::string Sensor::get_unidade()
{
    return _unidade;
}

std::string Sensor::get_tipo()
{
    return _tipo;
}

void Sensor::set_valor(double novoValor)
{
    _valor = novoValor;
}
bool Sensor::alerta() const
{
    return false;
}
void Sensor::exibirInfo() const
{
    std::cout << "Tipo: " << _tipo << " Valor: " << _valor << " Unidade: " << _unidade << std::endl;
}

void Sensor::resetar()
{
    // Volta o valor para o meio exato entre min e max (Estado perfeito)
    _valor = (_min + _max) / 2.0;
}