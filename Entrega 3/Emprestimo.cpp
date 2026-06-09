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


Emprestimo::Emprestimo(Usuario* novoUsuario, const Data& novaDataDeRetirada, const Data& novaDataPrevistaDevolucao, const Data& novaDataDevolucao, int novoStatus)
    :usuario(novoUsuario), dataDeRetirada(novaDataDeRetirada), dataPrevistaDevolucao(novaDataPrevistaDevolucao), dataDevolucao(novaDataDevolucao), status(novoStatus) {}


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
        usuario->imprimirUsuario(); 
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


Data Emprestimo::getDataDeRetirada() const { return dataDeRetirada; }


Data Emprestimo::getDataPrevistaDevolucao() const {
    
        Data dataBase; // Data de retirada, usada para o calculo

        dataBase.setData(dataDeRetirada.getDataInteira());

        Data DataPrevistaDevolução = dataBase + 7; //Utiliza a sobrecarga de operadores da classe Data para 7 na data de foi realizadaa  retirada.

        return DataPrevistaDevolução;
    
}


Data Emprestimo::getDataDevolucao() const { return dataDevolucao; }


int Emprestimo::getStatus() const { return status; }


Usuario* Emprestimo::getUsuario() const {return usuario; }


const vector<ItemEmprestimo*>& Emprestimo::getItens() const { return itens; }


/*Os setters de data utilizam o próprio construtor da classe data, o que
possibilita receber um inteiro, testar, tratar erro, e atribui-la */

void Emprestimo::setDataDeRetirada(Data novaDataDeRetirada)
{
    this -> dataDeRetirada = Data(novaDataDeRetirada);
}
    

void Emprestimo::setDataPrevistaDevolucao(Data novaDataPrevistaDevolucao) { 

    this -> dataPrevistaDevolucao = Data(novaDataPrevistaDevolucao); 

} 


void Emprestimo::setDataDevolucao(Data novaDataDevolucao) { 
    
    this -> dataDevolucao = Data(novaDataDevolucao); 

} 


void Emprestimo::setStatus(int novoStatus) { this -> status = novoStatus;} 


void Emprestimo::setUsuario(Usuario* novoUsuario) {this-> usuario = novoUsuario;}


void Emprestimo::setItens(Livro& novoLivro){                            
    ItemEmprestimo ItemAdicionado;
    ExemplarLivro* Exemplar = novoLivro.getExemplarDisponivel();
    if (Exemplar != nullptr) {
        ItemEmprestimo* ItemAdicionado = new ItemEmprestimo();
        ItemAdicionado->setExemplar(Exemplar);
        Exemplar->setStatus(StatusEmprestimo::EMPRESTADO);
        itens.push_back(ItemAdicionado);
    } else {
        cout << "Erro: Nenhum exemplar disponivel para o livro." << endl;
    }
}
