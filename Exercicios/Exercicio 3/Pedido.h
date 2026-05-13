#ifndef PEDIDO_H
#define PEDIDO_H

#include "ItemPedido.h"
#include "Situacao.h"

#include <string>
#include <vector>

using std::string;
using std::vector;

class Pedido {
    private:
    int ID;
    string descricao;
    float valor;
    vector<ItemPedido> itens;
    Situacao situacao;


    public:
    Pedido();
    Pedido(int id, string d, vector<ItemPedido> i, Situacao& s);

    void adicionarItem(const ItemPedido& novoItem);
    float calcularValorTotal();
    void listarItens() const;
    void exibirDados() const;

    void setID(int id);
    void setDescricao(const string d);
    void setValor(float v);
    void setItens(const vector<ItemPedido>& novosItens);
    void setSituacao(const Situacao& novaSituacao);

    int getID() const;
    string getDescricao() const;
    float getValor() const;
    vector<ItemPedido> getItens() const;
    Situacao getSituacao() const;
};

#endif