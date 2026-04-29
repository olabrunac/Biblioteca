#include "Emprestimo.h"
#include "Livro.h"
#include "ItemEmprestimo.h"
#include "ExemplarLivro.h"
#include <iostream>

using std::cout;
using std::endl;
using std::iterator;

Emprestimo::Emprestimo(): usuario(nullptr), status(0) {}         //cria o emprestimo com um ponteiro que nao associa a nenhum usuário

void Emprestimo::imprimirEmprestimo() {
    cout << "+++ Detalhes Emprestimo +++" << endl;
    if (usuario != nullptr) {
        cout << "Usuario: ";
        usuario->imprimirUsuario();
    } else {
        cout << "Usuario: (Nao especificado)" << endl;           // caso base
    }
    cout << "Status do Emprestimo: " << toString(status) << endl;
    cout << "Livros Emprestados:" << endl;
    for (vector<ItemEmprestimo>::const_iterator temp = itens.cbegin(); temp != itens.cend(); ++temp) { // iterador aponta para os elementos do vetor, começa no primeiro elemento graças ao itens.cbegin() e percorre temp++ até o itens.cend()
        temp -> imprimirItemEmprestimo();
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

StatusEmprestimo Emprestimo::getStatus() const { return status; }

Usuario* Emprestimo::getUsuario() const {return usuario;}

const vector<ItemEmprestimo>& Emprestimo::getItens() const { return itens; }

void Emprestimo::setDataDeRetirada(int novaDataDeRetirada) { this -> dataDeRetirada = novaDataDeRetirada; }

void Emprestimo::setDataPrevistaDevolucao(int novaDataPrevistaDevolucao) { this -> dataPrevistaDevolucao = novaDataPrevistaDevolucao; }

void Emprestimo::setDataDevolucao(int novaDataDevolucao) { this -> dataDevolucao = novaDataDevolucao; }

void Emprestimo::setStatus(StatusEmprestimo novoStatus) { this -> status = novoStatus;} 

void Emprestimo::setUsuario(Usuario* novoUsuario) {this-> usuario = novoUsuario;}

void Emprestimo::setItens(Livro& novoLivro){
    ItemEmprestimo ItemAdicionado;                                      // cria um objeto em branco do tipo ItemEmprestimo
    ExemplarLivro* Exemplar = novoLivro.getExemplarDisponivel();        // procura qual cópia está disponivel e retorna um ponteiro para ele
    if (Exemplar != nullptr) {  
        ItemAdicionado.setExemplar(Exemplar);                           //vai vincular o livro ao ponteiro do exemplar disponivel
        Exemplar->setStatus(StatusEmprestimo::EMPRESTADO);          // altera o status desse exemplar
        itens.push_back(ItemAdicionado);                                //pega o registro do exemplar e o adiciona no final do vetor itens
    } else {
        cout << "Erro: Nenhum exemplar disponivel para o livro." << endl;    // caso base
    }
}

