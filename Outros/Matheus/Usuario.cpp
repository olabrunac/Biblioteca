#include "Usuario.h"
#include <iostream>

using std::cout;
using std::endl;

Usuario::Usuario(): codigo(0), nome(""), status(StatusUsuario::HABILITADO){}

void Usuario::imprimirUsuario() const {
    cout << "Nome: " << nome << endl;
    cout << "Codigo: " << codigo << endl;
    cout << "Status do usuário: ";
    if (status == StatusUsuario::HABILITADO) {
        cout << "Habilitado" << endl;
    } else {
        cout << "Em débito" << endl; 
    }
}

int Usuario::getCodigo() const { return codigo; }

string Usuario::getNome() const{ return nome; }

StatusUsuario Usuario::getStatus() const { return status; }


void Usuario::setCodigo(int novoCodigo) { this -> codigo = novoCodigo; }

void Usuario::setNome(string novoNome) { this -> nome = novoNome; }

void Usuario::setStatus(StatusUsuario novoStatus) { this -> status = novoStatus; } // Para Enums,não precisa passar por referência
