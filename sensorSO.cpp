#include "sensorSO.h"
#include <iostream>

SensorOxigenio::SensorOxigenio() : Sensor("Fc", 100, "sPo2", 95, 100)
{
}

SensorOxigenio::~SensorOxigenio()
{
}
bool SensorOxigenio::alerta() const
{
    if (_valor < _min || _valor > _max)
        return true;
    return false;
}
void SensorOxigenio::exibirInfo() const
{
    std::cout << "Sensor Respiratorio:\n";
    std::cout << "Valor: " << _valor << " sPo2" << "\n";
    std::cout << "Faixa normal: " << _min << " - " << _max << " bpm\n";
    if (alerta())
        std::cout << "Alerta!!! Fora do intevalo esperado" << std::endl;
    else
        std::cout << "Situacao normal" << std::endl;
}
void SensorOxigenio::lerValor()
{
    std::cout << _valor << " sPo2" << std::endl;
}