#ifndef LIVRO_H
#define LIVRO_H

#include "ExemplarLivro.h"
#include "Autor.h"
#include "Editora.h"
#include <vector>

using std::string;
using std::vector;

class Livro {
    private:
        int codigo;
        string genero; /*ADICIONAR ISSO, VER SE VAI SER USADO PARA PESQUISA OU PARA OUTRA COISA*/
        string titulo;
        int edicao;
        float preco;
        Editora editora;
        int anoPublicacao;
        int quantidadeDeExemplares;
        int nroDiasPermitidoEmprestimo;
        vector<Autor> autor;
        int statusAgora; /*VER COMO SE RELACIONA COM A RESERVA*/
        int statusFuturo;
        int nroPaginas;

        vector <ExemplarLivro> exemplares;
    public:
        //****************** CRIAR CONSTRUTOR COM PARÂMETROS*********Livro()
        Livro();
        void imprimirLivro();
        
        bool estaDisponivel() const;
        void criarExemplares(int quantidade);

        ExemplarLivro* getExemplarDisponivel();

        int getCodigo() const;
        string getTitulo() const;
        int getEdicao() const;
        float getPreco() const;
        Editora getEditora() const;
        int getAnoPublicacao() const;
        int getQuantidadeDeExemplares() const;
        int getNroDiasPermitidoEmprestimo() const;
        int getQuantidadeDisponivel() const;
        vector<Autor> getAutor() const;
        string getStatusAgora() const;
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
        void setNroPaginas(int novoNroPaginas);
    
};

#endif