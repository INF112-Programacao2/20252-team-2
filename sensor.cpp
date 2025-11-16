 #include "sensor.h"
 #include <iostream>

    Sensor::Sensor(std::string tipo, double valor, std::string unidade)
    :_tipo(tipo), _valor(valor), _unidade(unidade){}

    Sensor::~Sensor(){

    }
    void Sensor::set_tipo(){

    }
    double Sensor::get_valor(){
        return _valor;
    }
    void Sensor::set_valor(int novoValor){
        _valor = novoValor;
    }
    bool Sensor::alerta(){
        return false;
    }   
    bool Sensor::exibirInfo(){
        std::cout << "Tipo: " << _tipo << " Valor: " << _valor << " Unidade: " <<   _unidade << std::endl;
        return true;
    }