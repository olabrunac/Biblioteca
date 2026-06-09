#include "Autor.h"

#include <iostream>

using std::cout;
using std::endl;

Autor::Autor():codigo(0), nome("Sem Nome") {}


Autor::Autor(int novoCodigo, string novoNome)
    : codigo(novoCodigo), nome(novoNome) {}


Autor::~Autor() {}      //nao precisa de delete pois nao faz alocacao dinamica (new)


void Autor::imprimirAutor() {  
        cout << "Codigao: " << codigo << endl;
        cout << "Nome: " << nome << endl;
}


void Autor::imprimirTodos(const vector<Autor*>& listaAutores) {
    for (vector<Autor*>::const_iterator temp = listaAutores.begin(); temp != listaAutores.end(); ++temp) {
        cout << "Codigo: " << (*temp)->getCodigo() << " | Nome: " << (*temp)->getNome() << endl;
    }
}


int Autor::getCodigo() const { return codigo; }


string Autor::getNome() const { return nome; }


void Autor::setCodigo(int novoCodigo) { this -> codigo = novoCodigo; }


void Autor::setNome(string novoNome) { this -> nome = novoNome; }
