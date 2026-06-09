#include "Acervo.h"
#include "Livro.h"
#include <iostream>

using std::cout;
using std::endl;
using std::iterator;

Acervo::Acervo() {}

Acervo::Acervo(initializer_list<Livro*> listaLivros) {
    for (auto temp : listaLivros) {
        acervo.push_back(temp);
    }
}


Acervo::~Acervo() {
    // O destrutor é responsável por liberar a memória de todos os objetos Livro* no acervo.
    for (auto temp : acervo) {
        delete temp;
    }
    acervo.clear();
}


void Acervo::acrescentarLivro(Livro* novoLivro) {
    acervo.push_back(novoLivro);
    cout << "1 livro foi adicionado ao acervo!" << endl;
}


void Acervo::acrescentarLivro(initializer_list<Livro*> listaLivros) { // Sobrecarga para adicionar múltiplos livros.
    for (auto temp : listaLivros) {
        acervo.push_back(temp);
    }
    cout << listaLivros.size() << " livros foram adicionados ao acervo!" << endl;
}

Acervo& Acervo::operator+=(Livro* novoLivro) {
    this->acrescentarLivro(novoLivro);
    return *this;
}


void Acervo::removerDoAcervo(Livro* removerLivro) {
    cout << " <<<<< REMOVENDO O LIVRO >>>>> " << endl;
    for (auto it = acervo.begin(); it != acervo.end(); ++it){
        // Compara o endereço de memória para garantir que o objeto exato seja removido.
        if(*it == removerLivro){
            delete *it; // Libera a memória do objeto Livro antes de remover o ponteiro do vetor.
            acervo.erase(it);
            cout << "Livro removido do acervo com sucesso" << endl;
            return;
        }
    }
    cout <<"Livro nao encontrado no acervo" << endl;
}


void Acervo::listarTodos() const {
    cout << "===== TODOS OS LIVROS =====" << endl;
    for (auto temp : acervo) { 
        cout << temp->getTitulo() << ", "
        << temp->getStatusAgora() << endl;
    }
}


void Acervo::listarLivrosDisponiveis() const {
    cout << "+++++ TODOS OS LIVROS DISPONIVEIS +++++" << endl;
    for (auto temp : acervo) {
        if (temp->estaDisponivel()) {
            cout << "Titulo: " << temp->getTitulo() << " | Codigo: " << temp->getCodigo() << endl;
        }
    }
}


void Acervo::listarLivrosIndisponiveis() const {
    cout << "----- TODOS OS LIVROS INDISPONIVEIS -----" << endl;
    for (auto temp : acervo) {
        if (!temp->estaDisponivel()) {
            cout << "Titulo: " << temp->getTitulo() << " | Codigo: " << temp->getCodigo() << endl;
        }
    }
}