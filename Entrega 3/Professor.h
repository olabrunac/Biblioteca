#ifndef PROFESSOR_H
#define PROFESSOR_H

#include "Usuario.h"
#include <iostream>

using std::cout;
using std::endl;

class Professor : public Usuario {
    public:
        Professor():Usuario() {}

        Professor(int novoCodigo, string novoNome, StatusUsuario status = StatusUsuario::HABILITADO) : Usuario(novoCodigo, novoNome, status) {}

        void imprimirUsuario() const override {     //implementado aqui para sobrescrever a herança
            cout << "---Dados do Professor---" << endl;
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