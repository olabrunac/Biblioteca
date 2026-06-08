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
        Aluno(int novoCodigo, string novoNome, StatusUsuario status = StatusUsuario::HABILITADO) : Usuario(novoCodigo, novoNome, novoStatus) {}
        
        void imprimirUsuario() const override {
        cout << "---Dados do Aluno---" << endl;
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