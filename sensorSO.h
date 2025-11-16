#ifndef SENSOR_SO_H
#define SENSOR_SO_H
#include "sensor.h"

class SensorOxigenio : public Sensor{
private:
    double _min;
    double _max;
public:
    SensorOxigenio();
    ~SensorOxigenio();
    bool alerta() override;
    bool exibirInfo() override;
    void lerValor() override;
};
#endif