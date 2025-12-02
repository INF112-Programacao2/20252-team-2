#include "sensorTC.h"
#include <iostream>

// Construtor
SensorTemperatura::SensorTemperatura() : Sensor("Temperatura Corporal", 36.5, "C", 35, 38)
{
}

// Destrutor
SensorTemperatura::~SensorTemperatura()
{
}

// Sai o alerta critico
bool SensorTemperatura::alerta() const
{
    if (_valor < _min || _valor > _max)
        return true;
    return false;
}

// Exibe os valores do sensor
void SensorTemperatura::exibirInfo() const
{
    std::cout << "Sensor Temperatura Corporal:\n";
    std::cout << "Valor: " << _valor << " C" << "\n";
    std::cout << "Faixa normal: " << _min << " - " << _max << " C\n";
    if (alerta())
        std::cout << "Alerta!!! Fora do intevalo esperado" << std::endl;
    else
        std::cout << "Situacao normal" << std::endl;
}

// Recebe o valor do sensor
void SensorTemperatura::lerValor()
{
    std::cout << _valor << " C" << std::endl;
}