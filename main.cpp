#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <string>
#include <vector>
#include <mutex> 
#include "hospital.h"
#include "paciente.h"
#include "database.h"
#include "simulador.h" 

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

    // Inicializar Gerenciador de Threads (Simulação em 2º Plano)
    GerenciadorSimulacao sim;

    string nomeHospital;
    int capacidadeHospital;
    Hospital *h = nullptr;

    cout << "--- SISTEMA HOSPITALAR ---" << endl;

    // --- BLOCO DE LOGIN/CARREGAMENTO ---
    while (h == nullptr)
    {
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
                break;
            else if (opcao == -1)
            {
                cout << "Digite o numero do hospital para deletar: ";
                int del;
                cin >> del;
                if (del > 0 && del <= (int)hospitaisSalvos.size())
                {
                    string nomeParaDeletar = hospitaisSalvos[del - 1].first;
                    cout << "Tem certeza? (S/N): ";
                    char confirm;
                    cin >> confirm;
                    if (confirm == 'S' || confirm == 's')
                        db.removerHospital(nomeParaDeletar);
                }
                else
                    cout << "Opcao invalida!" << endl;
            }
            else if (opcao > 0 && opcao <= (int)hospitaisSalvos.size())
            {
                nomeHospital = hospitaisSalvos[opcao - 1].first;
                capacidadeHospital = hospitaisSalvos[opcao - 1].second;
                h = new Hospital(nomeHospital, capacidadeHospital);
                db.carregarPacientesParaHospital(h);

                int ultimoId = db.getUltimoIdPaciente();
                if (ultimoId > idPaciente)
                    idPaciente = ultimoId;
                cout << "Hospital carregado com sucesso!" << endl;
            }
            else
                cout << "Opcao invalida." << endl;
        }
        else
            break;
    }

    if (h == nullptr)
    {
        cout << "Crie um hospital (insira nome e capacidade): ";
        cin >> nomeHospital >> capacidadeHospital;
        h = new Hospital(nomeHospital, capacidadeHospital);
        db.salvarHospital(nomeHospital, capacidadeHospital);
    }
    // -----------------------------------

    while (true)
    {
        // --- NOVO BLOCO: RECUPERA E IMPRIME ALERTAS ---
        if (sim.estaRodando())
        {
            vector<string> alertas = sim.pegarAlertas(); // Pega da caixa de correio
            if (!alertas.empty())
            {
                cout << "\n\033[1;31m========== NOVOS ALERTAS DETECTADOS ==========\033[0m" << endl;
                for (const string &msg : alertas)
                {
                    cout << " -> " << msg << endl;
                }
                cout << "==============================================\n"
                     << endl;
            }
        }
        // ----------------------------------------------

        int escolha;
        cout << "\nHospital: " << h->get_nome() << endl;
        cout << "Escolha uma opcao:\n";
        cout << "1. Cadastrar novo paciente\n";
        cout << "2. Deletar Paciente\n";
        cout << "3. Buscar Paciente (Ver Sinais Vitais)\n";

        // Mostra se está rodando ou não
        if (sim.estaRodando())
            cout << "4. [PARAR] Simulacao (Rodando em background...)\n";
        else
            cout << "4. [INICIAR] Simulacao (Threads)\n";

        cout << "5. Atender Emergencia\n";
        cout << "0. Sair\n";
        cout << "Escolha: ";
        cin >> escolha;

        switch (escolha)
        {
        case 1: // CADASTRAR
        {
            idPaciente++;
            cout << "Digite: Nome, Idade, M/F: ";
            cin >> nomepaciente >> idadePaciente >> sexoPaciente;

            {
                std::lock_guard<std::mutex> lock(mtxHospital);
                Paciente *p = new Paciente(idPaciente, nomepaciente, idadePaciente, sexoPaciente);
                h->cadastrarPaciente(p);
                db.salvarPaciente(idPaciente, nomepaciente, idadePaciente, sexoPaciente, h->get_nome());
            }

            // --- FEEDBACK PARA O USUÁRIO ---
            cout << "\n****************************************" << endl;
            cout << " SUCEESSO! Paciente cadastrado." << endl;
            cout << " Nome: " << nomepaciente << endl;
            cout << " ID DO PACIENTE: " << idPaciente << "  <-- (Use este numero para buscar)" << endl;
            cout << "****************************************\n"
                 << endl;

            break;
        }
        case 2: // DELETAR
        {
            h->listarPacientes();
            try
            {
                int idBusca = lerID();
                // Bloqueia para garantir que a simulação não acesse enquanto deletamos
                std::lock_guard<std::mutex> lock(mtxHospital);

                Paciente *p = h->buscarPaciente(idBusca);
                if (p != nullptr)
                {
                    cout << "Paciente encontrado: " << p->get_nome() << endl;
                    cout << "Confirmar remocao? (S/N): ";
                    char x;
                    cin >> x;
                    if (x == 'S' || x == 's')
                    {
                        h->removerPaciente(idBusca);
                        db.removerPaciente(idBusca);
                    }
                }
                else
                    cout << "Paciente nao encontrado.\n";
            }
            catch (runtime_error &e)
            {
                cout << e.what() << endl;
            }
            break;
        }
        case 3: // BUSCAR E MOSTRAR SENSORES
        {
            try
            {
                cout << "\n--- Lista Rapida de Pacientes ---" << endl;
                h->listarPacientes();
                cout << "---------------------------------" << endl;
                // h->listarPacientes(); // Opcional, pode poluir se tiver muitos
                int idBusca = lerID();

                // Trava o mutex para ler os dados sem que a thread mude eles no meio da leitura
                std::lock_guard<std::mutex> lock(mtxHospital);

                Paciente *p = h->buscarPaciente(idBusca);
                if (p != nullptr)
                {
                    cout << "\n--- FICHA DO PACIENTE ---" << endl;
                    cout << "ID:    " << p->get_id() << endl;
                    cout << "Nome:  " << p->get_nome() << endl;
                    cout << "Idade: " << p->get_idade() << endl;
                    cout << "Sexo:  " << p->get_sexo() << endl;

                    cout << "\n--- MONITORAMENTO EM TEMPO REAL ---" << endl;
                    // Chama o lerValor() de cada sensor existente
                    if (p->get_sensorBatimento())
                    {
                        cout << "- ";
                        p->get_sensorBatimento()->lerValor();
                    }
                    if (p->get_sensorOxigenio())
                    {
                        cout << "- ";
                        p->get_sensorOxigenio()->lerValor();
                    }
                    if (p->get_sensorPressao())
                    {
                        cout << "- ";
                        p->get_sensorPressao()->lerValor();
                    }
                    if (p->get_sensorTemperatura())
                    {
                        cout << "- ";
                        p->get_sensorTemperatura()->lerValor();
                    }
                    if (p->get_sensorRespiratorio())
                    {
                        cout << "- ";
                        p->get_sensorRespiratorio()->lerValor();
                    }
                    cout << "-----------------------------------\n";
                }
                else
                    cout << "Paciente nao encontrado.\n";
            }
            catch (runtime_error &e)
            {
                cout << e.what() << endl;
            }
            break;
        }
        case 4: // LIGAR/DESLIGAR THREADS
        {
            if (sim.estaRodando())
            {
                sim.parar();
            }
            else
            {
                sim.iniciar(h);
            }
            break;
        }
        case 5: // ATENDER EMERGENCIA
        {
            try
            {
                cout << "\n--- Lista Rapida de Pacientes ---" << endl;
                h->listarPacientes();
                cout << "---------------------------------" << endl;
                int idEmergencia;
                cout << "digite o ID para atender: "; 
              
                cin >> idEmergencia;

                std::lock_guard<std::mutex> lock(mtxHospital);
                if (h->tratarPaciente(idEmergencia))
                    cout << "Paciente tratado com sucesso!\n";
                else
                    cout << "Erro ao tratar.\n";
            }
            catch (runtime_error &e)
            {
                cout << e.what() << endl;
            }
            break;
        }
        case 0:
            sim.parar(); // Para a thread antes de sair
            delete h;
            return 0;
        default:
            cout << "Opcao invalida" << endl;
            break;
        }
    }

    return 0;
}