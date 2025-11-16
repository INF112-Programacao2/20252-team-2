#include "paciente.h"
#include <iostream>

    Paciente::Paciente(){}

    Paciente::Paciente(std::string nome, int idade, std::string sexo)
    :_nome(nome), _idade(idade), _sexo(sexo){

    }
    Paciente::~Paciente(){

    }
    int Paciente::get_id(){
        return _id;
    }
    std::string Paciente::get_nome(){
        return _nome;
    }
    int Paciente::get_idade(){
        return _idade;
    }
    std::string Paciente::get_sexo(){
        return _sexo;
    }