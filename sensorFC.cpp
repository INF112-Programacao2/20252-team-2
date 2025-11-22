#include "sensorFC.h"
#include <iostream>

SensorBatimento::SensorBatimento() : Sensor("Frequencia Cardiaca", 80, "bpm", 60, 120)
{
}

SensorBatimento::~SensorBatimento()
{
}
bool SensorBatimento::alerta() const
{
    if (_valor < _min || _valor > _max)
        return true;
    return false;
}
void SensorBatimento::exibirInfo() const
{
    std::cout << "Sensor de Batimentos Cardiacos:\n";
    std::cout << "Valor: " << _valor << " bpm" << "\n";
    std::cout << "Faixa normal: " << _min << " - " << _max << " bpm\n";
    if (alerta())
        std::cout << "Alerta!!! Fora do intevalo esperado" << std::endl;
    else
        std::cout << "Situacao normal" << std::endl;
}
void SensorBatimento::lerValor()
{
    std::cout << _valor << " bpm" << std::endl;
}