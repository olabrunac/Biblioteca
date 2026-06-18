#include "Emprestimo.h"
#include "Livro.h"
#include "ItemEmprestimo.h"
#include "ExemplarLivro.h"
#include "StatusEmprestimo.h"  
#include <iostream>

using std::cout;
using std::endl;


Emprestimo::Emprestimo(): usuario(nullptr), status(0) {}


Emprestimo::Emprestimo(Usuario* novoUsuario, const Data& novaDataDeRetirada, const Data& novaDataPrevistaDevolucao, const int novaDataDevolucao, int novoStatus)
    :usuario(novoUsuario), dataDeRetirada(novaDataDeRetirada), dataPrevistaDevolucao(novaDataPrevistaDevolucao), dataDevolucao(novaDataDevolucao), status(novoStatus) {}


Emprestimo::~Emprestimo() {
    for (auto temp : itens) {
        delete temp;
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
    for (auto temp : itens) {
        temp->imprimirItemEmprestimo();
    }
}


void Emprestimo::adicionarItem(ItemEmprestimo* novoItem) {
    if (novoItem->getExemplar() != nullptr) {
        itens.push_back(novoItem);
    } else {
        cout << "Erro: item invalido." << endl;
    }
}


Data Emprestimo::getDataDeRetirada() const { return dataDeRetirada; }


Data Emprestimo::getDataPrevistaDevolucao() const { return dataPrevistaDevolucao; }


int Emprestimo::getDataDevolucao() const { return dataDevolucao; }


int Emprestimo::getStatus() const { return status; }


Usuario* Emprestimo::getUsuario() const {return usuario; }


const vector<ItemEmprestimo*>& Emprestimo::getItens() const { return itens; }


void Emprestimo::setDataDeRetirada(Data novaDataDeRetirada) { this -> dataDeRetirada = Data(novaDataDeRetirada); }
    

void Emprestimo::setDataPrevistaDevolucao(Data novaDataPrevistaDevolucao) { this -> dataPrevistaDevolucao = Data(novaDataPrevistaDevolucao); } 


void Emprestimo::setDataDevolucao(int novaDataDevolucao) { this -> dataDevolucao = int(novaDataDevolucao); } 


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


bool Emprestimo::possuiLivro(Livro* livroTeste) const {

      for (const auto& temp : itens){
        Livro* livro = temp->getLivro();

        if (livro && livroTeste && *livro == *livroTeste) {
            return true;
        }
    }
    cout << "Não possui o livro no emprestimo" << endl;
    return false;
}
