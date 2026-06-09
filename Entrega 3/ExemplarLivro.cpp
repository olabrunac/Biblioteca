#include "ExemplarLivro.h"
#include "Livro.h"
#include "StatusEmprestimo.h"
#include <iostream>
#include <string>

using std::cout;
using std::endl;

ExemplarLivro::ExemplarLivro() {}


ExemplarLivro::~ExemplarLivro() {}      //nao faz alocacao dinamica


void ExemplarLivro::imprimirExemplarLivro() {

    cout << livro->getTitulo() << ", " << nroExemplar << ", " << toString(status) << endl;
}


int ExemplarLivro::getNroExemplar() const { return nroExemplar; }


StatusEmprestimo ExemplarLivro::getStatus() const { return status; }


Livro* ExemplarLivro::getLivro() const { return livro; }


void ExemplarLivro::setNroExemplar(int novoNroExemplar) { this -> nroExemplar = novoNroExemplar; }


void ExemplarLivro::setStatus(StatusEmprestimo novoStatusEmprestimo) { this -> status = novoStatusEmprestimo; }


void ExemplarLivro::setLivro(Livro* Nlivro){ this->livro = Nlivro;}