#ifndef EMPRESTIMO_H
#define EMPRESTIMO_H

#include "ItemEmprestimo.h"
#include "Usuario.h"
#include "Data.h"

#include <vector>

using std::vector;


class Emprestimo {
    private:

        vector <ItemEmprestimo*> itens;
        Usuario* usuario;
        Data dataDeRetirada;
        Data dataPrevistaDevolucao;
        Data dataDevolucao;
        int status;

    public:
        Emprestimo();
        void imprimirEmprestimo();
        void adicionarItem(const ItemEmprestimo& novoitem);

        Data getDataDeRetirada() const;
        Data getDataPrevistaDevolucao() const;
        Data getDataDevolucao() const; 
        int getStatus() const;
        Usuario* getUsuario() const;
        const vector<ItemEmprestimo>& getItens() const;

        void setDataDeRetirada(const int novaDataDeRetirada);
        void setDataPrevistaDevolucao(const int novaDataPrevistaDevolucao);
        void setDataDevolucao(const int novaDataDevolucao);
        void setStatus(int novoStatus);
        void setUsuario(Usuario* novoUsuario);
        void setItens(Livro& novoLivro);
        
};

#endif