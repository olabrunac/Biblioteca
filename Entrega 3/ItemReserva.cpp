#include "ItemReserva.h"
#include <iostream>

using std::cout;
using std::endl;

ItemReserva::ItemReserva() {}


ItemReserva::ItemReserva(int novoNroDoItem, const Data& novaDataDeRetirada, Livro* novoLivro)
    : nroDoItem(novoNroDoItem), dataDeRetirada(novaDataDeRetirada), livro(novoLivro) {}


ItemReserva::~ItemReserva() {}


void ItemReserva::imprimirItemReserva() const{
    cout << "Numero do Item: " << nroDoItem << endl;
    cout << "Data de Retirada: " << dataDeRetirada.getDataInteira() << endl;
    cout << "Livro: " << livro->getTitulo() << endl;
}


int ItemReserva::getNroDoItem() const { return nroDoItem; }


Data ItemReserva::getDataDeRetirada() const { return  dataDeRetirada; }


Livro* ItemReserva::getLivro() const {

        return livro; // 

 }


void ItemReserva::setNroDoItem( const int novoNroDoItem) { this -> nroDoItem = novoNroDoItem; }


void ItemReserva::setDataDeRetirada(const Data& novaDataDeRetirada) { this -> dataDeRetirada = novaDataDeRetirada; }


void ItemReserva::setLivro(Livro* novoLivro) { this -> livro = novoLivro; }