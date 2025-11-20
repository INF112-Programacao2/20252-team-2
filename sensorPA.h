#ifndef SENSOR_PA_H
#define SENSOR_PA_H
#include "sensor.h"

class SensorPressao : public Sensor
{
private:
public:
    SensorPressao();
    ~SensorPressao();
    bool alerta() const override;
    void exibirInfo() const override;
    void lerValor() override;
};
#endif