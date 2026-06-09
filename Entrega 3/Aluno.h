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
            cout << "Aluno" << endl;
            cout << "Nome: " << nome << endl;
            cout << "Codigo: " << codigo << endl;
            cout << "Status do usuario: ";
            if (status == StatusUsuario::HABILITADO) {
                cout << "Habilitado" << endl;
            } else {
            cout << "Em debito" << endl;
            }
        }
};

#endif