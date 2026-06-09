#include "Acervo.h"
#include "Livro.h"
#include <iostream>

using std::cout;
using std::endl;
using std::iterator;

Acervo::Acervo() {}

Acervo::Acervo(initializer_list<Livro*> listaLivros) {                  //permite colocar 1 ou mais livros na criação do acervo
    for (initializer_list<Livro*>::const_iterator temp = listaLivros.begin(); temp != listaLivros.end(); ++temp) {
        acervo.push_back(*temp);
    }
}


Acervo::~Acervo() {                                                     //destrutor com os ponteiros e etc
    for (vector<Livro*>::iterator temp = acervo.begin(); temp != acervo.end(); ++temp) {
        delete *temp;  //apaga na memória
    }
    acervo.clear();
}


void Acervo::acrescentarLivro(Livro* novoLivro) {
    acervo.push_back(novoLivro);
    cout << "1 livro foi adicionado ao acervo!" << endl;
}


// permite colocar um vetor de livros no acervo de uma vez só 
void Acervo::acrescentarLivro(initializer_list<Livro*> listaLivros) {
    for (initializer_list<Livro*>::const_iterator temp = listaLivros.begin(); temp != listaLivros.end(); ++temp) {
        acervo.push_back(*temp);
    }
    cout << listaLivros.size() << " livros foram adicionados ao acervo!" << endl;
}


void Acervo::removerDoAcervo(Livro* removerLivro) {
    cout << " <<<<< REMOVENDO O LIVRO >>>>> " << endl;
    for (vector<Livro*>::iterator temp = acervo.begin(); temp != acervo.end(); ++temp){
        if((*temp)->getCodigo() == removerLivro->getCodigo()){       //funciona com ponteiro
            acervo.erase(temp);
            cout << "Livro removido do acervo com sucesso" << endl;
            return;
        }
    }
    cout <<"Livro nao encontrado no acervo" << endl;
}


void Acervo::listarTodos() const {                                  //atualizado com ponteiro
    cout << "===== TODOS OS LIVROS =====" << endl;
    for (vector<Livro*>::const_iterator temp = acervo.cbegin(); temp != acervo.cend(); ++temp) { 
        cout << (*temp)->getTitulo() << ", "                        // (*temp) devolve o ponteiro de livro
        << (*temp)->getStatusAgora() << endl;
    }
}


void Acervo::listarLivrosDisponiveis() const {
    cout << "+++++ TODOS OS LIVROS DISPONIVEIS +++++" << endl;
    for (vector<Livro*>::const_iterator temp = acervo.cbegin(); temp != acervo.cend(); ++temp) {
        if ((*temp)->estaDisponivel()) {
            cout << "Titulo: " << (*temp)->getTitulo() << " | Codigo: " << (*temp)->getCodigo() << endl;
        }
    }
}


void Acervo::listarLivrosIndisponiveis() const {
    cout << "----- TODOS OS LIVROS INDISPONIVEIS -----" << endl;
    for (vector<Livro*>::const_iterator temp = acervo.cbegin(); temp != acervo.cend(); ++temp) {
        if (!(*temp)->estaDisponivel()) {
            cout << "Titulo: " << (*temp)->getTitulo() << " | Codigo: " << (*temp)->getCodigo() << endl;
        }
    }
}