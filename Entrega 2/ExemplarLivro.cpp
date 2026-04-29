#include "ExemplarLivro.h"
#include "Livro.h"
#include <iostream>

using std::cout;
using std::endl;

ExemplarLivro::ExemplarLivro(){}



void ExemplarLivro::imprimirExemplarLivro() {

    cout << "Titulo: " << livro->getTitulo() << endl;
    cout << "Numero do Exemplar: " << nroExemplar << endl;
    cout << "Status: " << (status == StatusParaEmprestimo::DISPONIVEL ? "DISPONIVEL" : "EMPRESTADO") << endl;
}

int ExemplarLivro::getNroExemplar() const { return nroExemplar; }



StatusParaEmprestimo ExemplarLivro::getStatus() const { return status; }

Livro* ExemplarLivro::getLivro() const { return livro; }

void ExemplarLivro::setNroExemplar(int novoNroExemplar) { this -> nroExemplar = novoNroExemplar; }

void ExemplarLivro::setStatus(StatusParaEmprestimo novoStatusEmprestimo) { this -> status = novoStatusEmprestimo; }

void ExemplarLivro::setLivro(Livro* Nlivro){ this->livro = Nlivro;}