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
        string titulo;
        Editora editora; //sem preço e sem edição
        vector <Autor*> autores;
        int quantidadeDeExemplares;
        int nroDiasPermitidoEmprestimo;
        int anoPublicacao;
        int nroPaginas;
        int statusAgora; /*VER COMO SE RELACIONA COM A RESERVA*/
        int statusFuturo;
        vector <ExemplarLivro> exemplares;

    public:
        //reorganizei aqui, falta deixar o cpp na mesma ordem
        Livro();
        Livro(int novoCodigo, string novoTitulo, Editora& novaEditora, vector<Autor*> novoAutor, int quantidade);
        Livro(int novoCodigo, string novoTitulo, Editora& novaEditora, vector<Autor*> novoAutor, int quantidade, int novoNroDias, int novoAno, int novoNroPaginas);
        //~Livro();                                       //o acervo já faz esse trampo
        void imprimirLivro();
        void criarExemplares(int quantidade);
        bool estaDisponivel() const;
        bool possuiExemplaresEmprestados() const;       //Pode ser usado antes de excluir um livro, verificar se tem exemplares emprestados
        
        int getCodigo() const;
        string getTitulo() const;
        const Editora& getEditora() const;
        const vector<Autor*>& getAutor() const;             //garante que nao alterem o vetor
        int getQuantidadeDeExemplares() const;
        int getNroDiasPermitidoEmprestimo() const;
        int getAnoPublicacao() const;
        int getNroPaginas() const; // Adicionado const para consistência
        string getStatusAgora() const;
        int getStatusFuturo(Data& data) const;
        ExemplarLivro* getExemplarDisponivel();
        int getQuantidadeDisponivel() const;

        void setCodigo(int novoCodigo);
        void setTitulo(string novoTitulo);
        void setEditora(Editora& novaEditora);
        void setAutor(vector<Autor*> novoAutor);
        void setQuantidadeDeExemplares(int novaQuantidade);
        void setNroDiasPermitidoEmprestimo(int novoNroDias);
        void setAnoPublicacao(int novoAno);
        void setNroPaginas(int novoNroPaginas);
    

        bool operator==( const Livro& outroLivro) const;
};
#endif