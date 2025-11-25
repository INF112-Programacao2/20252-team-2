#ifndef SIMULADOR_H
#define SIMULADOR_H
#include "paciente.h"
#include "sensor.h"
#include <mutex>
#include <thread>
#include <atomic>
#include <vector>
#include <string>

// Forward Declaration
class Hospital;

extern std::mutex mtxHospital;

std::string simular(Paciente *p, Sensor *sensor);

class GerenciadorSimulacao
{
private:
    std::atomic<bool> _ativo;
    std::thread _threadSimulacao;

    std::vector<std::string> _bufferAlertas;
    std::mutex _mtxAlertas;

    void loop(Hospital *h);

public:
    GerenciadorSimulacao();
    ~GerenciadorSimulacao();

    void iniciar(Hospital *h);
    void parar();
    bool estaRodando() const;

    std::vector<std::string> pegarAlertas();
};

#endif