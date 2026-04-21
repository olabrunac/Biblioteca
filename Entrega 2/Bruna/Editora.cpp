#include <iostream>

#include "Editora.h"

using std::cout;
using std::endl;

Editora::Editora() {}

void Editora::imprimirEditora() {
    cout << "Codigo: " << codigo << endl;
    cout << "Nome: " << nome << endl;
    cout << "Endereco: " << &endereco << endl; // ---------------------------------
}

int Editora::getCodigo() { return codigo; }

string Editora::getNome() { return nome; }

Endereco Editora::getEndereco() { return endereco; }

void Editora::setCodigo(int novoCodigo) { this -> codigo = novoCodigo; }

void Editora::setNome(string novoNome) { this -> nome = novoNome; }

void Editora::setEndereco(Endereco& novoEndereco) { this -> endereco = novoEndereco; }