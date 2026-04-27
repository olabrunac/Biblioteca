#ifndef EXEMPLARLIVRO_H
#define EXEMPLARLIVRO_H

#include "StatusEmprestimo.h"

class ExemplarLivro {
    private:
        int nroExemplar;
        StatusEmprestimo status;
        
    public:
        ExemplarLivro();
        void imprimirExemplarLivro();

        int getNroExemplar() const;
        StatusEmprestimo getStatus()const ;//Precisei adicionar o const para o Acervo

        void setNroExemplar(int novoNroExemplar);
        void setStatus(StatusEmprestimo novoStatusEmprestimo);

};

#endif