#include "Reserva.h"
#include <iostream>

using std::cout;
using std::endl;

Reserva::Reserva() : ID(0), usuario(nullptr) {}


Reserva::Reserva(int novoID, const Data& novaDataRealizacao, Usuario* novoUsuario)
    : ID(novoID), dataRealizacao(novaDataRealizacao), usuario(novoUsuario) {}


Reserva::Reserva(int novoID, const Data& novaDataRealizacao, Usuario* novoUsuario, const vector<ItemReserva*>& itensIn)
    : ID(novoID), dataRealizacao(novaDataRealizacao), usuario(novoUsuario), itens(itensIn) {}


Reserva::~Reserva() {
    for (vector<ItemReserva*>::iterator temp = itens.begin(); temp != itens.end(); ++temp) {
         delete *temp;
         cout << "-Destruindo a reserva ID: " << this->ID << " e liberando a memória" << endl;
    }
    itens.clear();
}


void Reserva::adicionarItem(ItemReserva* novoItem) {
    itens.push_back(novoItem);
}


void Reserva::imprimirReserva() const {
    cout << "Reserva ID: " << ID << endl;
    cout << "Data da Reserva: " << dataRealizacao.getDataInteira() << endl; //Imprime a data no formato AAAAMMDD
    if (usuario != nullptr) {
        cout << "Reservado por: ";
        usuario->imprimirUsuario(); // polimorfismo aqui
    }
    for (vector<ItemReserva*>::const_iterator temp = itens.cbegin(); temp != itens.cend(); ++temp) {
        (*temp)->imprimirItemReserva();
    }
}


int Reserva::getID() const { return ID; }


Data Reserva::getDataRealizacao() const { return dataRealizacao; }


Usuario* Reserva::getUsuario() const { return usuario; }


const vector<ItemReserva*>& Reserva::getItens() const { return itens; }

bool Reserva::possuiLivro(const Livro* livroBuscado) const {
    for (vector<ItemReserva*>::const_iterator temp = itens.begin(); temp != itens.end(); ++temp) {
        if ((*temp)->getLivro() == livroBuscado) {
            return true;
        }
    }
    return false;
}


void Reserva::setID(int novoID) { this -> ID = novoID; }


void Reserva::setDataRealizacao(Data& novaDataReserva) { this -> dataRealizacao = novaDataReserva; }


void Reserva::setUsuario(Usuario* novoUsuario) { this->usuario = novoUsuario; }