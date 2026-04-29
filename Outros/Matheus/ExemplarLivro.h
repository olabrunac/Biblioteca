#ifndef EXEMPLARLIVRO_H
#define EXEMPLARLIVRO_H

class Livro;

#include "StatusParaEmprestimo.h"



class ExemplarLivro {
    private:
        int nroExemplar;
        StatusParaEmprestimo status;
        Livro* livro;
        
    public:
        ExemplarLivro();
        void imprimirExemplarLivro();

        int getNroExemplar() const;
        StatusParaEmprestimo getStatus()const ;//Precisei adicionar o const para o Acervo
        Livro* getLivro() const;

        void setNroExemplar(int novoNroExemplar);
        void setStatus(StatusParaEmprestimo novoStatusEmprestimo);
        void setLivro(Livro* Nlivro);

};

#endif