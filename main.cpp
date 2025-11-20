#include <iostream>
#include <cstdlib>
#include <ctime>
#include "hospital.h"
#include "paciente.h"
#include "sensor.h"
#include "sensorSO.h"
#include "sensorFC.h"
#include "sensorFR.h"
#include "sensorTC.h"
#include "sensorPA.h"
using namespace std;

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
        cout << "Paciente: " << p->get_nome() << " Em estado de emergencia! Valor fora dos limites: " << sensor->get_valor() << sensor->get_unidade() << endl;
    }

    cout << "Teste: " << sensor->get_valor() << endl;
}

int main()
{
    srand(time(0));
    int cont = 0;

    string nomeHospital;
    int capacidadeHospital;

    cout << "Crie um hospital: (insira nome e capacidade): ";
    cin >> nomeHospital >> capacidadeHospital;
    Hospital *h = new Hospital(nomeHospital, capacidadeHospital);
    Paciente p("Tiago", 19, "Masculino");

    while (true)
    {
        string escolha;
        cout << "Escolha uma opcao:\n";
        cout << "Cadastrar novo paciente(1)\n";
        cout << "Deletar Paciente(2)\n";
        cout << "Buscar Paciente(3):\n";
        cin >> escolha;
    }

    return 0;
}