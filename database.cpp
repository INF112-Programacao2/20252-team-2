#include "database.h"
#include <iostream>
#include <string>

GerenciadorBD::GerenciadorBD()
{
    // Atenção: Use aspas "sqlite3.h" se estiver na mesma pasta
    int rc = sqlite3_open("dados_hospital.db", &db);
    if (rc)
    {
        std::cerr << "Erro ao abrir banco: " << sqlite3_errmsg(db) << std::endl;
    }
}

GerenciadorBD::~GerenciadorBD()
{
    sqlite3_close(db);
}

void GerenciadorBD::verificarErro(int rc, char *zErrMsg)
{
    if (rc != SQLITE_OK)
    {
        std::cerr << "Erro SQL: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
    }
}

void GerenciadorBD::inicializar()
{
    char *zErrMsg = 0;
    std::string sqlH = "CREATE TABLE IF NOT EXISTS Hospital (nome TEXT PRIMARY KEY, capacidade INTEGER NOT NULL);";
    std::string sqlP = "CREATE TABLE IF NOT EXISTS Paciente (id INTEGER PRIMARY KEY, nome TEXT NOT NULL, idade INTEGER, sexo TEXT, nome_hospital TEXT, FOREIGN KEY(nome_hospital) REFERENCES Hospital(nome));";

    verificarErro(sqlite3_exec(db, sqlH.c_str(), 0, 0, &zErrMsg), zErrMsg);
    verificarErro(sqlite3_exec(db, sqlP.c_str(), 0, 0, &zErrMsg), zErrMsg);
}

void GerenciadorBD::salvarHospital(std::string nome, int capacidade)
{
    std::string sql = "INSERT OR IGNORE INTO Hospital (nome, capacidade) VALUES ('" + nome + "', " + std::to_string(capacidade) + ");";
    char *zErrMsg = 0;
    verificarErro(sqlite3_exec(db, sql.c_str(), 0, 0, &zErrMsg), zErrMsg);
}

std::vector<std::pair<std::string, int>> GerenciadorBD::listarHospitais()
{
    std::vector<std::pair<std::string, int>> hospitais;
    sqlite3_stmt *stmt;
    std::string sql = "SELECT nome, capacidade FROM Hospital";

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0) == SQLITE_OK)
    {
        while (sqlite3_step(stmt) == SQLITE_ROW)
        {
            std::string nome = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0));
            int cap = sqlite3_column_int(stmt, 1);
            hospitais.push_back({nome, cap});
        }
    }
    sqlite3_finalize(stmt);
    return hospitais;
}

void GerenciadorBD::salvarPaciente(int id, std::string nome, int idade, std::string sexo, std::string nomeHospital)
{
    std::string sql = "INSERT OR REPLACE INTO Paciente (id, nome, idade, sexo, nome_hospital) VALUES (" +
                      std::to_string(id) + ", '" + nome + "', " + std::to_string(idade) + ", '" + sexo + "', '" + nomeHospital + "');";
    char *zErrMsg = 0;
    verificarErro(sqlite3_exec(db, sql.c_str(), 0, 0, &zErrMsg), zErrMsg);
}

void GerenciadorBD::removerPaciente(int id)
{
    std::string sql = "DELETE FROM Paciente WHERE id = " + std::to_string(id) + ";";
    char *zErrMsg = 0;
    verificarErro(sqlite3_exec(db, sql.c_str(), 0, 0, &zErrMsg), zErrMsg);
}

void GerenciadorBD::removerHospital(std::string nome)
{
    char *zErrMsg = 0;
    std::string sqlP = "DELETE FROM Paciente WHERE nome_hospital = '" + nome + "';";
    verificarErro(sqlite3_exec(db, sqlP.c_str(), 0, 0, &zErrMsg), zErrMsg);

    std::string sqlH = "DELETE FROM Hospital WHERE nome = '" + nome + "';";
    verificarErro(sqlite3_exec(db, sqlH.c_str(), 0, 0, &zErrMsg), zErrMsg);
}

void GerenciadorBD::resetarBanco()
{
    char *zErrMsg = 0;
    const char *sql = "DROP TABLE IF EXISTS Paciente; DROP TABLE IF EXISTS Hospital;";
    sqlite3_exec(db, sql, 0, 0, &zErrMsg);
    inicializar(); // Recria tabelas vazias
}

int GerenciadorBD::getUltimoIdPaciente()
{
    sqlite3_stmt *stmt;
    std::string sql = "SELECT MAX(id) FROM Paciente;";
    int maiorId = 0;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0) == SQLITE_OK)
    {
        if (sqlite3_step(stmt) == SQLITE_ROW)
        {
            maiorId = sqlite3_column_int(stmt, 0);
        }
    }
    sqlite3_finalize(stmt);
    return maiorId;
}

void GerenciadorBD::carregarPacientesParaHospital(Hospital *h)
{
    sqlite3_stmt *stmt;
    std::string sql = "SELECT id, nome, idade, sexo FROM Paciente WHERE nome_hospital = '" + h->get_nome() + "';";

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0) == SQLITE_OK)
    {
        while (sqlite3_step(stmt) == SQLITE_ROW)
        {
            int id = sqlite3_column_int(stmt, 0);
            std::string nome = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
            int idade = sqlite3_column_int(stmt, 2);
            std::string sexo = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3));

            Paciente *p = new Paciente(id, nome, idade, sexo);
            h->cadastrarPaciente(p);

            // IMPORTANTE: NÃO FAZEMOS 'delete p' AQUI!
            // O Hospital agora é o dono do ponteiro p.
        }
    }
    sqlite3_finalize(stmt);
}