#ifndef HOSPITAL_H
#define HOSPITAL_H
#include <iostream>
#include "paciente.h"

class Hospital
{
private:
    int _capacidade;
    int _qtdPacientes;
    std::string _nome;
    Paciente *_pacientes;

public:
    Hospital(std::string nome, int capacidade);
    ~Hospital();
    void cadastrarPaciente(Paciente *p);
    void removerPaciente(int idPaciente);
    Paciente *buscarPaciente(int idPaciente);
    std::string get_nome();
    int get_qtdPacientes();
    Paciente **get_pacientes();
    void listarPacientes();
};

#endif
