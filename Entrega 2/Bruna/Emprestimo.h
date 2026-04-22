#ifndef EMPRESTIMO_H
#define EMPRESTIMO_H

class Emprestimo {
    private:
        int dataDeRetirada;
        int dataPrevistaDevolucao;
        int dataDevolucao;
        int status;

    public:
        Emprestimo();
        void imprimirEmprestimo();

        int getDataDeRetirada();
        int getDataPrevistaDevolucao();
        int getDataDevolucao();
        int getStatus();

        void setDataDeRetirada(int novaDataDeRetirada);
        void setDataPrevistaDevolucao(int novaDataPrevistaDevolucao);
        void setDataDevolucao(int novaDataDevolucao);
        void setStatus(int novoStatus);
        
};

#endif