#ifndef SENSOR_FC_H
#define SENSOR_FC_H
#include "sensor.h"

class SensorBatimento : public Sensor
{
private:
    double _max;
    double _min;

public:
    SensorBatimento();
    ~SensorBatimento();
    bool alerta() override;
    bool exibirInfo() override;
    void lerValor() override;
};
#endif