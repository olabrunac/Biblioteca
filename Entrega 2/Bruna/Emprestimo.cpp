#include "Emprestimo.h"
#include <iostream>

using std::cout;
using std::endl;

Emprestimo::Emprestimo() {}

void Emprestimo::imprimirEmprestimo() {
    cout << "Data de Retirada: " << dataDeRetirada << endl;
    cout << "Status: " << status << endl;
}

int Emprestimo::getDataDeRetirada() { return dataDeRetirada; }

int Emprestimo::getDataPrevistaDevolucao() { return dataPrevistaDevolucao; }

int Emprestimo::getDataDevolucao() { return dataDevolucao; }

int Emprestimo::getStatus() { return status; }

void Emprestimo::setDataDeRetirada(int novaDataDeRetirada) { this -> dataDeRetirada = novaDataDeRetirada; }

void Emprestimo::setDataPrevistaDevolucao(int novaDataPrevistaDevolucao) { this -> dataPrevistaDevolucao = novaDataPrevistaDevolucao; }

void Emprestimo::setDataDevolucao(int novaDataDevolucao) { this -> dataDevolucao = novaDataDevolucao; }

void Emprestimo::setStatus(int novoStatus) { this -> status = novoStatus;} 
