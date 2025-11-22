#include "simulador.h"
#include <iostream>
#include <cstdlib>

void simular(Paciente *p, Sensor *sensor)
{
    double var = (sensor->get_max() - sensor->get_min()) / 10;
    double v = sensor->get_valor();

    double ruido = ((rand() % 100) / 100.0 - 0.5) * var;

    double normal = (sensor->get_min() + sensor->get_max()) / 2.0;
    double homeostase = (normal - v) * 0.05;

    sensor->set_valor(v + ruido + homeostase);

    if (sensor->alerta())
    {
        std::cout << "Paciente: " << p->get_nome()
                  << " Em estado de emergencia! Valor fora dos limites: "
                  << sensor->get_valor() << sensor->get_unidade() << std::endl;
    }

    std::cout << "Teste: " << sensor->get_valor() << std::endl;
}