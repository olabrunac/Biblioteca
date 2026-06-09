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
        int dataDevolucao; //tem que ser int pois se Data = 0 dá erro
        int status;

    public:
        Emprestimo();
        Emprestimo(Usuario* novoUsuario, const Data& novaDataDeRetirada, const Data& novaDataPrevistaDevolucao, const int novaDataDevolucao, int novoStatus);
        ~Emprestimo();
        void imprimirEmprestimo();
        void adicionarItem(ItemEmprestimo* novoitem);

        Data getDataDeRetirada() const;
        Data getDataPrevistaDevolucao() const;
        int getDataDevolucao() const; 
        int getStatus() const;
        Usuario* getUsuario() const;
        const vector<ItemEmprestimo*>& getItens() const;

        void setDataDeRetirada(const Data novaDataDeRetirada);
        void setDataPrevistaDevolucao(const Data novaDataPrevistaDevolucao);
        void setDataDevolucao(const int novaDataDevolucao);
        void setStatus(int novoStatus);
        void setUsuario(Usuario* novoUsuario);
        void setItens(Livro& novoLivro);

        bool possuiLivro(Livro* livroTeste) const;
        
};

#endif