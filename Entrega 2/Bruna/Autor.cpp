#include "Autor.h"

#include <iostream>

using std::cout;
using std::endl;

Autor::Autor() {}

void Autor::imprimirAutor() {
    cout << "Codigo: " << codigo << endl;
    cout << "Nome: " << nome << endl;
}

int Autor::getCodigo() {return codigo; }

string Autor::getNome() {return nome; }

void Autor::setCodigo(int novoCodigo) { this -> codigo = novoCodigo; }

void Autor::setNome(string novoNome) { this -> nome = novoNome; }




