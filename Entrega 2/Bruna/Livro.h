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

        int getCodigo();
        string getTitulo();
        int getEdicao();
        float getPreco();
        Editora getEditora();
        int getAnoPublicacao();
        int getQuantidadeDeExemplares();
        int getNroDiasPermitidoEmprestimo();
};

#endif