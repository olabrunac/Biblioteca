#include "Reserva.h"
#include <iostream>

using std::cout;
using std::endl;

Reserva::Reserva() {}

void Reserva::imprimirReserva() {
    cout << "ID: " << ID << endl;
    cout << "Data da Reserva: " << dataRealizacao << endl;
}

int Reserva::getID() { return ID; }

int Reserva::getDataRealizacao() { return dataRealizacao; }

void Reserva::setID(int novoID) { this -> ID = novoID; }

void Reserva::setDataRealizacao(int novaDataReserva) { this -> dataRealizacao = novaDataReserva; }
