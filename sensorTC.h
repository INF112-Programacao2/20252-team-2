#ifndef SENSOR_TC_H
#define SENSOR_TC_H
#include "sensor.h"

class SensorTemperatura : public Sensor
{
private:
public:
    SensorTemperatura();
    ~SensorTemperatura();
    bool alerta() const override;
    void exibirInfo() const override;
    void lerValor() override;
};
#endif