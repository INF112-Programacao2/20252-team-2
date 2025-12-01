#include "sensorTC.h"
#include <iostream>

SensorTemperatura::SensorTemperatura() : Sensor("Temperatura Corporal", 36.5, "C", 35, 38)
{
}

SensorTemperatura::~SensorTemperatura()
{
}
bool SensorTemperatura::alerta() const
{
    if (_valor < _min || _valor > _max)
        return true;
    return false;
}
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
void SensorTemperatura::lerValor()
{
    std::cout << _valor << " C" << std::endl;
}