#include "Livro.h"
#include <iostream>

using std::cout;
using std::endl;

Livro::Livro() {}

void Livro::imprimirLivro() {
    cout << "Código: " << codigo << endl;
    cout << "Titulo: " << titulo << endl;
    cout << "Edicao: " << edicao << endl;
    cout << "Preco: " << preco << endl;
    cout << "Editora: " << &editora << endl;  // ------------------------------
    cout << "Ano: " << anoPublicacao << endl;
    cout << "Quantidade de Exemplares: " << quantidadeDeExemplares << endl;
}

int Livro::getCodigo() { return codigo; }

string Livro::getTitulo() { return titulo; }

int Livro::getEdicao() {return edicao; }

float Livro::getPreco() { return preco; }

Editora Livro::getEditora() { return editora; }

int Livro::getAnoPublicacao() { return anoPublicacao; }

int Livro::getQuantidadeDeExemplares() { return quantidadeDeExemplares; }

int Livro::getNroDiasPermitidoEmprestimo() { return nroDiasPermitidoEmprestimo; }

void Livro::setCodigo(int novoCodigo) { this -> codigo = novoCodigo; }

void Livro::setTitulo(string novoTitulo) { this -> titulo = novoTitulo; }

void Livro::setEdicao(int novaEdicao) { this -> edicao = novaEdicao; }

void Livro::setPreco(float novoPreco) { this -> preco = novoPreco; }

void Livro::setEditora(Editora& novaEditora) { this -> editora = novaEditora; }

void Livro::setAnoPublicacao(int novoAno) { this -> anoPublicacao = novoAno; }

void Livro::setQuantidadeDeExemplares(int novaQuantidade) { this -> quantidadeDeExemplares = novaQuantidade; }

void Livro::setNroDiasPermitidoEmprestimo(int novoNroDias) { this -> nroDiasPermitidoEmprestimo = novoNroDias; }
