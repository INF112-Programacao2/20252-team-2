#include "sensorFR.h"
#include <iostream>

SensorRespiratorio::SensorRespiratorio() : Sensor("Fc", 18, "rpm", 12, 24)
{
}

SensorRespiratorio::~SensorRespiratorio()
{
}
bool SensorRespiratorio::alerta() const
{
    if (_valor < _min || _valor > _max)
        return true;
    return false;
}
void SensorRespiratorio::exibirInfo() const
{
    std::cout << "Sensor Respiratorio:\n";
    std::cout << "Valor: " << _valor << " rpm" << "\n";
    std::cout << "Faixa normal: " << _min << " - " << _max << " bpm\n";
    if (alerta())
        std::cout << "Alerta!!! Fora do intevalo esperado" << std::endl;
    else
        std::cout << "Situacao normal" << std::endl;
}
void SensorRespiratorio::lerValor()
{
    std::cout << _valor << " rpm" << std::endl;
}