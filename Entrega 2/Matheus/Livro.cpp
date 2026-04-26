#include "Livro.h"
#include <iostream>

using std::cout;
using std::endl;

Livro::Livro() : codigo(0), quantidadeDeExemplares(0), statusAgora(0) {}

void Livro::imprimirLivro() {
    cout << "Titulo: " << titulo << " | Edicao: " << edicao << endl;
    cout << "Codigo: " << codigo << " | Editora: " << editora.getNome() << endl;  // ------------------------------
    cout << "Autores: ";
        if (autor.empty()) {
            cout << "Nenhum autor" << endl;
        } else {
            for (const Autor& temp : autor) {
                cout << "[" << temp.getNome() << "]" << endl;
            }
        }
    cout << "Quantidade de exemplares em estoque: " << quantidadeDeExemplares << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
}

bool Livro::estaDisponivel() const { return quantidadeDeExemplares > 0; }

void Livro::criarExemplares(int novoExemplar) { this -> quantidadeDeExemplares += novoExemplar; }



// set e get dos outros métodos

int Livro::getCodigo() const { return codigo; }

string Livro::getTitulo() const { return titulo; }

int Livro::getEdicao() const {return edicao; }

float Livro::getPreco() const { return preco; }

Editora Livro::getEditora() const { return editora; }

int Livro::getAnoPublicacao() const { return anoPublicacao; }

int Livro::getQuantidadeDeExemplares() const { return quantidadeDeExemplares; }

int Livro::getNroDiasPermitidoEmprestimo() const { return nroDiasPermitidoEmprestimo; }

vector<Autor> Livro::getAutor() const { return autor; }

int Livro::getStatusAgora() const {}

int Livro::getStatusFuturo() const {}

int Livro::getNroPaginas() const { return nroPaginas; }

void Livro::setCodigo(int novoCodigo) { this -> codigo = novoCodigo; }

void Livro::setTitulo(string novoTitulo) { this -> titulo = novoTitulo; }

void Livro::setEdicao(int novaEdicao) { this -> edicao = novaEdicao; }

void Livro::setPreco(float novoPreco) { this -> preco = novoPreco; }

void Livro::setEditora(Editora& novaEditora) { this -> editora = novaEditora; }

void Livro::setAnoPublicacao(int novoAno) { this -> anoPublicacao = novoAno; }

void Livro::setQuantidadeDeExemplares(int novaQuantidade) { this -> quantidadeDeExemplares = novaQuantidade; }

void Livro::setNroDiasPermitidoEmprestimo(int novoNroDias) { this -> nroDiasPermitidoEmprestimo = novoNroDias; }

void Livro::setAutor(vector<Autor> novoAutor) { this -> autor = novoAutor; }

void Livro::setStatusAgora() {}

void Livro::setStatusFuturo() {}

void Livro::setNroPaginas(int novoNroPaginas) { this -> nroPaginas = novoNroPaginas; }
