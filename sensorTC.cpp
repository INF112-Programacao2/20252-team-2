#include "sensorTC.h"
#include <iostream>

    SensorTemperatura::SensorTemperatura() : Sensor("Fc", 36.5, "C"){
        _min = 35; 
        _max = 37,5;
    }

    SensorTemperatura::~SensorTemperatura(){

    }
    bool SensorTemperatura::alerta(){
        if(_valor < _min || _valor > _max) 
            return true;
        return false;
    }
    bool SensorTemperatura::exibirInfo(){
            std::cout << "Sensor Respiratorio:\n";
            std::cout << "Valor: " << _valor << " C" << "\n";
            std::cout << "Faixa normal: " << _min << " - " << _max << " bpm\n";
            if(alerta) std::cout << "Alerta!!! Fora do intevalo esperado" << std::endl;
            else std::cout << "Situacao normal" << std::endl;
            
            return false;
    }
    void SensorTemperatura::lerValor(){
        std::cout << _valor << " C" << std::endl;
    }