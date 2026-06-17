#ifndef ACERVO_H
#define ACERVO_H

#include "Livro.h"
#include <vector>
#include <initializer_list> //para adicionar varios livros no acervo de uma vez sem ter muitos construtores

using std::vector;
using std::initializer_list;

class Acervo {
    private:
        vector<Livro*> acervo; // agora é um vetor de ponteiros :)

    public:
        Acervo();
        Acervo(initializer_list<Livro*> listaLivros);
        ~Acervo();  //Destrutor
        
        void acrescentarLivro(Livro* novoLivro);
        void acrescentarLivro(initializer_list<Livro*> listaLivros); //sobrecarga de metodos
        void removerDoAcervo(Livro* removerLivro);

        void listarTodos() const;

        const vector<Livro*>& getLivros() const { return acervo; }

};

#endif