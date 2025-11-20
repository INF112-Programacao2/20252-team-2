#ifndef SENSOR_H
#define SENSOR_H
#include <iostream>

class Sensor
{
protected:
    std::string _tipo;
    double _valor;
    std::string _unidade;

public:
    Sensor(std::string tipo, double valor, std::string unidade);
    ~Sensor();
    void set_tipo();
    double get_valor();
    void set_valor(int novoValor);
    virtual bool alerta();
    virtual bool exibirInfo();
    virtual void lerValor() = 0;
};
#endif