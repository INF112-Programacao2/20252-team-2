#include "sensorFR.h"
#include <iostream>

SensorRespiratorio::SensorRespiratorio() : Sensor("Fc", 18, "rpm")
{
    _min = 12;
    _max = 24;
}

SensorRespiratorio::~SensorRespiratorio()
{
}
bool SensorRespiratorio::alerta()
{
    if (_valor < _min || _valor > _max)
        return true;
    return false;
}
bool SensorRespiratorio::exibirInfo()
{
    std::cout << "Sensor Respiratorio:\n";
    std::cout << "Valor: " << _valor << " rpm" << "\n";
    std::cout << "Faixa normal: " << _min << " - " << _max << " bpm\n";
    if (alerta)
        std::cout << "Alerta!!! Fora do intevalo esperado" << std::endl;
    else
        std::cout << "Situacao normal" << std::endl;

    return false;
}
void SensorRespiratorio::lerValor()
{
    std::cout << _valor << " rpm" << std::endl;
}