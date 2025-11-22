#ifndef DATABASE_H
#define DATABASE_H

#include "sqlite3.h"
#include <string>
#include <vector>
#include "hospital.h"

class GerenciadorBD
{
private:
    sqlite3 *db;
    void verificarErro(int rc, char *zErrMsg);

public:
    GerenciadorBD();
    ~GerenciadorBD();

    // Inicializa as tabelas se não existirem
    void inicializar();

    // Funções para Hospital
    void salvarHospital(std::string nome, int capacidade);
    bool hospitalExiste(std::string nome);
    std::vector<std::pair<std::string, int>> listarHospitais();

    // Funções para Paciente
    void salvarPaciente(int id, std::string nome, int idade, std::string sexo, std::string nomeHospital);
    void removerPaciente(int id);
    void carregarPacientesParaHospital(Hospital *h);
    int getUltimoIdPaciente();
    void removerHospital(std::string nome);
    void resetarBanco();
};

#endif