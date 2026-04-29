#ifndef ACERVO_H
#define ACERVO_H

#include "Livro.h"
#include <vector>

using std::vector;

class Acervo {
    private:
        vector<Livro> acervo;

    public:
        Acervo();
        
        void acrescentarLivro(const Livro& novoLivro);
        void removerDoAcervo(const Livro& removerLivro);

        void listarTodos() const;
        void listarLivrosDisponiveis() const;
        void listarLivrosIndisponiveis() const;

};

#endif