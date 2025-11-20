#ifndef SENSOR_FR_H
#define SENSOR_FR_H
#include "sensor.h"

class SensorRespiratorio : public Sensor
{
private:
public:
    SensorRespiratorio();
    ~SensorRespiratorio();
    bool alerta() const override;
    void exibirInfo() const override;
    void lerValor() override;
};
#endif