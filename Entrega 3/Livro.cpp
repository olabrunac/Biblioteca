#include "Livro.h"
#include <iostream>

using std::cout;
using std::endl;

Livro::Livro() : codigo(0), quantidadeDeExemplares(0), statusAgora(0) {}

Livro::Livro(int novoCodigo, string novoTitulo, Editora& novaEditora, int novaQuantidade, vector<Autor*> novoAutor) : codigo(novoCodigo), titulo(novoTitulo), editora(novaEditora), quantidade(novaQuantidade), autores(novoAutor) {}

Livro::Livro(int novoCodigo, string novoTitulo, int novaEdicao, float novoPreco, Editora& novaEditora, int novoAno, int novaQuantidade, int novoNroDias, vector<Autor*> novoAutor, int novoNroPaginas)
: codigo(novoCodigo), titulo(novoTitulo), edicao(novaEdicao), preco(novoPreco), editora(novaEditora), anoPublicacao(novoAno), quantidadeDeExemplares(novaQuantidade), nroDiasPermitidoEmprestimo(novoNroDias), autores(novoAutor), nroPaginas(novoNroPaginas) {
    criarExemplares(novaQuantidade); //para criar os exemplares aqui em vez de só anotar quantos tem
}

Livro::~Livro() {}

void Livro::imprimirLivro() { 
    cout << "Titulo: " << titulo << " | Edicao: " << edicao << endl;
    cout << "Codigo: " << codigo << " | Editora: " << editora.getNome() << endl;
    cout << "Autores: ";
        if (autores.empty()) {
            cout << "Nenhum autor" << endl;
        } else {
            for (const Autor& temp : autores) {
                cout << "[" << temp.getNome() << "]" << endl;
            }
        }
    cout << "Quantidade de exemplares em estoque: " << getQuantidadeDeExemplares() << endl;
    cout << "Quantidade de disponíveis: " << getQuantidadeDisponivel() << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
}

bool Livro::estaDisponivel() const  {
    for (const ExemplarLivro& exemplar : exemplares) {
        if (exemplar.getStatus() == StatusEmprestimo::DISPONIVEL) {
            return true;
        }
    }
    return false;
}

void Livro::criarExemplares(int quantidade) {

for (int i = 0; i < quantidade; i++) {
        ExemplarLivro novoExemplar;
        StatusEmprestimo statusInicial = StatusEmprestimo::DISPONIVEL;
        novoExemplar.setStatus(statusInicial);
        novoExemplar.setLivro(this);
        novoExemplar.setNroExemplar(this->quantidadeDeExemplares + i + 1);
        this->exemplares.push_back(novoExemplar);
    }
    this->quantidadeDeExemplares += quantidade;
}

ExemplarLivro* Livro::getExemplarDisponivel() {

    for (ExemplarLivro& exemplar : exemplares) {
        if (exemplar.getStatus() == StatusEmprestimo::DISPONIVEL) {
            return &exemplar;
        }
    }
    
    cout << "Nenhum exemplar disponivel no momento!" << endl;
    return nullptr;
}

int Livro::getCodigo() const { return codigo; } 

string Livro::getTitulo() const { return titulo; }

int Livro::getEdicao() const {return edicao; }

float Livro::getPreco() const { return preco; }

Editora Livro::getEditora() const { return editora; }

int Livro::getAnoPublicacao() const { return anoPublicacao; }

int Livro::getQuantidadeDeExemplares() const { return exemplares.size(); }

int Livro::getNroDiasPermitidoEmprestimo() const { return nroDiasPermitidoEmprestimo; }

vector<Autor> Livro::getAutor() const { return autores; }

string Livro::getStatusAgora() const {
    if (estaDisponivel()) {
        return "Disponivel (" + std::to_string(getQuantidadeDisponivel()) + " exemplares)";
    }
    return "Indisponivel";
}

int Livro::getQuantidadeDisponivel() const {
    int contador = 0;
    for (const ExemplarLivro& exemplar : exemplares) {
        if (exemplar.getStatus() == StatusEmprestimo::DISPONIVEL) {
            contador++;
        }
    }
    return contador;
}

int Livro::getNroPaginas() const { return nroPaginas; }

void Livro::setCodigo(int novoCodigo) { this -> codigo = novoCodigo; }

void Livro::setTitulo(string novoTitulo) { this -> titulo = novoTitulo; }

void Livro::setEdicao(int novaEdicao) { this -> edicao = novaEdicao; }

void Livro::setPreco(float novoPreco) { this -> preco = novoPreco; }

void Livro::setEditora(Editora& novaEditora) { this -> editora = novaEditora; }

void Livro::setAnoPublicacao(int novoAno) { this -> anoPublicacao = novoAno; }

void Livro::setQuantidadeDeExemplares(int novaQuantidade) { this -> quantidadeDeExemplares = novaQuantidade; }

void Livro::setNroDiasPermitidoEmprestimo(int novoNroDias) { this -> nroDiasPermitidoEmprestimo = novoNroDias; }

void Livro::setAutor(vector<Autor*> novoAutor) { this -> autores = novoAutor; }

void Livro::setNroPaginas(int novoNroPaginas) { this -> nroPaginas = novoNroPaginas; }
