#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <string>
#include <vector>
#include "hospital.h"
#include "paciente.h"
#include<stdexcept>
using namespace std;

// Variaveis globais auxiliares
int idPaciente = 0;
string nomepaciente;
int idadePaciente;
string sexoPaciente;

int lerID()
{
    string entrada;
    int id;
    cout << "Digite o ID do paciente: ";
    cin >> entrada;
    try
    {
        id = stoi(entrada);
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
    Hospital *h = nullptr;

    cout << "--- SISTEMA HOSPITALAR ---" << endl;

    // 3. Se não carregou nenhum, cria novo
    if (h == nullptr)
    {
        cout << "Crie um hospital (insira nome e capacidade): ";
        cin >> nomeHospital >> capacidadeHospital;
        h = new Hospital(nomeHospital, capacidadeHospital);
    }

    time_t b = time(NULL);

    while (true)
    {
        int escolha;
        cout << "\nHospital: " << h->get_nome() << endl;
        cout << "Escolha uma opcao:\n";
        cout << "Cadastrar novo paciente(1)\n";
        cout << "Deletar Paciente(2)\n";
        cout << "Buscar Paciente(3)\n";
        cout << "Rodar simulacao(4)\n";
        cout << "Sair(0)\n";
        cin >> escolha;

        switch (escolha)
        {
        case 1:
        {
            idPaciente++; // Incrementa ID
            cout << "Digite: Nome, Idade, M/F: ";
            cin >> nomepaciente >> idadePaciente >> sexoPaciente;
            Paciente *p = new Paciente(idPaciente, nomepaciente, idadePaciente, sexoPaciente);

            // Adiciona na memória
            h->cadastrarPaciente(p);

            delete p; // O hospital faz cópia, podemos deletar esse
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
                    cout << "Paciente encontrado: " << p->get_nome() << endl;
                    char x;
                    cout << "Deseja remover esse paciente? (S/N): ";
                    cin >> x;
                    if (x == 'S' || x == 's')
                    {
                        // Remove da memória
                        h->removerPaciente(idBusca);
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
        case 4:
        {
            try
            {
                int vezes;
                cout << "Insira Numero de simulacoes: ";
                cin >> vezes;

                if (!cin)
                    throw runtime_error("Numero invalido!");

                int cont = 0;
                while (cont < vezes)
                {
                    time_t a = time(NULL);
                    if (difftime(a, b) >= 0.1)
                    {
                        b = a;
                        h->atualizarSensores();
                        cont++;
                    }
                    
                    break;
                }
            }
            catch (exception &e)
            {
                cout << "Erro: " << e.what() << endl;
            }
            break;
        }
        case 0:
            delete h;
            return 0;
        default:
            cout << "Opcao invalida" << endl;
            break;
        }
    }

    return 0;
}