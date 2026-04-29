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

bool Livro::estaDisponivel()const  {  
    // Percorre todos os exemplares físicos que o livro possui
    for (const ExemplarLivro& exemplar : exemplares) {
        // Se encontrar pelo menos UM exemplar na prateleira (DISPONIVEL), o livro está disponível!
        if (exemplar.getStatus() == StatusParaEmprestimo::DISPONIVEL) {
            return true;
        }
    }
    // Se olhou todos e não achou nenhum disponível (ou se a lista estiver vazia), retorna falso.
    return false; 
}

void Livro::criarExemplares(int quantidade) { 

for (int i = 0; i < quantidade; i++) {
        ExemplarLivro novoExemplar;
        
        // Todo novo exemplar nasce com status DISPONIVEL
        StatusParaEmprestimo statusInicial = StatusParaEmprestimo::DISPONIVEL;
        novoExemplar.setStatus(statusInicial);

        novoExemplar.setLivro(this);
        
        // Define um número para o exemplar (ex: se ja tem 2, o próximo é o 3)
        novoExemplar.setNroExemplar(this->quantidadeDeExemplares + i + 1);

        // Adiciona o exemplar gerado na lista que pertence a este Livro
        this->exemplares.push_back(novoExemplar);
    }
    
    // Atualiza o contador de quantidade
    this->quantidadeDeExemplares += quantidade; 
}

ExemplarLivro* Livro::getExemplarDisponivel() {

    for (ExemplarLivro& exemplar : exemplares) {
        if (exemplar.getStatus() == StatusParaEmprestimo::DISPONIVEL) {
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

int Livro::getQuantidadeDeExemplares() const { 
    
    return exemplares.size(); }

int Livro::getNroDiasPermitidoEmprestimo() const { return nroDiasPermitidoEmprestimo; }

vector<Autor> Livro::getAutor() const { return autor; }

string Livro::getStatusAgora() const {
    if (estaDisponivel()) {
        return "Disponivel";
    }
    return "Indisponivel";
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

void Livro::setAutor(vector<Autor> novoAutor) { this -> autor = novoAutor; }

void Livro::setNroPaginas(int novoNroPaginas) { this -> nroPaginas = novoNroPaginas; }
