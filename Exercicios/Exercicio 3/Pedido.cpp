#include "Pedido.h"

#include <iostream>

using std::cout;
using std::endl;

Pedido::Pedido() {}
Pedido::Pedido(int id, string d, vector<ItemPedido> i, Situacao& s) : ID(id), descricao(d), itens(i), situacao(s) {}

void Pedido::adicionarItem(const ItemPedido& novoItem) { itens.push_back(novoItem); }

float Pedido::calcularValorTotal() {
    float soma = 0.0;
    for (const ItemPedido& item : itens) {
        soma += item.getQuantidade() * item.getPreco();
    }
    this -> valor = soma;
    return soma;
}

void Pedido::listarItens() const {
    for (const ItemPedido& item : itens) {
        cout << "----- ITEM -----" << endl;
        cout << item.getNome() << endl;
        cout << "Quantidade: " << item.getQuantidade() << endl;
        cout << "Preco unitário: R$ " << item.getPreco() << endl;
    }
}

void Pedido::exibirDados() const {
    //cout << endl << "---------------------------------" << endl;
    cout << endl << "----- Detalhes do pedido -----"<< endl;
    cout << "ID: " << ID << endl;
    cout << "Descricao: " << descricao << endl;
    cout << "Valor total: R$ " << valor << endl;
}

void Pedido::setID(int id) { this -> ID = id; }

int Pedido::getID() const { return ID; }

void Pedido::setDescricao(const string d) { this -> descricao = d; }

string Pedido::getDescricao() const { return descricao; }

void Pedido::setValor(float v) { this -> valor = v; }

float Pedido::getValor() const { return valor; }

void Pedido::setItens(const vector<ItemPedido>& novosItens) { this -> itens = novosItens; }

vector<ItemPedido> Pedido::getItens() const { return itens; }

void Pedido::setSituacao(const Situacao& novaSituacao) { this -> situacao = novaSituacao; }

Situacao Pedido::getSituacao() const { return situacao; }