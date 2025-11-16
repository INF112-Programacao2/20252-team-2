#include "hospital.h"
#include "paciente.h"
#include <iostream>

    Hospital::Hospital(std::string nome, int capacidade)
    :_nome(nome), _capacidade(capacidade), _qtdPacientes(0){
        _paciente = new Paciente[capacidade];
    }
    Hospital::~Hospital(){
        delete[] _paciente;
    }
    void Hospital::cadastrarPaciente(Paciente *p){
        if(_qtdPacientes<_capacidade){
            _paciente[_qtdPacientes] = *p;
            _qtdPacientes++;
        }
        else std::cout << "O hospital esta lotado!" << std::endl;
    }
    void Hospital::removerPaciente(int idPaciente){
        for (int i = 0; i < _qtdPacientes; i++) {
            if (_paciente[i].get_id() == idPaciente) {
                
                for (int j = i; j < _qtdPacientes - 1; j++) { // Deleta o paciente escolhido e realoca o vetor para nao perder espaco
                    _paciente[j] = _paciente[j + 1];
                }
                _qtdPacientes--;
                std::cout << "Paciente de ID: " << idPaciente << " removido com sucesso!" << std::endl;
                return;
            }
        }
        std::cout << "Paciente não encontrado!" << std::endl;
    }
    Paciente* Hospital::buscarPaciente(int idPaciente){
        for (int i = 0; i < _qtdPacientes; i++) {
            if (_paciente[i].get_id() == idPaciente) {
                return &_paciente[i];
                    }
                }
        return nullptr; // se nao encontrar
    }
    std::string Hospital::get_nome(){
        return _nome;
    }