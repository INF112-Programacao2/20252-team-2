#include "sensorSO.h"
#include <iostream>
// construtor
SensorOxigenio::SensorOxigenio() : Sensor("Saturacao de Oxigenio", 97.5, "sPo2", 95, 100)
{
}
// destrutor
SensorOxigenio::~SensorOxigenio()
{
}
// alerta de emergencia
bool SensorOxigenio::alerta() const
{
    if (_valor < _min)
        return true;
    return false;
}
// exibe valores
void SensorOxigenio::exibirInfo() const
{
    std::cout << "Sensor Saturacao de Oxigenio:\n";
    std::cout << "Valor: " << _valor << " sPo2" << "\n";
    std::cout << "Faixa normal: " << _min << " - " << _max << " sPo2\n";
    if (alerta())
        std::cout << "Alerta!!! Fora do intevalo esperado" << std::endl;
    else
        std::cout << "Situacao normal" << std::endl;
}
// retornar o valor para ver o valor de um paciente
void SensorOxigenio::lerValor()
{
    std::cout << _valor << " sPo2" << std::endl;
}