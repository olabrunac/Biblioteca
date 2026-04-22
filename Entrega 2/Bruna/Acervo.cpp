#include "Acervo.h"
#include "Livro.h"
#include <iostream>

using std::cout;
using std::endl;

Acervo::Acervo() {}

void Acervo::acrescentarLivro(const Livro& novoLivro) {
    acervo.push_back(novoLivro);
}

void Acervo::removerDoAcervo()  {} // Destrutor

void Acervo::listarTodos() const {
    for (const Livro& temp : acervo ) {
        cout << "----- TODOS OS LIVROS -----" << endl;
        cout << temp.getTitulo() << ", " << temp.getStatusAgora() << endl;
    }
}

void Acervo::listarLivrosDisponiveis() const {
    for (const Livro& temp : acervo ) {
        if (temp.getQuantidadeDeExemplares() > 0) {
            cout << "+++++ TODOS OS LIVROS DISPONIVEIS +++++" << endl;
            cout << "Titulo: " << temp.getTitulo() << " | Código: " << temp.getCodigo() << endl;
        }
    }
}

void Acervo::listarLivrosIndisponiveis() const {
    for (const Livro& temp : acervo ) {
        if (temp.getQuantidadeDeExemplares() == 0) {
            cout << "----- TODOS OS LIVROS INDISPONIVEIS -----" << endl;
            cout << "Titulo: " << temp.getTitulo() << " | Código: " << temp.getCodigo() << endl;
        }
    }
}