#ifndef SENSOR_PA_H
#define SENSOR_PA_H
#include "sensor.h"

class SensorPressao : public Sensor{
private:
    double _max;
    double _min;
public:
    SensorPressao();
    ~SensorPressao();
    bool alerta() override;
    bool exibirInfo() override;
    void lerValor() override;
};
#endif