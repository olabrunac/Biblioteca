#include "Pedido.h"
#include "ItemPedido.h"
#include <iostream>

using std::cout;
using std::endl;

int main () {

    ItemPedido pao;
    pao.setNome ("Pao Frances Unidade");
    pao.setPreco (0.80);
    pao.setQuantidade (4);

    ItemPedido leite;
    leite.setNome ("Leite Ninho Integral 1L");
    leite.setPreco (6.50);
    leite.setQuantidade (1);

    vector<ItemPedido> itensP1;
    itensP1.push_back(pao);
    itensP1.push_back(leite);

    Situacao situacaoP1(Situacao::ABERTO);

    Pedido p1(111, "Cafe da manha", itensP1, situacaoP1);

    p1.calcularValorTotal();
    p1.exibirDados();

//-----------------------------------------------

    ItemPedido arroz;
    arroz.setNome ("Arroz Branco Camil tipo 1");
    arroz.setPreco (6.90);
    arroz.setQuantidade (1);

    ItemPedido feijao;
    feijao.setNome ("Feijao Carioca 1kg");
    feijao.setPreco (9.80);
    feijao.setQuantidade (1);

    vector<ItemPedido> itensP2;
    itensP2.push_back(arroz);
    itensP2.push_back(feijao);

    Situacao situacaoP2 (Situacao::ABERTO);

    Pedido p2(222, "Almoco", itensP2, situacaoP2);

    p2.calcularValorTotal();
    p2.exibirDados();

//-----------------------------------------

    cout << endl << "- Mudando a situação dos pedidos -" << endl;
    
    p1.setSituacao(Situacao::FINALIZADO);
    p2.setSituacao(Situacao::CANCELADO);

    p1.exibirDados();
    p1.listarItens();
    p2.exibirDados();
    p2.listarItens();
    cout << endl;
    return 0;
};