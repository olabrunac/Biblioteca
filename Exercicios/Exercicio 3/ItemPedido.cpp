#include "ItemPedido.h"

#include <iostream>


using std::cout;
using std::endl;


ItemPedido::ItemPedido() {}

void ItemPedido::setNome(string n) { this -> nomeProduto = n; }

string ItemPedido::getNome() const {return nomeProduto; }

void ItemPedido::setPreco(float p) { this -> precoUnitario = p; }

float ItemPedido::getPreco() const { return precoUnitario; }

void ItemPedido::setQuantidade(int q) { this -> quantidade = q; }

int ItemPedido::getQuantidade() const { return quantidade; }