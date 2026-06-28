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
    for (auto temp : itens) {
         delete temp;
    }
    itens.clear();
}


void Reserva::imprimirReserva() const {
    cout << "Reserva ID: " << ID << endl;
    cout << "Data da Reserva: "; dataRealizacao.imprimirData(); cout << endl;
    if (usuario != nullptr) {
        usuario->imprimirUsuario(); // polimorfismo aqui
    }
    for (auto temp : itens) {
        temp->imprimirItemReserva();
    }
}


void Reserva::adicionarItem(ItemReserva* novoItem) {
    itens.push_back(novoItem);
}


//-------------------- sets e gets --------------------


int Reserva::getID() const { return ID; }


Data Reserva::getDataRealizacao() const { return dataRealizacao; }


Usuario* Reserva::getUsuario() const { return usuario; }


const vector<ItemReserva*>& Reserva::getItens() const { 
    return itens; 
}


ItemReserva* Reserva::getItemPorLivro(Livro* livro) const {
    for (ItemReserva* item : itens)
        if (item->getLivro() == livro){
        return item;
        }
    return nullptr;
}


void Reserva::setID(int novoID) { this -> ID = novoID; }


void Reserva::setDataRealizacao(Data& novaDataReserva) { this -> dataRealizacao = novaDataReserva; }


void Reserva::setUsuario(Usuario* novoUsuario) { this->usuario = novoUsuario; }


bool Reserva::possuiLivro(const Livro* livroBuscado) const {
    for (auto temp : itens) {
        if (temp->getLivro() == livroBuscado) {
            return true;
        }
    }
    return false;
}


bool Reserva::removerItemPorLivro(int codigoLivro) {
    for (auto temp = itens.begin(); temp != itens.end(); ++temp) {
        if ((*temp)->getLivro()->getCodigo() == codigoLivro) {
            cout << "Removendo item da reserva: " << (*temp)->getLivro()->getTitulo() << endl;
            delete *temp; // Libera a memória do ItemReserva
            itens.erase(temp); // Remove o ponteiro do vetor
            return true;
        }
    }
    return false;
}