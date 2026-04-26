#ifndef LIVRO_H
#define LIVRO_H

#include "ExemplarLivro.h"
#include "Autor.h"
#include "Editora.h"
#include <vector>
#include <string>

using std::string;
using std::vector;

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
        vector<Autor> autor;
        int statusAgora;
        int statusFuturo;
        int nroPaginas;

    public:
        Livro();
        void imprimirLivro();
        
        bool estaDisponivel () const;
        void criarExemplares(int novoExemplar);
        ExemplarLivro getExemplarDisponivel();

        int getCodigo() const;
        string getTitulo() const;
        int getEdicao() const;
        float getPreco() const;
        Editora getEditora() const;
        int getAnoPublicacao() const;
        int getQuantidadeDeExemplares() const;
        int getNroDiasPermitidoEmprestimo() const;
        vector<Autor> getAutor() const;
        int getStatusAgora() const;
        int getStatusFuturo() const;
        int getNroPaginas() const;

        void setCodigo(int novoCodigo);
        void setTitulo(string novoTitulo);
        void setEdicao(int novaEdicao);
        void setPreco(float novoPreco);
        void setEditora(Editora& novaEditora);
        void setAnoPublicacao(int novoAno);
        void setQuantidadeDeExemplares(int novaQuantidade);
        void setNroDiasPermitidoEmprestimo(int novoNroDias);
        void setAutor(vector<Autor> novoAutor);
        void setStatusAgora();
        void setStatusFuturo();
        void setNroPaginas(int novoNroPaginas);
    
};

#endif