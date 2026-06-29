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

        cout << "Pesquisador" << endl;
        cout << "Nome: " << nome << endl;

        cout << "Status do usuario: ";

        if(status == StatusUsuario::HABILITADO)
            cout << "Habilitado" << endl;
        else
            cout << "Em debito" << endl;
    }

};


#endif