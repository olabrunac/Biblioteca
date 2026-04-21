#ifndef LIVRO_H
#define LIVRO_H

#include "Editora.h"
#include <string>

using std::string;

class Livro {
    private:
        int codigo;
        string titulo;
        int edicao;
        float preco;
        Editora editora;
        int anoPublicacao;
        int quantidadeDeExemplares;
        int nroDiasPermitidoEmprestimo;

    public:
        Livro();
        void imprimirLivro();

        int getCodigo();
        string getTitulo();
        int getEdicao();
        float getPreco();
        Editora getEditora();
        int getAnoPublicacao();
        int getQuantidadeDeExemplares();
        int getNroDiasPermitidoEmprestimo();

        void setCodigo(int novoCodigo);
        void setTitulo(string novoTitulo);
        void setEdicao(int novaEdicao);
        void setPreco(float novoPreco);
        void setEditora(Editora& novaEditora);
        void setAnoPublicacao(int novoAno);
        void setQuantidadeDeExemplares(int novaQuantidade);
        void setNroDiasPermitidoEmprestimo(int novoNroDias);
    
};

#endif