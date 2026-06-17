#include "Livro.h"
#include <iostream>

using std::cout;
using std::endl;

Livro::Livro() : codigo(0), statusAgora(0), nroDiasPermitidoEmprestimo(7) {}


Livro::Livro(int novoCodigo, string novoTitulo, Editora& novaEditora, vector<Autor*> novoAutor, int quantidade)
    : codigo(novoCodigo), titulo(novoTitulo), editora(novaEditora), autores(novoAutor) {
        criarExemplares(quantidade);
    }

    
Livro::Livro(int novoCodigo, string novoTitulo, int novaEdicao, float novoPreco, Editora& novaEditora, int novoAno, int quantidade, int novoNroDias, vector<Autor*> novoAutor, int novoNroPaginas)
    : codigo(novoCodigo), titulo(novoTitulo), edicao(novaEdicao), preco(novoPreco), editora(novaEditora), anoPublicacao(novoAno), nroDiasPermitidoEmprestimo(novoNroDias), autores(novoAutor), nroPaginas(novoNroPaginas) {
        criarExemplares(quantidade);
    }


void Livro::imprimirLivro() { 
    cout << "Titulo: " << titulo << " | Edicao: " << edicao << endl;
    cout << "Codigo: " << codigo << " | Editora: " << editora.getNome() << endl;
    cout << "Autores: ";
        if (autores.empty()) {
            cout << "Nenhum autor" << endl;
        } else {
            for (const Autor* temp : autores) {
                cout << "[" << temp->getNome() << "]" << endl;
            }
        }
    cout << "Quantidade de exemplares em estoque: " << getQuantidadeDeExemplares() << endl;
    cout << "Quantidade de disponíveis: " << getQuantidadeDisponivel() << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
}


bool Livro::estaDisponivel() const  {
    for (const ExemplarLivro& temp : exemplares) {
        if (temp.getStatus() == StatusEmprestimo::DISPONIVEL) {
            return true;
        }
    }
    return false;
}


bool Livro::possuiExemplaresEmprestados() const {
    // Vasculha os exemplares para ver se tem algum emprestado
    for (const ExemplarLivro& temp : exemplares) {
        if (temp.getStatus() == StatusEmprestimo::EMPRESTADO) {
            return true; //Ainda não pode ser excluido
        }
    }
    return false; 
}


void Livro::criarExemplares(int quantidade) { 
    // Conta quantos exemplares já existem fisicamente no vetor
    int tamanhoAtual = exemplares.size(); 
    
    for (int i = 0; i < quantidade; i++) {
        ExemplarLivro novoExemplar;
        novoExemplar.setStatus(StatusEmprestimo::DISPONIVEL);
        novoExemplar.setLivro(this);
        
        // Agora o cálculo será: 0 + 0 + 1 = 1 (Para o primeiro livro)
        novoExemplar.setNroExemplar(tamanhoAtual + i + 1); 
        
        this->exemplares.push_back(novoExemplar);
    }
    
    // Atualiza a variável de controle apenas no final
    this->quantidadeDeExemplares = exemplares.size(); 
}


ExemplarLivro* Livro::getExemplarDisponivel() {

    for (ExemplarLivro& temp : exemplares) {
        if (temp.getStatus() == StatusEmprestimo::DISPONIVEL) {
            return &temp;
        }
    }
    cout << "-Nenhum exemplar de '" << titulo << "' disponivel!" << endl;
    return nullptr;
}


int Livro::getCodigo() const { return codigo; } 


string Livro::getTitulo() const { return titulo; }


int Livro::getEdicao() const {return edicao; }


float Livro::getPreco() const { return preco; }


const Editora& Livro::getEditora() const { return editora; }


int Livro::getAnoPublicacao() const { return anoPublicacao; }


int Livro::getQuantidadeDeExemplares() const { return exemplares.size(); }


int Livro::getNroDiasPermitidoEmprestimo() const { 
    
    if(this->nroDiasPermitidoEmprestimo < 7){ //minimo de 7 dias, menos que isso não faz sentido

        return 7;
    }
    
    return nroDiasPermitidoEmprestimo; }


int Livro::getQuantidadeDisponivel() const {
    int contador = 0;
    for (const ExemplarLivro& temp : exemplares) {
        if (temp.getStatus() == StatusEmprestimo::DISPONIVEL) {
            contador++;
        }
    }
    return contador;
}

const vector<Autor*>& Livro::getAutor() const { return autores; }


string Livro::getStatusAgora() const {
    if (estaDisponivel()) {
        return "Disponivel (" + std::to_string(getQuantidadeDisponivel()) + " exemplares)";
    }
    return "Indisponivel (0 exemplares)";
}


//int Livro::getStatusFuturo(Data& data) const {} //Nao tenho a menor ideia de como fazer isso por enquanto, precisa acessar o vetor de Reservas e Emprestimos.

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


bool Livro::operator==( const Livro& outroLivro) const {
           if (codigo == outroLivro.codigo) {
                return true;
            }
            return false;
        }