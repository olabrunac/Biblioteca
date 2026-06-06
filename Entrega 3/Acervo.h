#ifndef ACERVO_H
#define ACERVO_H

#include "Livro.h"
#include <vector>

using std::vector;

class Acervo {
    private:
        vector<Livro*> acervo; // agora é um vetor de ponteiros :)

    public:
        Acervo();
        ~Acervo();  //Destrutor
        
        void acrescentarLivro(Livro* novoLivro);
        void removerDoAcervo(Livro* removerLivro);

        void listarTodos() const;
        void listarLivrosDisponiveis() const;
        void listarLivrosIndisponiveis() const;

};

#endif