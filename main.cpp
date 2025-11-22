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
#include "simulador.h"
using namespace std;

int idPaciente = 0;
string nomepaciente;
int idadePaciente;
string sexoPaciente;
int idBusca;

#include <iostream>
#include <string>
using namespace std;

int lerID()
{
    string entrada;
    int id;

    cout << "Digite o ID do paciente: ";
    cin >> entrada;

    try
    {
        id = stoi(entrada); // tenta converter
    }
    catch (invalid_argument &)
    {
        throw runtime_error("Erro: o ID deve ser um numero.");
    }

    return id;
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

    while (true)
    {

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
        case 1:
        {
            cout << "Digite: Nome, Idade, M/F: ";
            cin >> nomepaciente >> idadePaciente >> sexoPaciente;
            Paciente *p = new Paciente(idPaciente, nomepaciente, idadePaciente, sexoPaciente);
            h->cadastrarPaciente(p);
            break;
        }
        case 2:
        {
            h->listarPacientes();
            try
            {
                int idBusca = lerID();
                Paciente *p = h->buscarPaciente(idBusca);

                if (p != nullptr)
                {
                    cout << "Paciente encontrado: " << p->get_nome() << " | Idade: " << p->get_idade() << " | Sexo: " << p->get_sexo() << endl;

                    while (true)
                    {
                        try
                        {
                            char x;
                            cout << "Deseja remover esse paciente? (S/N)" << endl;
                            cin >> x;

                            if (x == 'S')
                            {
                                h->removerPaciente(idBusca);
                                break;
                            }
                            else if (x == 'N')
                            {
                                break;
                            }
                            else
                            {
                                throw invalid_argument("Entrada invalida! Digite apenas S ou N.");
                            }
                        }
                        catch (invalid_argument &e)
                        {
                            cout << e.what() << endl;
                        }
                    }
                }
                else
                {
                    cout << "Paciente nao encontrado.\n";
                }
            }
            catch (runtime_error &e)
            {
                cout << e.what() << endl;
            }

            break;
        }

        case 3:
        {
            try
            {
                int idBusca = lerID();
                Paciente *p = h->buscarPaciente(idBusca);

                if (p != nullptr)
                {
                    cout << "Paciente encontrado: " << p->get_nome() << " | Idade: " << p->get_idade() << " | Sexo: " << p->get_sexo() << endl;
                }
                else
                {
                    cout << "Paciente nao encontrado.\n";
                }
            }
            catch (runtime_error &e)
            {
                cout << e.what() << endl;
            }
            break;
        }
        break;
        case 4:
        {
            cout << "Insira Numero de simulacoes desejadas: ";
            cin >> vezes;
            cont = 0;
            while (cont < vezes)
            {
                time_t a = time(NULL);
                if (a - b >= 0.1)
                {
                    b = a;
                    h->atualizarSensores();
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
