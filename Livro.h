#ifndef LIVRO_H
#define LIVRO_H

#include "ExemplarLivro.h"
#include "Autor.h"
#include "Data.h"
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
        vector<Autor*> autores;  //Arrumar o ponteiro
        int statusAgora; /*VER COMO SE RELACIONA COM A RESERVA*/
        int statusFuturo;
        int nroPaginas;

        vector <ExemplarLivro> exemplares;
    public:
        //****************** CRIAR CONSTRUTOR COM PARÂMETROS*********Livro()
        Livro();
        Livro(int novoCodigo, string novoTitulo, Editora& novaEditora, vector<Autor*> novoAutor); //Tive que tirar o quantidade de exemplares daqui, dava conflito com o método criarExemplares
        Livro(int novoCodigo, string novoTitulo, int novaEdicao, float novoPreco, Editora& novaEditora, int novoAno, int novaQuantidade, int novoNroDias, vector<Autor*> novoAutor, int novoNroPaginas);
        ~Livro(); //precisa implementar
        void imprimirLivro();
        
        bool estaDisponivel() const;
        void criarExemplares(int quantidade);
        bool possuiExemplaresEmprestados() const; //Pode ser usado antes de excluir um livro, verificar se tem exemplares emprestados

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
        vector<Autor*> getAutor() const;

        string getStatusAgora() const;

        int getStatusFuturo(Data& data) const;

        int getNroPaginas() const;

        void setCodigo(int novoCodigo);
        void setTitulo(string novoTitulo);
        void setEdicao(int novaEdicao);
        void setPreco(float novoPreco);
        void setEditora(Editora& novaEditora);
        void setAnoPublicacao(int novoAno);
        void setQuantidadeDeExemplares(int novaQuantidade);
        void setNroDiasPermitidoEmprestimo(int novoNroDias);
        void setAutor(vector<Autor*> novoAutor);
        void setNroPaginas(int novoNroPaginas);
    

        bool operator==( const Livro& outroLivro) const;
};
#endif