#ifndef SENSOR_FC_H
#define SENSOR_FC_H
#include "sensor.h"

class SensorBatimento : public Sensor
{
private:
public:
    SensorBatimento();
    ~SensorBatimento();
    bool alerta() const override;
    void exibirInfo() const override;
    void lerValor() override;
};
#endif