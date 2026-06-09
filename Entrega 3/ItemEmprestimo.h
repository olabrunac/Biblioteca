#ifndef ITEMEMPRESTIMO_H
#define ITEMEMPRESTIMO_H

#include "ExemplarLivro.h"
#include "Data.h"

class ItemEmprestimo {
    private:
        ExemplarLivro* exemplar;
        Data dataParaDevolucao;
        Data dataQueFoiDevolvido;
    public:
        
        ItemEmprestimo();

        void imprimirItemEmprestimo() const;
        ExemplarLivro* getExemplar() const;

        Data getDataParaDevolucao();
        Data getDataQueFoiDevolvido();
        Livro* getLivro() const;

        void setExemplar(ExemplarLivro* novoExemplar);
        void setDataParaDevolucao(Data novaDataParaDevolucao);
        void setDataQueFoiDevolvido(Data novaDataQueFoiDevolvido);
};

#endif