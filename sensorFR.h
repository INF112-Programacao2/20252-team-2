#ifndef SENSOR_FR_H
#define SENSOR_FR_H
#include "sensor.h"

class SensorRespiratorio : public Sensor{
private:
    double _max;
    double _min;
public:
    SensorRespiratorio();
    ~SensorRespiratorio();
    bool alerta() override;
    bool exibirInfo() override;
    void lerValor() override;
};
#endif