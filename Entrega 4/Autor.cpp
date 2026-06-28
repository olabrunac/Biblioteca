#include "Autor.h"

#include <iostream>

using std::cout;
using std::endl;


Autor::Autor():codigo(0), nome("Sem Nome") {}


Autor::Autor(int novoCodigo, string novoNome)
    : codigo(novoCodigo), nome(novoNome) {}


Autor::~Autor() {}      //nao precisa de delete pois nao faz alocacao dinamica (new)


void Autor::imprimirAutor() {  
        cout << "Codigo: " << codigo << " | Nome: " << nome << endl;
}


void Autor::imprimirTodos(const vector<Autor*>& listaAutores) {
    for (auto temp : listaAutores) {
        cout << "Codigo: " << temp->getCodigo() << " | Nome: " << temp->getNome() << endl;
    }
}


//-------------------- sets e gets --------------------


int Autor::getCodigo() const { return codigo; }


string Autor::getNome() const { return nome; }


void Autor::setCodigo(int novoCodigo) { this -> codigo = novoCodigo; }


void Autor::setNome(string novoNome) { this -> nome = novoNome; }
