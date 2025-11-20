#include "sensorFC.h"
#include <iostream>

SensorBatimento::SensorBatimento() : Sensor("Fc", 80, "bpm")
{
    _min = 60;
    _max = 120;
}

SensorBatimento::~SensorBatimento()
{
}
bool SensorBatimento::alerta()
{
    if (_valor < _min || _valor > _max)
        return true;
    return false;
}
bool SensorBatimento::exibirInfo()
{
    std::cout << "Sensor de Batimentos Cardiacos:\n";
    std::cout << "Valor: " << _valor << " bpm" << "\n";
    std::cout << "Faixa normal: " << _min << " - " << _max << " bpm\n";
    if (alerta)
        std::cout << "Alerta!!! Fora do intevalo esperado" << std::endl;
    else
        std::cout << "Situacao normal" << std::endl;

    return false;
}
void SensorBatimento::lerValor()
{
    std::cout << _valor << " bpm" << std::endl;
}