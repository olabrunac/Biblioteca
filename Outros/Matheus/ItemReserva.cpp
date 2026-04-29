#include "ItemReserva.h"
#include <iostream>

using std::cout;
using std::endl;

ItemReserva::ItemReserva() {}

void ItemReserva::imprimirItemReserva() {
    cout << "Numero do Item: " << nroDoItem << endl;
    cout << "Data de Retirada: " << dataDeRetirada << endl;
    cout << "Livro: " << &livro << endl;
}

int ItemReserva::getNroDoItem() { return nroDoItem; }

int ItemReserva::getDataDeRetirada() { return dataDeRetirada; }

Livro ItemReserva::getLivro() { return livro; }

void ItemReserva::setNroDoItem(int novoNroDoItem) { this -> nroDoItem = novoNroDoItem; }

void ItemReserva::setDataDeRetirada(int novaDataDeRetirada) { this -> dataDeRetirada = novaDataDeRetirada; }

void ItemReserva::setLivro(Livro& novoLivro) { this -> livro = novoLivro; }