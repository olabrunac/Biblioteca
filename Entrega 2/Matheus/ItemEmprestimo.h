#ifndef ITEMEMPRESTIMO_H
#define ITEMEMPRESTIMO_H

#include "ExemplarLivro.h"

class ItemEmprestimo {
    private:
        ExemplarLivro* exemplar;
        int dataParaDevolucao;
        int dataQueFoiDevolvido;
        
    public:
        
        ItemEmprestimo();

        void imprimirItemEmprestimo();
        ExemplarLivro getExemplar() const;

        int getDataParaDevolucao();
        int getDataQueFoiDevolvido();

        void setExemplar(ExemplarLivro* novoExemplar);
        void setDataParaDevolucao(int novaDataParaDevolucao);
        void setDataQueFoiDevolvido(int novaDataQueFoiDevolvido);
};

#endif