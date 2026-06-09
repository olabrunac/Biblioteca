#ifndef EMPRESTIMO_H
#define EMPRESTIMO_H

#include "ItemEmprestimo.h"
#include "Usuario.h"
#include "Data.h"

#include <vector>

using std::vector;


class Emprestimo {
    private:

        vector <ItemEmprestimo*> itens; // Ponteiro quebrou a classe 
        Usuario* usuario;
        Data dataEmprestimo;
        Data dataPrevistaDevolucao;
        Data dataDevolucao;
        int status;

    public:
        Emprestimo();
        Emprestimo(Usuario* novoUsuario, const Data& novaDataDEmprestimo, const Data& novaDataPrevistaDevolucao, const Data& novaDataDevolucao, int novoStatus);
        ~Emprestimo();                                      
        void imprimirEmprestimo();
        void adicionarItem(ItemEmprestimo* novoItem);

        Data getDataEmprestimo() const;
        Data getDataPrevistaDevolucao() const;
        Data getDataDevolucao() const; 
        int getStatus() const;
        Usuario* getUsuario() const;
        const vector<ItemEmprestimo*>& getItens() const;

        void setDataEmprestimo(const Data novaDataEmprestimo);
        void setDataPrevistaDevolucao(const Data novaDataPrevistaDevolucao);
        void setDataDevolucao(const Data novaDataDevolucao);
        void setStatus(int novoStatus);
        void setUsuario(Usuario* novoUsuario);
        void setItens(Livro& novoLivro);
        
};

#endif