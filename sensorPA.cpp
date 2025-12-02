#include "sensorPA.h"
#include <iostream>
//construtor
SensorPressao::SensorPressao() : Sensor("Pressao Arterial", 85, "mmHg", 60, 110)
{
}
//destrutor
SensorPressao::~SensorPressao()
{
}
// alerta sobre emergencia
bool SensorPressao::alerta() const
{
    if (_valor < _min || _valor > _max)
        return true;
    return false;
}
// exibir informações sobre o sensor
void SensorPressao::exibirInfo() const
{
    std::cout << "Sensor Pressao Arterial:\n";
    std::cout << "Valor: " << _valor << " mmHG" << "\n";
    std::cout << "Faixa normal: " << _min << " - " << _max << " mmHg\n";
    if (alerta())
        std::cout << "Alerta!!! Fora do intevalo esperado" << std::endl;
    else
        std::cout << "Situacao normal" << std::endl;
}
// retornar o valor para ver o valor de um paciente
void SensorPressao::lerValor()
{
    std::cout << _valor << " mmHG" << std::endl;
}