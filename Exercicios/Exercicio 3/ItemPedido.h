#ifndef ITEMPEDIDO_H
#define ITEMPEDIDO_H
#include <string>

using std::string;

class ItemPedido {
    private:
    string nomeProduto;
    float precoUnitario;
    int quantidade;

    public:
    ItemPedido();

    void setNome(string n);
    void setPreco(float p);
    void setQuantidade(int q);

    string getNome() const;
    float getPreco() const;
    int getQuantidade() const;
};

#endif