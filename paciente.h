#ifndef PACIENTE_H
#define PACIENTE_H
#include <iostream>
#include <vector>
#include <memory>
#include "sensor.h"
#include "sensorFC.h"
#include "sensorPA.h"
#include "sensorSO.h"
#include "sensorFR.h"
#include "sensorTC.h"

class Paciente
{
private:
    int _id;
    std::string _nome;
    int _idade;
    std::string _sexo;
    std::string _diagnostico;
    SensorPressao *_sensorPressao;
    SensorTemperatura *_sensorTemperatura;
    SensorOxigenio *_sensorOxigenio;
    SensorBatimento *_sensorBatimento;
    SensorRespiratorio *_sensorRespiratorio;

public:
    Paciente(); // Construtor padrao necessario para alocar vetor na classe hospital
    Paciente(int id, std::string nome, int idade, std::string sexo);
    ~Paciente();
    int get_id();
    std::string get_nome();
    int get_idade();
    std::string get_sexo();
    SensorPressao *get_sensorPressao();
    SensorTemperatura *get_sensorTemperatura();
    SensorOxigenio *get_sensorOxigenio();
    SensorBatimento *get_sensorBatimento();
    SensorRespiratorio *get_sensorRespiratorio();
};

#endif
