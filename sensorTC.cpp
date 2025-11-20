#include "sensorTC.h"
#include <iostream>

SensorTemperatura::SensorTemperatura() : Sensor("Fc", 36.5, "C", 35, 38)
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
    std::cout << "Sensor Respiratorio:\n";
    std::cout << "Valor: " << _valor << " C" << "\n";
    std::cout << "Faixa normal: " << _min << " - " << _max << " bpm\n";
    if (alerta())
        std::cout << "Alerta!!! Fora do intevalo esperado" << std::endl;
    else
        std::cout << "Situacao normal" << std::endl;
}
void SensorTemperatura::lerValor()
{
    std::cout << _valor << " C" << std::endl;
}