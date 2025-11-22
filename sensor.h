#ifndef SENSOR_H
#define SENSOR_H
#include <iostream>
#include <vector>

class Sensor
{
protected:
    double _min;
    double _max;

    std::string _tipo;
    std::string _unidade;

    double _valor;
    std::vector<double> _historico;

public:
    Sensor(std::string tipo, double valor, std::string unidade, double min, double max);
    ~Sensor();

    double get_valor();
    double get_min();
    double get_max();
    std::string get_tipo();
    std::string get_unidade();

    void set_tipo(std::string newTipo);
    void set_valor(double novoValor);

    double previsao();

    virtual bool alerta() const;
    virtual void exibirInfo() const;
    virtual void lerValor() = 0;

};
#endif