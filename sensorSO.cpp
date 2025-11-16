#include "sensorSO.h"
#include <iostream>

    SensorOxigenio::SensorOxigenio() : Sensor("Fc", 100, "sPo2"){
        _min = 95; 
        _max = 100;
    }

    SensorOxigenio::~SensorOxigenio(){

    }
    bool SensorOxigenio::alerta(){
        if(_valor < _min || _valor > _max) 
            return true;
        return false;
    }
    bool SensorOxigenio::exibirInfo(){
            std::cout << "Sensor Respiratorio:\n";
            std::cout << "Valor: " << _valor << " sPo2" << "\n";
            std::cout << "Faixa normal: " << _min << " - " << _max << " bpm\n";
            if(alerta) std::cout << "Alerta!!! Fora do intevalo esperado" << std::endl;
            else std::cout << "Situacao normal" << std::endl;
            
            return false;
    }
    void SensorOxigenio::lerValor(){
        std::cout << _valor << " sPo2" << std::endl;
    }