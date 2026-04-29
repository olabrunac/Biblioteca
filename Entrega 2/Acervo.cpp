#include "Acervo.h"
#include "Livro.h"
#include <iostream>

using std::cout;
using std::endl;
using std::iterator;

Acervo::Acervo() {}

void Acervo::acrescentarLivro(const Livro& novoLivro) { acervo.push_back(novoLivro); }

void Acervo::removerDoAcervo(const Livro& removerLivro) {
    cout << " <<<<< REMOVENDO O LIVRO >>>>> " << endl;
    for (vector<Livro>::const_iterator temp = acervo.cbegin(); temp != acervo.cend(); temp ++){
        if(temp->getCodigo() == removerLivro.getCodigo()){
            acervo.erase(temp);
            cout << "Livro removido com sucesso" << endl;
            return;
        }
    }
    cout <<"Livro nao encontrado" << endl;
}

void Acervo::listarTodos() const {
    cout << "----- TODOS OS LIVROS -----" << endl;
    for (const Livro& temp: acervo) { 
        cout << temp.getTitulo() << ", "
        << temp.getStatusAgora() << endl;
    }
}

void Acervo::listarLivrosDisponiveis() const {
    cout << "+++++ TODOS OS LIVROS DISPONIVEIS +++++" << endl;
    for (const Livro& temp: acervo) {
        if (temp.estaDisponivel()) {
            cout << "Titulo: " << temp.getTitulo() << " | Codigo: " << temp.getCodigo() << endl;
        }
    }
}

void Acervo::listarLivrosIndisponiveis() const {
    cout << "----- TODOS OS LIVROS INDISPONIVEIS -----" << endl;
    for (const Livro& temp : acervo ) {
        if (!temp.estaDisponivel()) {
            cout << "Titulo: " << temp.getTitulo() << " | Codigo: " << temp.getCodigo() << endl;
        }
    }
}