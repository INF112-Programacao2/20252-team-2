#ifndef SENSOR_H
#define SENSOR_H
#include <iostream>

class Sensor
{
protected:
    std::string _tipo;
    double _valor;
    std::string _unidade;
    double _min;
    double _max;

public:
    Sensor(std::string tipo, double valor, std::string unidade, double min, double max);
    ~Sensor();
    double get_valor();
    double get_min();
    double get_max();
    std::string get_tipo();
    std::string get_unidade();
    void set_tipo();
    void set_valor(double novoValor);
    virtual bool alerta() const;
    virtual void exibirInfo() const;
    virtual void lerValor() = 0;
};
#endif