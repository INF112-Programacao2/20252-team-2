#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <string>
#include <vector>
#include "hospital.h"
#include "paciente.h"
#include "database.h"
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

    // Inicializar Banco de Dados
    GerenciadorBD db;
    db.inicializar();
    idPaciente = db.getUltimoIdPaciente();
    // --------------------------------

    string nomeHospital;
    int capacidadeHospital;
    Hospital *h = nullptr;

    cout << "--- SISTEMA HOSPITALAR ---" << endl;

    while (h == nullptr)
    { // Loop até o usuário escolher ou criar um hospital
        vector<pair<string, int>> hospitaisSalvos = db.listarHospitais();

        if (!hospitaisSalvos.empty())
        {
            cout << "\n--- Hospitais Disponiveis ---" << endl;
            for (size_t i = 0; i < hospitaisSalvos.size(); i++)
            {
                cout << i + 1 << ". " << hospitaisSalvos[i].first
                     << " (Capacidade: " << hospitaisSalvos[i].second << ")" << endl;
            }
            cout << "-----------------------------" << endl;
            cout << "[0] Criar NOVO hospital" << endl;
            cout << "[-1] DELETAR um hospital" << endl;

            int opcao;
            cout << "Escolha: ";
            cin >> opcao;

            if (opcao == 0)
            {
                break;
            }
            else if (opcao == -1)
            {
                cout << "Digite o numero do hospital para deletar: ";
                int del;
                cin >> del;
                if (del > 0 && del <= (int)hospitaisSalvos.size())
                {
                    string nomeParaDeletar = hospitaisSalvos[del - 1].first;

                    cout << "Tem certeza que deseja apagar " << nomeParaDeletar << " e todos os seus pacientes? (S/N): ";
                    char confirm;
                    cin >> confirm;
                    if (confirm == 'S' || confirm == 's')
                    {
                        db.removerHospital(nomeParaDeletar);
                    }
                }
                else
                {
                    cout << "Opcao invalida!" << endl;
                }
                // O loop roda de novo para atualizar a lista
            }
            else if (opcao > 0 && opcao <= (int)hospitaisSalvos.size())
            {
                // Carregar Existente
                nomeHospital = hospitaisSalvos[opcao - 1].first;
                capacidadeHospital = hospitaisSalvos[opcao - 1].second;
                h = new Hospital(nomeHospital, capacidadeHospital);
                db.carregarPacientesParaHospital(h);

                // Atualiza ID para não dar conflito
                int ultimoId = db.getUltimoIdPaciente();
                if (ultimoId > idPaciente)
                    idPaciente = ultimoId;

                cout << "Hospital carregado com sucesso!" << endl;
            }
            else
            {
                cout << "Opcao invalida." << endl;
            }
        }
        else
        {
            break; // Se não tem hospitais, sai para criar um
        }
    }

    // Se não carregou nenhum, cria novo
    if (h == nullptr)
    {
        cout << "Crie um hospital (insira nome e capacidade): ";
        cin >> nomeHospital >> capacidadeHospital;
        h = new Hospital(nomeHospital, capacidadeHospital);
        // Salva o novo hospital no banco
        db.salvarHospital(nomeHospital, capacidadeHospital);
    }

    time_t b = time(NULL);

    while (true)
    {
        string nomeHospital;
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

            // Adiciona no Banco de Dados
            db.salvarPaciente(idPaciente, nomepaciente, idadePaciente, sexoPaciente, h->get_nome());

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
                        // Remove do Banco de Dados
                        db.removerPaciente(idBusca);
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
                h->listarPacientes();
                int idBusca = lerID();
                Paciente *p = h->buscarPaciente(idBusca);
                if (p != nullptr)
                {
                    cout << "Paciente encontrado: " << p->get_nome() << " | Idade: " << p->get_idade() << " | Sexo: " << p->get_sexo() << endl;
                    h->atualizarSensores();
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

            int vezes;
            int cont = 0;
            cout << "Insira Numero de simulacoes desejadas: ";
            cin >> vezes;
            while (cont < vezes)
            {
                time_t a = time(NULL);
                if (a - b >= 1)
                {
                    b = a;
                    h->atualizarSensores();
                    cont++;
                }

                break;
            }
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