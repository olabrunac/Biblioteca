#include "Emprestimo.h"
#include "Livro.h"
#include "ItemEmprestimo.h"
#include "ExemplarLivro.h"
#include "StatusEmprestimo.h"  
#include <iostream>

using std::cout;
using std::endl;
using std::iterator;

Emprestimo::Emprestimo(): usuario(nullptr), status(0) {}

void Emprestimo::imprimirEmprestimo() {                                  
    cout << "+++ Detalhes Emprestimo +++" << endl;                       
    if (usuario != nullptr) {
        cout << "Usuario: "; 
        usuario->imprimirUsuario(); 
    } else {
        cout << "Usuario: (Nao especificado)" << endl;
    }
    cout << "Livros Emprestados:" << endl;
    for (vector<ItemEmprestimo>::const_iterator temp = itens.cbegin(); temp != itens.cend(); ++temp) {
        temp -> imprimirItemEmprestimo();
    }
}

void Emprestimo::adicionarItem(const ItemEmprestimo& novoItem) {
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

Usuario* Emprestimo::getUsuario() const {return usuario; }

const vector<ItemEmprestimo>& Emprestimo::getItens() const { return itens; }

void Emprestimo::setDataDeRetirada(int novaDataDeRetirada) { this -> dataDeRetirada = novaDataDeRetirada; } 

void Emprestimo::setDataPrevistaDevolucao(int novaDataPrevistaDevolucao) { this -> dataPrevistaDevolucao = novaDataPrevistaDevolucao; } 

void Emprestimo::setDataDevolucao(int novaDataDevolucao) { this -> dataDevolucao = novaDataDevolucao; } 

void Emprestimo::setStatus(int novoStatus) { this -> status = novoStatus;} 

void Emprestimo::setUsuario(Usuario* novoUsuario) {this-> usuario = novoUsuario;}

void Emprestimo::setItens(Livro& novoLivro){                            
    ItemEmprestimo ItemAdicionado;
    ExemplarLivro* Exemplar = novoLivro.getExemplarDisponivel();
    if (Exemplar != nullptr) {
        ItemAdicionado.setExemplar(Exemplar);
        Exemplar->setStatus(StatusEmprestimo::EMPRESTADO);
        itens.push_back(ItemAdicionado);
    } else {
        cout << "Erro: Nenhum exemplar disponivel para o livro." << endl;
    }
}
