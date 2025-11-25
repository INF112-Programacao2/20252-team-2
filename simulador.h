#ifndef SIMULADOR_H
#define SIMULADOR_H
#include "paciente.h"
#include "sensor.h"
#include <mutex>
#include <thread>
#include <atomic>

// Forward Declaration: Evita erro de include circular
class Hospital;

// Mutex global para sincronização
extern std::mutex mtxHospital;
void simular(Paciente *p, Sensor *sensor);

class GerenciadorSimulacao
{
private:
    std::atomic<bool> _ativo;
    std::thread _threadSimulacao;
    void loop(Hospital *h);

public:
    GerenciadorSimulacao();
    ~GerenciadorSimulacao();
    void iniciar(Hospital *h);
    void parar();
    bool estaRodando() const;
};

#endif