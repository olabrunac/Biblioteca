#include "Acervo.h"
#include "Livro.h"
#include <iostream>

using std::cout;
using std::endl;
using std::iterator;

Acervo::Acervo() {}

void Acervo::acrescentarLivro(const Livro& novoLivro) { acervo.push_back(novoLivro); }  // Cadastra um novo livro no fim do vetor acervo

void Acervo::removerDoAcervo(const Livro& removerLivro) {                               // recebe o const livro& que será removido por referencia constante, evita copiar o objeto inteiro na memória
    cout << " <<<<< REMOVENDO O LIVRO >>>>> " << endl;
    for (vector<Livro>::const_iterator temp = acervo.cbegin(); temp != acervo.cend(); temp ++){ // iterador constante aponta para os elementos do vetor, começa no primeiro elemento graças ao acervo.cbegin() e percorre temp++ até o acervo.cend()
        if(temp->getCodigo() == removerLivro.getCodigo()){                              // compara o código de cada livro do acervo com o código que vai ser removido
            acervo.erase(temp);                                                         // deleta se achar
            cout << "Livro removido com sucesso" << endl;
            return; 
        }
    }
    cout <<"Livro nao encontrado" << endl;
}

void Acervo::listarTodos() const {
    cout << "----- TODOS OS LIVROS -----" << endl;
    for (const Livro& temp: acervo) {                                                   // temporariamente coloca cada item do acervo no temp e executa o código dentro do for
        cout << temp.getTitulo() << ", "                                                // & (referencia) impede que o programa crie cópia do livro na memória em toda volta do laço
        << temp.getStatusAgora() << endl;                                               // const garante uqe o livro temp nao vai ser modificado acidentalmente
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
        if (!temp.estaDisponivel()) {                                                    // !temp inverte o resultado obtido pelo estádisponivel, nesse caso se um livro está indisponivel vai retornar true e entrar no if
            cout << "Titulo: " << temp.getTitulo() << " | Codigo: " << temp.getCodigo() << endl;
        }
    }
}