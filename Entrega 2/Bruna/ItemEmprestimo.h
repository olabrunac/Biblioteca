#ifndef ITEMEMPRESTIMO_H
#define ITEMEMPRESTIMO_H

class ItemEmprestimo {
    private:
        int dataParaDevolucao;
        int dataQueFoiDevolvido;
        
    public:
        ItemEmprestimo();
        void imprimirItemEmprestimo();

        int getDataParaDevolucao();
        int getDataQueFoiDevolvido();

        void setDataParaDevolucao(int novaDataParaDevolucao);
        void setDataQueFoiDevolvido(int novaDataQueFoiDevolvido);
};

#endif