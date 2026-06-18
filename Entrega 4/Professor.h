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

        ~Professor() override {cout << "Destruindo objeto tipo Professor: " << this->nome << endl; }

        void imprimirUsuario() const override {     //implementado aqui para sobrescrever a herança
            cout << "Professor - Cod: " << codigo << " | Nome: " << nome << " | Status: ";
            cout << (status == StatusUsuario::HABILITADO ? "Habilitado" : "Em debito");
            cout << endl;
        }
};

#endif