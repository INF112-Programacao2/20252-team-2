#ifndef SENSOR_SO_H
#define SENSOR_SO_H
#include "sensor.h"

class SensorOxigenio : public Sensor
{
private:
public:
    SensorOxigenio();
    ~SensorOxigenio();
    bool alerta() const override;
    void exibirInfo() const override;
    void lerValor() override;
};
#endif