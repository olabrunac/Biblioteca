#include "Acervo.h"
#include "Livro.h"
#include <iostream>

using std::cout;
using std::endl;
using std::iterator;

Acervo::Acervo() {}

Acervo::~Acervo() {     //destrutor com os ponteiros e etc
    for (vector<Livro*>::iterator temp = acervo.begin(); temp != acervo.end(); ++temp) {
        delete *temp;  //apaga na memória
    }
    acervo.clear();
}

void Acervo::acrescentarLivro(Livro* novoLivro) { acervo.push_back(novoLivro); }

void Acervo::removerDoAcervo(Livro* removerLivro) {
    cout << " <<<<< REMOVENDO O LIVRO >>>>> " << endl;
    for (vector<Livro*>::iterator temp = acervo.begin(); temp != acervo.end(); ++temp){
        if((*temp)->getCodigo() == removerLivro->getCodigo()){      //funciona com ponteiro
            acervo.erase(temp);
            cout << "Livro removido do acervo com sucesso" << endl;
            return;
        }
    }
    cout <<"Livro nao encontrado no acervo" << endl;
}

void Acervo::listarTodos() const {      //atualizado com ponteiro
    cout << "----- TODOS OS LIVROS -----" << endl;
    for (vector<Livro*>::const_iterator temp = acervo.cbegin(); temp != acervo.cend(); ++temp) { 
        cout << (*temp)->getTitulo() << ", "  // (*temp) devolve o ponteiro de livro
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