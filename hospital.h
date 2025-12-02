#ifndef HOSPITAL_H
#define HOSPITAL_H
#include <iostream>
#include "paciente.h"

// Classe Hospital
class Hospital
{
private:
    int _capacidade;
    int _qtdPacientes;
    std::string _nome;
    Paciente **_pacientes;

public:
    // construtor
    Hospital(std::string nome, int capacidade);
    // destrutor
    ~Hospital();
    // funcoes do sistema
    void cadastrarPaciente(Paciente *p);
    void removerPaciente(int idPaciente);
    Paciente *buscarPaciente(int idPaciente);
    void listarPacientes();
    void atualizarSensores();
    bool tratarPaciente(int Id);
    // getters
    std::string get_nome();
    int get_qtdPacientes();
    Paciente **get_pacientes();
};

#endif