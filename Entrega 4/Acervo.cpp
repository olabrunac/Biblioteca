#include "Acervo.h"
#include "Livro.h"
#include <iostream>
#include "Erros.h"

using std::cout;
using std::endl;

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


void Acervo::removerDoAcervo(Livro* removerLivro) {
    cout << " <<<<< REMOVENDO O LIVRO >>>>> " << endl;
    for (auto temp = acervo.begin(); temp != acervo.end(); ++temp){
        // Compara o endereço de memória para garantir que o objeto exato seja removido.
        if(*temp == removerLivro){
            delete *temp; // Libera a memória do objeto Livro antes de remover o ponteiro do vetor.
            acervo.erase(temp);
            cout << "Livro removido do acervo com sucesso" << endl;
            return;
        }
    }
    throw ErroLivroNaoExisteAcervo();
}


void Acervo::listarTodos() const {
    cout << "===== TODOS OS LIVROS =====" << endl;
    for (auto temp : acervo) {
        cout << "Codigo: " << temp->getCodigo() << " | Titulo: " << temp->getTitulo() << ", "
        << temp->getStatusAgora() << endl;
    }
}