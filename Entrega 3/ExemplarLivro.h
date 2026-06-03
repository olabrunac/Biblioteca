#ifndef EXEMPLARLIVRO_H
#define EXEMPLARLIVRO_H

class Livro;

#include "StatusEmprestimo.h"
#include "LocalizacaoPrateleira.h"


class ExemplarLivro {
    private:
        int nroExemplar;
        StatusEmprestimo status;
        Livro* livro;
        //Localizacao
        
    public:
        ExemplarLivro();
        void imprimirExemplarLivro();

        int getNroExemplar() const;
        StatusEmprestimo getStatus()const ;//Precisei adicionar o const para o Acervo
        Livro* getLivro() const;

        void setNroExemplar(int novoNroExemplar);
        void setStatus(StatusEmprestimo novoStatusEmprestimo);
        void setLivro(Livro* Nlivro);

};

#endif