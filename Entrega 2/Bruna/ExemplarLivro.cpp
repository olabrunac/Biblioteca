#include "ExemplarLivro.h"
#include <iostream>

using std::cout;
using std::endl;

ExemplarLivro::ExemplarLivro() {}

void ExemplarLivro::imprimirExemplarLivro() {
    cout << "Numero do Exemplar: " << nroExemplar << endl;
    cout << "Status do emprestimo: " << &status << endl; //----------------
}

int ExemplarLivro::getNroExemplar() { return nroExemplar; }

StatusEmprestimo ExemplarLivro::getStatus() { return status; }

void ExemplarLivro::setNroExemplar(int novoNroExemplar) { this -> nroExemplar = novoNroExemplar; }

void ExemplarLivro::setStatus(StatusEmprestimo& novoStatusEmprestimo) { this -> status = novoStatusEmprestimo; }