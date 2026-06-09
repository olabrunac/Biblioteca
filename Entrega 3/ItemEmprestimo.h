#ifndef ITEMEMPRESTIMO_H
#define ITEMEMPRESTIMO_H

#include "ExemplarLivro.h"
#include "Data.h"

class ItemEmprestimo {
    private:
        ExemplarLivro* exemplar;
        Data dataParaDevolucao;
        int dataQueFoiDevolvido;
    public:
        
        ItemEmprestimo();

        void imprimirItemEmprestimo() const;
        ExemplarLivro* getExemplar() const;

        Data getDataParaDevolucao();
        int getDataQueFoiDevolvido();
        Livro* getLivro() const;

        void setExemplar(ExemplarLivro* novoExemplar);
        void setDataParaDevolucao(Data novaDataParaDevolucao);
        void setDataQueFoiDevolvido(int novaDataQueFoiDevolvido);
};

#endif