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

        int getNroExemplar();
        StatusEmprestimo getStatus();

        void setNroExemplar(int novoNroExemplar);
        void setStatus(StatusEmprestimo& novoStatusEmprestimo);

};

#endif