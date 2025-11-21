#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <string>
#include "hospital.h"
#include "paciente.h"
#include "sensor.h"
#include "sensorSO.h"
#include "sensorFC.h"
#include "sensorFR.h"
#include "sensorTC.h"
#include "sensorPA.h"
using namespace std;

int idPaciente = 0;
string nomepaciente;
int idadePaciente;
string sexoPaciente;
int idBusca;

#include <iostream>
#include <string>
using namespace std;

int lerID() {
    string entrada;
    int id;

    cout << "Digite o ID do paciente: ";
    cin >> entrada;

    try {
        id = stoi(entrada);        // tenta converter
    } catch (invalid_argument&) {
        throw runtime_error("Erro: o ID deve ser um numero.");}  

    return id;
}

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

    string nomeHospital;
    int capacidadeHospital;
    int vezes;
    int cont = 0;

    cout << "Crie um hospital(insira nome e capacidade): ";
    cin >> nomeHospital >> capacidadeHospital;
    Hospital *h = new Hospital(nomeHospital, capacidadeHospital);
    
    time_t b = time(NULL);

    while(true){

        int escolha;
        cout << "Escolha uma opcao:\n";
        cout << "Cadastrar novo paciente(1)\n";
        cout << "Deletar Paciente(2)\n";
        cout << "Buscar Paciente(3)\n";
        cout << "Rodar simulacao(4)\n";
        cin >> escolha;

        idPaciente++;

        switch (escolha)
        {
        case 1:{
            cout << "Digite: Nome, Idade, M/F: ";
            cin >> nomepaciente >> idadePaciente >> sexoPaciente;   
            Paciente *p = new Paciente(idPaciente, nomepaciente, idadePaciente, sexoPaciente);
            h->cadastrarPaciente(p);
            break;
        }
        case 2:{
            h->listarPacientes();
            cout << "Digite o ID do paciente a ser deletado: ";
            cin >> idBusca;
            h->removerPaciente(idBusca);
            break;
           
            
            

        }
            break;
        case 3:{
            try {
            int idBusca = lerID();
            Paciente* p = h->buscarPaciente(idBusca);

            if (p != nullptr) {
                cout << "Paciente encontrado: " << p->get_nome() << " | Idade: " << p->get_idade() << " | Sexo: " << p->get_sexo() << endl;
            } else {
                cout << "Paciente não encontrado.\n";
            }
        }
        catch (runtime_error &e) {
            cout << e.what() << endl;
        }
        break;
             
        }
            break;
        case 4:{
            cout << "Insira Numero de simulacoes desejadas: ";
            cin >> vezes;
            cont=0;
            while(cont < vezes){
                time_t a = time(NULL);
                if(a-b >= 0.1){
                b = a;
                simular(h->get_pacientes()[0], h->get_pacientes()[0]->get_sensorBatimento());
                cont++;
                }
            }
            break;
        }
        default:
            break;
        }
    }

    return 0;
}