#include "ExemplarLivro.h"
#include <iostream>

using std::cout;
using std::endl;

ExemplarLivro::ExemplarLivro() {}

void ExemplarLivro::imprimirExemplarLivro() {
    cout << "Numero do Exemplar: " << nroExemplar << endl;
    cout << "Status: " << (status == StatusEmprestimo::DISPONIVEL ? "DISPONIVEL" : "EMPRESTADO") << endl;
}

int ExemplarLivro::getNroExemplar() const{ return nroExemplar; }

StatusEmprestimo ExemplarLivro::getStatus() const { return status; }

void ExemplarLivro::setNroExemplar(int novoNroExemplar) { this -> nroExemplar = novoNroExemplar; }

void ExemplarLivro::setStatus(StatusEmprestimo novoStatusEmprestimo) { this -> status = novoStatusEmprestimo; }