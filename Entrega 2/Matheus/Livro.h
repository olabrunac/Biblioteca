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

        vector <ExemplarLivro> exemplares;
    public:
        Livro();
        void imprimirLivro();
        
        bool estaDisponivel() const; //Precisei adicionar o const pois utilizo esse método no listarDisponiveis do Acervo
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