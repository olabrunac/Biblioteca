#include "Emprestimo.h"
#include "Livro.h"
#include "ItemEmprestimo.h"
#include "ExemplarLivro.h"
#include <iostream>

using std::cout;
using std::endl;

Emprestimo::Emprestimo(): usuario(nullptr), status(0) {}

void Emprestimo::imprimirEmprestimo() {
    cout << "+++ Detalhes Emprestimo +++" << endl;
    cout << "Usuario: ";
    usuario->imprimirUsuario();
    cout << "Livros Emprestados:" << endl;
    for (const auto& temp : itens) {
        temp.imprimirItemEmprestimo();
    }
}

void Emprestimo::adicionarItem(const ItemEmprestimo& novoItem) { //Apenas adiciona um item, o gerenciadorDeEmprestimos que lida com o status dos exemplares
    if (novoItem.getExemplar() != nullptr) {
        itens.push_back(novoItem);
    } else {
        cout << "Erro: item invalido." << endl;
    }
}

int Emprestimo::getDataDeRetirada() const { return dataDeRetirada; }

int Emprestimo::getDataPrevistaDevolucao() const { return dataPrevistaDevolucao; }

int Emprestimo::getDataDevolucao() const { return dataDevolucao; }

int Emprestimo::getStatus() const { return status; }

Usuario* Emprestimo::getUsuario() const {return usuario;}

const vector<ItemEmprestimo>& Emprestimo::getItens() const { return itens; }

void Emprestimo::setDataDeRetirada(int novaDataDeRetirada) { this -> dataDeRetirada = novaDataDeRetirada; }

void Emprestimo::setDataPrevistaDevolucao(int novaDataPrevistaDevolucao) { this -> dataPrevistaDevolucao = novaDataPrevistaDevolucao; }

void Emprestimo::setDataDevolucao(int novaDataDevolucao) { this -> dataDevolucao = novaDataDevolucao; }

void Emprestimo::setStatus(int novoStatus) { this -> status = novoStatus;} 

void Emprestimo::setUsuario(Usuario* novoUsuario) {this-> usuario = novoUsuario;}

void Emprestimo::setItens(Livro& novoLivro){
    ItemEmprestimo ItemAdicionado;
    ExemplarLivro* Exemplar = novoLivro.getExemplarDisponivel();
    ItemAdicionado.setExemplar(Exemplar);
    Exemplar->setStatus(StatusParaEmprestimo::EMPRESTADO);
    itens.push_back(ItemAdicionado);
}
