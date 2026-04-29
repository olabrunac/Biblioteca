#include "Autor.h"

#include <iostream>

using std::cout;
using std::endl;

Autor::Autor():codigo(0), nome("Sem Nome") {}

void Autor::imprimirAutor() {
    cout << "Codigo: " << codigo << endl;
    cout << "Nome: " << nome << endl;
}

int Autor::getCodigo() const {return codigo; }

string Autor::getNome() const {return nome; }

void Autor::setCodigo(int novoCodigo) { this -> codigo = novoCodigo; }

void Autor::setNome(string novoNome) { this -> nome = novoNome; }




