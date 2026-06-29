#ifndef PESQUISADOR_H
#define PESQUISADOR_H

#include "Professor.h"
#include "Aluno.h"
#include <iostream>

using std::cout;
using std::endl;


class Pesquisador : public Professor, public Aluno {

public:

    Pesquisador()
        : Usuario(),
          Professor(),
          Aluno()
    {}


    Pesquisador(int novoCodigo,
                string novoNome,
                StatusUsuario status = StatusUsuario::HABILITADO)
        : Usuario(novoCodigo, novoNome, status),
          Professor(novoCodigo, novoNome, status),
          Aluno(novoCodigo, novoNome, status)
    {}


    ~Pesquisador() override {

        cout << "Destruindo objeto tipo Pesquisador: "
             << nome << endl;
    }


    void imprimirUsuario() const override {

        cout << "Pesquisador: " << nome << " (Cod: " << codigo << ") | Status: ";
            cout << (status == StatusUsuario::HABILITADO ? "Habilitado" : "Em debito");
            cout << endl;
    }

};


#endif