#include <iostream>

#include "Editora.h"

using std::cout;
using std::endl;

Editora::Editora() {}


Editora::Editora(int novoCodigo, string novoNome)
    : codigo(novoCodigo), nome(novoNome)  {}


Editora::Editora(int novoCodigo, string novoNome, const Endereco& novoEndereco)
    : codigo(novoCodigo), nome(novoNome), endereco(novoEndereco)  {}


Editora::~Editora() {}      //assim como o autor nao precisa de delete pois editora nao faz alocacao dinamica


void Editora::imprimirEditora() {
    cout << "Codigo: " << codigo << endl;
    cout << "Nome: " << nome << endl;
    cout << "--- Endereco da Editora ---" << endl;
    endereco.imprimirEndereco(); 
}


int Editora::getCodigo() const { return codigo; }


string Editora::getNome() const { return nome; }


Endereco Editora::getEndereco() const { return endereco; }


void Editora::setCodigo(int novoCodigo) { this -> codigo = novoCodigo; }


void Editora::setNome(string novoNome) { this -> nome = novoNome; }


void Editora::setEndereco(Endereco& novoEndereco) { this -> endereco = novoEndereco; }