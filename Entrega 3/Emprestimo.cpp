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


Emprestimo::Emprestimo(Usuario* novoUsuario, const Data& novaDataEmprestimo, const Data& novaDataPrevistaDevolucao, const Data& novaDataDevolucao, int novoStatus)
    :usuario(novoUsuario), dataEmprestimo(novaDataEmprestimo), dataPrevistaDevolucao(novaDataPrevistaDevolucao), dataDevolucao(novaDataDevolucao), status(novoStatus) {}


Emprestimo::~Emprestimo() {
    for(vector<ItemEmprestimo*>::iterator temp = itens.begin(); temp != itens.end(); ++temp) {
        delete *temp;
    }
    itens.clear();
}


void Emprestimo::imprimirEmprestimo() {                                  
    cout << endl << "+++ Detalhes Emprestimo +++" << endl;                       
    if (usuario != nullptr) {
        cout << "Tipo do usuario: "; 
        usuario->imprimirUsuario();         //polimorfismo
    } else {
        cout << "Tipo do usuario: (Nao especificado)" << endl;
    }
    cout << "Livros Emprestados:" << endl;
    for (vector<ItemEmprestimo*>::const_iterator temp = itens.begin(); temp != itens.end(); ++temp) {
        (*temp)->imprimirItemEmprestimo();
    }
}


void Emprestimo::adicionarItem(ItemEmprestimo* novoItem) {
    if (novoItem->getExemplar() != nullptr) {
        itens.push_back(novoItem);
    } else {
        cout << "Erro: item invalido." << endl;
    }
}


Data Emprestimo::getDataEmprestimo() const { return dataEmprestimo; }


Data Emprestimo::getDataPrevistaDevolucao() const { return dataPrevistaDevolucao; }


Data Emprestimo::getDataDevolucao() const { return dataDevolucao; }


int Emprestimo::getStatus() const { return status; }


Usuario* Emprestimo::getUsuario() const {return usuario; }


const vector<ItemEmprestimo*>& Emprestimo::getItens() const { return itens; }


/*Os setters de data utilizam o próprio construtor da classe data, o que
possibilita receber um inteiro, testar, tratar erro, e atribui-la */

void Emprestimo::setDataEmprestimo(Data novaDataEmprestimo) { this -> dataEmprestimo = Data(novaDataEmprestimo); }
    

void Emprestimo::setDataPrevistaDevolucao(Data novaDataPrevistaDevolucao) { this -> dataPrevistaDevolucao = Data(novaDataPrevistaDevolucao); } 


void Emprestimo::setDataDevolucao(Data novaDataDevolucao) { this -> dataDevolucao = Data(novaDataDevolucao); } 


void Emprestimo::setStatus(int novoStatus) { this -> status = novoStatus;} 


void Emprestimo::setUsuario(Usuario* novoUsuario) {this-> usuario = novoUsuario;}


void Emprestimo::setItens(Livro& novoLivro){                            
    ExemplarLivro* Exemplar = novoLivro.getExemplarDisponivel();
    if (Exemplar != nullptr) {
        ItemEmprestimo* novoItem = new ItemEmprestimo();
        novoItem->setExemplar(Exemplar);
        Exemplar->setStatus(StatusEmprestimo::EMPRESTADO);
        itens.push_back(novoItem);
    } else {
        cout << "Erro: Nenhum exemplar disponivel para o livro." << endl;
    }
}
