#include "Usuario.h"
#include <iostream>

using std::cout;
using std::endl;

Usuario::Usuario() {}

void Usuario::imprimirUsuario() const {
    cout << "Codigo: " << codigo << endl;
    cout << "Nome: " << nome << endl;
    cout << "Status do usuário: " << &status << endl;
}

int Usuario::getCodigo() { return codigo; }

string Usuario::getNome() { return nome; }

StatusUsuario Usuario::getStatus() { return status; }

void Usuario::setCodigo(int novoCodigo) { this -> codigo = novoCodigo; }

void Usuario::setNome(string novoNome) { this -> nome = novoNome; }

void Usuario::setStatus(StatusUsuario& novoStatus) { this -> status = novoStatus; }