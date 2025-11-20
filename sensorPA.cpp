#include "sensorPA.h"
#include <iostream>

SensorPressao::SensorPressao() : Sensor("Fc", 85, "mmHg")
{
    _min = 60;
    _max = 110;
}

SensorPressao::~SensorPressao()
{
}
bool SensorPressao::alerta()
{
    if (_valor < _min || _valor > _max)
        return true;
    return false;
}
bool SensorPressao::exibirInfo()
{
    std::cout << "Sensor Respiratorio:\n";
    std::cout << "Valor: " << _valor << " mmHG" << "\n";
    std::cout << "Faixa normal: " << _min << " - " << _max << " bpm\n";
    if (alerta)
        std::cout << "Alerta!!! Fora do intevalo esperado" << std::endl;
    else
        std::cout << "Situacao normal" << std::endl;

    return false;
}
void SensorPressao::lerValor()
{
    std::cout << _valor << " mmHG" << std::endl;
}