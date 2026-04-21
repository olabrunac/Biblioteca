#ifndef EMPRESTIMO_H
#define EMPRESTIMO_H

class Emprestimo {
    private:
        int dataDeRetirada;
        int status;

    public:
        Emprestimo();
        void imprimirEmprestimo();

        int getDataDeRetirada();
        int getStatus();

        void setDataDeRetirada(int novaDataDeRetirada);
        void setStatus(int novoStatus);
};

#endif