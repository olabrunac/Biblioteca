#include "Autor.h"

#include <iostream>

using std::cout;
using std::endl;

Autor::Autor():codigo(0), nome("Sem Nome") {}               // Cria um autor com o código 0 e com o nome Sem Nome caso a classe seja criada sem informações

void Autor::imprimirAutor() {
    cout << "Codigo: " << codigo << endl;
    cout << "Nome: " << nome << endl;
}

int Autor::getCodigo() const { return codigo; }

string Autor::getNome() const { return nome; }

void Autor::setCodigo(int novoCodigo) { this -> codigo = novoCodigo; }  //setCodigo é um método e o novoCodigo é um parametro que o método exige para funcionar

void Autor::setNome(string novoNome) { this -> nome = novoNome; }       // this-> aponta tipo "pegue o atributo nome desse objeto e mude o valor dele para o novoNome que foi passado como parametro"



