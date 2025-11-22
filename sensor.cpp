#include "sensor.h"
#include <iostream>

Sensor::Sensor(std::string tipo, double valor, std::string unidade, double min, double max)
    : _tipo(tipo), _valor(valor), _unidade(unidade), _min(min), _max(max), _dono(nullptr) {}

Sensor::~Sensor(){
}
    //Gets
double Sensor::get_valor()
{
    return _valor;
}
double Sensor::get_min()
{
    return _min;
}
double Sensor::get_max()
{
    return _max;
}

std::string Sensor::get_unidade()
{
    return _unidade;
}

std::string Sensor::get_tipo()
{
    return _tipo;
}

    //Sets
void Sensor::set_valor(double novoValor){
    _historico.push_back(_valor);
    _valor = novoValor;
}

void Sensor::set_tipo(std::string newTipo){
    _tipo = newTipo;
}

void Sensor::set_dono(Paciente *novodono){
    _dono = novodono;
}

    //Metodos


double Sensor::previsao(){ // Retorna uma media baseada nos cinco ultimos valores do paciente
    double soma =0;

    if(_historico.size() < 5){
        for(int i = 0; i < _historico.size(); i++){
            soma+=_historico[i];
        }
        soma += _valor;

        if(soma < _min){
            std::cout << "Alerta! Previsao de Estado de Emergencia! Tendencia de queda abaixo do limite segur no parametro: " << _tipo << std::endl;
        }
        else if(soma > _max){
            std::cout << "Alerta! Previsao de Estado de Emergencia! Tendencia de pico acima do limite seguro no parametro: " << _tipo << std::endl;
        }

        return soma / (_historico.size() + 1);
    }

    for(int i = 1; i < 5; i++){
        soma += *(_historico.end()-i);
    }
    soma += _valor;
    return soma / 5;
}

bool Sensor::alerta() const{
    return _valor < _min || _valor > _max;
}
void Sensor::exibirInfo() const
{
    std::cout << "Tipo: " << _tipo << " Valor: " << _valor << " Unidade: " << _unidade << std::endl;
}