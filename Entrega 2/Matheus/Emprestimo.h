#ifndef EMPRESTIMO_H
#define EMPRESTIMO_H

#include "ItemEmprestimo.h"
#include "Usuario.h"
#include <vector>

using std::vector;


class Emprestimo {
    private:

        vector <ItemEmprestimo> itens;
        Usuario* usuario;
        int dataDeRetirada;
        int dataPrevistaDevolucao;
        int dataDevolucao;
        int status;

    public:
        Emprestimo();
        void imprimirEmprestimo();
        void adicionarItem(const ItemEmprestimo& novoitem);

        int getDataDeRetirada() const;
        int getDataPrevistaDevolucao() const;
        int getDataDevolucao() const; 
        int getStatus() const;
        Usuario* getUsuario() const;
        const vector<ItemEmprestimo>& getItens() const;

        void setDataDeRetirada(int novaDataDeRetirada);
        void setDataPrevistaDevolucao(int novaDataPrevistaDevolucao);
        void setDataDevolucao(int novaDataDevolucao);
        void setStatus(int novoStatus);
        void setUsuario(Usuario* novoUsuario);
        
};

#endif