#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <string>
#include <vector>
#include <mutex>
#include <limits>
#include "hospital.h"
#include "paciente.h"
#include "database.h"
#include "simulador.h"

using namespace std;

// --- CORES E FORMATAÇÃO ---
#define RESET "\033[0m"
#define RED "\033[31m"     // Erro
#define GREEN "\033[32m"   // Sucesso
#define YELLOW "\033[33m"  // Alerta
#define BLUE "\033[34m"    // Informação
#define MAGENTA "\033[35m" // Detalhe
#define CYAN "\033[36m"    // Títulos
#define BOLD "\033[1m"     // Negrito

// --- FUNÇÕES VISUAIS AUXILIARES ---

void limparTela()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pausa()
{
    cout << "\n"
         << YELLOW << "Pressione [ENTER] para continuar..." << RESET;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void cabecalho(string titulo)
{
    limparTela();
    cout << CYAN << "+===========================================================+" << RESET << endl;
    cout << CYAN << "| " << BOLD << titulo << string(58 - titulo.length(), ' ') << "|" << RESET << endl;
    cout << CYAN << "+===========================================================+" << RESET << endl;
    cout << endl;
}

void linhaDivisoria()
{
    cout << BLUE << "-------------------------------------------------------------" << RESET << endl;
}

// --- VARIÁVEIS GLOBAIS ---
int idPaciente = 0;
string nomepaciente;
int idadePaciente;
string sexoPaciente;

// --- FUNÇÃO DE LEITURA SEGURA ---
int lerID()
{
    string entrada;
    int id;
    while (true)
    {
        cout << BOLD << "Digite o ID do paciente: " << RESET;
        cin >> entrada;
        try
        {
            id = stoi(entrada);
            return id;
        }
        catch (invalid_argument &)
        {
            cout << RED << ">> Erro: Digite apenas numeros!" << RESET << endl;
        }
    }
}

int main()
{
    srand(time(0));

    // Inicializar Banco de Dados
    GerenciadorBD db;
    db.inicializar();
    idPaciente = db.getUltimoIdPaciente();

    // Inicializar Gerenciador de Threads
    GerenciadorSimulacao sim;

    string nomeHospital;
    int capacidadeHospital;
    Hospital *h = nullptr;

    // --- TELA DE INICIALIZAÇÃO ---
    while (h == nullptr)
    {
        cabecalho("SISTEMA DE GESTAO HOSPITALAR - LOGIN");

        vector<pair<string, int>> hospitaisSalvos = db.listarHospitais();

        if (!hospitaisSalvos.empty())
        {
            cout << BOLD << "Selecione um Hospital existente:" << RESET << endl;
            linhaDivisoria();
            for (size_t i = 0; i < hospitaisSalvos.size(); i++)
            {
                cout << " [" << CYAN << i + 1 << RESET << "] "
                     << hospitaisSalvos[i].first
                     << MAGENTA << " (Cap: " << hospitaisSalvos[i].second << ")" << RESET << endl;
            }
            linhaDivisoria();
            cout << " [" << GREEN << "0" << RESET << "] Criar NOVO hospital" << endl;
            cout << " [" << RED << "-1" << RESET << "] DELETAR um hospital" << endl;
            linhaDivisoria();

            int opcao;
            cout << "Escolha: ";
            string entradaOpcao;
            cin >> entradaOpcao;
            try
            {
                opcao = stoi(entradaOpcao);
            }
            catch (invalid_argument &)
            {
                opcao = -99;
            }

            if (opcao == 0)
                break;
            else if (opcao == -1)
            {
                cout << "\nDigite o numero do hospital para " << RED << "DELETAR" << RESET << ": ";
                int del;
                cin >> del;
                if (del > 0 && del <= (int)hospitaisSalvos.size())
                {
                    string nomeParaDeletar = hospitaisSalvos[del - 1].first;
                    cout << RED << "Tem certeza que deseja apagar '" << nomeParaDeletar << "'? (S/N): " << RESET;
                    char confirm;
                    cin >> confirm;
                    if (confirm == 'S' || confirm == 's')
                    {
                        db.removerHospital(nomeParaDeletar);
                        cout << GREEN << "Hospital removido!" << RESET << endl;
                        pausa();
                    }
                }
                else
                {
                    cout << RED << "Opcao invalida!" << RESET << endl;
                    pausa();
                }
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
                cout << GREEN << "\n>> Hospital carregado com sucesso!" << RESET << endl;
                pausa();
            }
            else
            {
                cout << RED << "Opcao invalida." << RESET << endl;
                pausa();
            }
        }
        else
            break;
    }

    if (h == nullptr)
    {
        cabecalho("CRIACAO DE NOVO HOSPITAL");
        cout << "Nome do Hospital: ";
        cin >> nomeHospital;

        while (true)
        {
            cout << "Capacidade Maxima: ";
            string entradaCapacidade;
            cin >> entradaCapacidade;
            try
            {
                capacidadeHospital = stoi(entradaCapacidade);
                if (capacidadeHospital <= 0)
                    throw runtime_error("Deve ser positivo");
                break;
            }
            catch (...)
            {
                cout << RED << ">> Erro: Digite um numero valido (>0)." << RESET << endl;
            }
        }

        h = new Hospital(nomeHospital, capacidadeHospital);
        db.salvarHospital(nomeHospital, capacidadeHospital);
        cout << GREEN << "\n>> Hospital criado com sucesso!" << RESET << endl;
        pausa();
    }

    // --- MENU PRINCIPAL (LOOP) ---
    while (true)
    {
        // Só limpa a tela se NÃO tiver alertas críticos recentes para mostrar

        string tituloMenu = "HOSPITAL: " + h->get_nome();
        cabecalho(tituloMenu);

        if (sim.estaRodando())
        {
            vector<string> alertas = sim.pegarAlertas();
            if (!alertas.empty())
            {

                for (const string &msg : alertas)
                {
                    cout << msg << endl;
                }
                linhaDivisoria();
            }
        }

        // --- MENU ---
        cout << CYAN << " GERENCIAMENTO DE PACIENTES" << RESET << endl;
        cout << " [" << BOLD << "1" << RESET << "] Cadastrar Paciente" << endl;
        cout << " [" << BOLD << "2" << RESET << "] Deletar Paciente" << endl;
        cout << " [" << BOLD << "3" << RESET << "] Buscar/Monitorar Paciente" << endl;
        cout << endl;

        cout << CYAN << " CONTROLE DE SIMULACAO" << RESET << endl;
        if (sim.estaRodando())
            cout << " [" << BOLD << "4" << RESET << "] " << RED << "PARAR Monitoramento" << RESET << " (Rodando...)" << endl;
        else
            cout << " [" << BOLD << "4" << RESET << "] " << GREEN << "INICIAR Monitoramento" << RESET << " (Threads)" << endl;

        cout << " [" << BOLD << "5" << RESET << "] " << YELLOW << "ATENDER EMERGENCIA" << RESET << endl;
        linhaDivisoria();
        cout << " [" << BOLD << "0" << RESET << "] Sair do Sistema" << endl;

        cout << "\n"
             << BOLD << "Escolha: " << RESET;

        string entradaEscolha;
        int escolha;
        cin >> entradaEscolha;

        try
        {
            escolha = stoi(entradaEscolha);
        }
        catch (invalid_argument &)
        {
            escolha = -1;
        }

        switch (escolha)
        {
        case 1: // CADASTRAR
        {
            cout << "\n"
                 << CYAN << "--- NOVO CADASTRO ---" << RESET << endl;
            idPaciente++;

            cout << "Nome: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, nomepaciente);

            cout << "Idade: ";
            while (!(cin >> idadePaciente) || idadePaciente < 0)
            {
                cout << RED << ">> Idade invalida! " << RESET;
                cin.clear();
                cin.ignore(10000, '\n');
            }

            do
            {
                cout << "Sexo (M/F): ";
                cin >> sexoPaciente;
                if (!sexoPaciente.empty())
                    sexoPaciente[0] = toupper(sexoPaciente[0]);
                if (sexoPaciente != "M" && sexoPaciente != "F")
                    cout << RED << ">> Use apenas M ou F." << RESET << endl;
            } while (sexoPaciente != "M" && sexoPaciente != "F");

            Paciente *p = nullptr;
            try
            {
                std::lock_guard<std::mutex> lock(mtxHospital);
                p = new Paciente(idPaciente, nomepaciente, idadePaciente, sexoPaciente);
                h->cadastrarPaciente(p);
                db.salvarPaciente(idPaciente, nomepaciente, idadePaciente, sexoPaciente, h->get_nome());

                cout << GREEN << "\n[OK] Paciente cadastrado com sucesso!" << RESET << endl;
                cout << "ID Gerado: " << BOLD << idPaciente << RESET << endl;
            }
            catch (runtime_error &e)
            {
                cout << RED << "\n[ERRO] Falha ao cadastrar: " << e.what() << RESET << endl;
                delete p;
                idPaciente--;
            }
            pausa();
            break;
        }
        case 2: // DELETAR
        {
            cout << "\n"
                 << CYAN << "--- REMOVER PACIENTE ---" << RESET << endl;

            {
                std::lock_guard<std::mutex> lock(mtxHospital);
                h->listarPacientes();
            }
            linhaDivisoria();

            try
            {
                int idBusca = lerID();
                string nomeParaConfirmar;
                bool encontrado = false;

                // --- FASE 1: BUSCA ---
                {
                    std::lock_guard<std::mutex> lock(mtxHospital);
                    Paciente *p = h->buscarPaciente(idBusca);
                    if (p != nullptr)
                    {
                        nomeParaConfirmar = p->get_nome();
                        encontrado = true;
                    }
                }

                if (encontrado)
                {
                    char x;

                    while (true)
                    {
                        cout << YELLOW << "Remover paciente " << nomeParaConfirmar << "? (S/N): " << RESET;
                        cin >> x;
                        x = toupper(x);

                        if (x == 'S' || x == 'N')
                            break;

                        cout << RED << ">> Opcao invalida! Digite S ou N." << RESET << endl;
                        cin.ignore(10000, '\n');
                    }

                    if (x == 'S')
                    {

                        std::lock_guard<std::mutex> lock(mtxHospital);

                        h->removerPaciente(idBusca);
                        db.removerPaciente(idBusca);
                    }
                    else
                    {
                        cout << "Operacao cancelada." << endl;
                    }
                }
                else
                {

                    throw runtime_error("Paciente nao encontrado com este ID.");
                }
            }
            catch (runtime_error &e)
            {

                cout << RED << "Erro: " << e.what() << RESET << endl;
            }

            pausa();
            break;
        }
        case 3: // BUSCAR E MOSTRAR SENSORES (Visual Card)
        {
            cout << "\n"
                 << CYAN << "--- BUSCAR PACIENTE ---" << RESET << endl;
            h->listarPacientes();
            linhaDivisoria();

            try
            {
                int idBusca = lerID();
                std::lock_guard<std::mutex> lock(mtxHospital); // Trava leitura

                Paciente *p = h->buscarPaciente(idBusca);
                if (p != nullptr)
                {
                    // --- DESIGN DO CARTÃO DO PACIENTE ---
                    limparTela();
                    cout << CYAN << "+===========================================================+" << RESET << endl;
                    cout << CYAN << "|                    FICHA MEDICA DIGITAL                   |" << RESET << endl;
                    cout << CYAN << "+===========================================================+" << RESET << endl;
                    cout << " ID:    " << BOLD << p->get_id() << RESET << "\t\tSexo: " << p->get_sexo() << endl;
                    cout << " Nome:  " << BOLD << p->get_nome() << RESET << "\tIdade: " << p->get_idade() << " anos" << endl;
                    cout << BLUE << "-------------------------------------------------------------" << RESET << endl;
                    cout << BOLD << " SINAIS VITAIS (Tempo Real):" << RESET << endl;
                    cout << endl;

                    // Exibição dos Sensores com formatação
                    auto printSensor = [](string label, Sensor *s)
                    {
                        if (s)
                        {
                            cout << "  > " << label << ": ";
                            s->lerValor();
                        }
                    };

                    printSensor("Batimentos     ", p->get_sensorBatimento());
                    printSensor("Oxigenacao     ", p->get_sensorOxigenio());
                    printSensor("Pressao Art.   ", p->get_sensorPressao());
                    printSensor("Temperatura    ", p->get_sensorTemperatura());
                    printSensor("Freq. Resp.    ", p->get_sensorRespiratorio());

                    cout << CYAN << "+===========================================================+" << RESET << endl;
                }
                else
                {
                    cout << RED << "Paciente nao encontrado." << RESET << endl;
                }
            }
            catch (runtime_error &e)
            {
                cout << RED << e.what() << RESET << endl;
            }
            pausa();
            break;
        }
        case 4: // THREADS
        {
            if (sim.estaRodando())
            {
                sim.parar();
                cout << YELLOW << "\n>> Simulacao PAUSADA." << RESET << endl;
            }
            else
            {
                sim.iniciar(h);
                cout << GREEN << "\n>> Simulacao INICIADA em segundo plano." << RESET << endl;
            }
            // Pequeno delay para ler a msg antes do refresh
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            break;
        }
        case 5: // EMERGENCIA
        {
            cout << "\n"
                 << RED << "--- ATENDIMENTO DE EMERGENCIA ---" << RESET << endl;
            h->listarPacientes();
            linhaDivisoria();

            try
            {
                int idEmergencia = lerID();
                std::lock_guard<std::mutex> lock(mtxHospital);

                if (h->tratarPaciente(idEmergencia))
                    cout << GREEN << BOLD << ">> SUCESSO! Paciente estabilizado." << RESET << endl;
                else
                    cout << RED << "Erro: Paciente nao encontrado." << RESET << endl;
            }
            catch (runtime_error &e)
            {
                cout << RED << "Erro: " << e.what() << RESET << endl;
            }
            pausa();
            break;
        }
        case 0:
            sim.parar();
            delete h;
            cout << CYAN << "Encerrando sistema... Ate logo!" << RESET << endl;
            return 0;
        default:
            cout << RED << "Opcao invalida" << RESET << endl;
            pausa();
            break;
        }
    }

    return 0;
}