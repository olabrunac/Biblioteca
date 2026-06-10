#ifndef ALUNO_H
#define ALUNO_H

#include "Usuario.h"
#include <iostream>

using std::cout;
using std::endl;

class Aluno : public Usuario {
    public:
        Aluno():Usuario() {}
        //herdando os atributos do construtor
        Aluno(int novoCodigo, string novoNome, StatusUsuario status = StatusUsuario::HABILITADO) : Usuario(novoCodigo, novoNome, status) {}
        
        ~Aluno() override { cout << "Destruindo objeto tipo Aluno: " << this->nome << endl; } 

        void imprimirUsuario() const override {
            cout << "Aluno - Cod: " << codigo << " | Nome: " << nome << " | Status: ";
            cout << (status == StatusUsuario::HABILITADO ? "Habilitado" : "Em debito");
            cout << endl;
        }
};

#endif