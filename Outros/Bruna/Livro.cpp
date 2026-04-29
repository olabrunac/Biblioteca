#include "Livro.h"
#include <iostream>

using std::cout;
using std::endl;

Livro::Livro() : codigo(0), quantidadeDeExemplares(0), statusAgora(0) {}

void Livro::imprimirLivro() { 
    cout << "Titulo: " << titulo << " | Edicao: " << edicao << endl;
    cout << "Codigo: " << codigo << " | Editora: " << editora.getNome() << endl;
    cout << "Autores: ";
        if (autor.empty()) {                                                        // Verifica pela funcao empty() dos vector se ele esta vazio (0 de tamanho)
            cout << "Nenhum autor" << endl;
        } else {
            for (const Autor& temp : autor) {                                       // Range for-each que caminha pela lista referenciando ('&') e com bloqueio 'const' para ninguem estragar dados acidentalmente
                cout << "[" << temp.getNome() << "]" << endl;                       // Pega o iterador do momento, busca seu nome e envelopa em colchetes
            }
        }
    cout << "Quantidade de exemplares em estoque: " << getQuantidadeDeExemplares() << endl;
    cout << "Quantidade de disponíveis: " << getQuantidadeDisponivel() << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
}

bool Livro::estaDisponivel() const  {                                               // Funcao booleana para flag interna/externa (apenas le e nunca muda)
    for (const ExemplarLivro& exemplar : exemplares) {                              // Percorre todos os exemplares físicos que o livro possui
        if (exemplar.getStatus() == StatusEmprestimo::DISPONIVEL) {                 // Se encontrar pelo menos UM exemplar na prateleira (DISPONIVEL), o livro está disponível!
            return true;                                                            // Corta fluxo aqui e sai espalhando que eh verdadeiro
        }
    }
    return false;
}

void Livro::criarExemplares(int quantidade) {                                       // Método utilitario para pre-alocar copias fisicas no programa

for (int i = 0; i < quantidade; i++) {                                              // Roda num loop tradicional pelo numoero exato de passagens 
        ExemplarLivro novoExemplar;                                                 // Inicia um novo objeto ExemplarLivro fisico vazio
        StatusEmprestimo statusInicial = StatusEmprestimo::DISPONIVEL;              // Todo novo exemplar nasce com status DISPONIVEL
        novoExemplar.setStatus(statusInicial);                                      // Aplica a regra criada em cima pro exemplar
        novoExemplar.setLivro(this);                                                // Informa ao exemplar "Voce e copia da classe mae que ta me executando ('this' ponteiro)"
        novoExemplar.setNroExemplar(this->quantidadeDeExemplares + i + 1);          // Define um número para o exemplar (ex: se ja tem 2, o próximo é o 3)
        this->exemplares.push_back(novoExemplar);                                   // Adiciona o exemplar gerado na lista que pertence a este Livro
    }
    this->quantidadeDeExemplares += quantidade;                                     // Atualiza o contador de quantidade
}

ExemplarLivro* Livro::getExemplarDisponivel() {                                     // Busca um exemplar ativo para emprestar e o devolve

    for (ExemplarLivro& exemplar : exemplares) {                                    // Laco por todas as copias registradas (agora sem 'const' pois pretendemos empresta-la (alterar estado))
        if (exemplar.getStatus() == StatusEmprestimo::DISPONIVEL) {                 // Avalia o enum
            return &exemplar;                                                       // Usa o operador '&' pra obter a localizacao de memoria deste iterador em relacao e retornar seu ponteiro
        }
    }
    
    cout << "Nenhum exemplar disponivel no momento!" << endl;                       // Tratamento para fim de fluxo (vazio)
    return nullptr;                                                                 // Entrega o valor nulo significando que ha impedimento 
}

int Livro::getCodigo() const { return codigo; } 

string Livro::getTitulo() const { return titulo; }

int Livro::getEdicao() const {return edicao; }

float Livro::getPreco() const { return preco; }

Editora Livro::getEditora() const { return editora; }                               // (Getter) Devolve objeto contendo a copia da Editora

int Livro::getAnoPublicacao() const { return anoPublicacao; }

int Livro::getQuantidadeDeExemplares() const { return exemplares.size(); }          // (Getter) Retorna o tamanho atual da quantidade contada dentro do vector

int Livro::getNroDiasPermitidoEmprestimo() const { return nroDiasPermitidoEmprestimo; }

vector<Autor> Livro::getAutor() const { return autor; }

string Livro::getStatusAgora() const {
    if (estaDisponivel()) {                                                         // Aciona rotina boolean
        return "Disponivel (" + std::to_string(getQuantidadeDisponivel()) + " exemplares)"; // mostrar a quantidade de exemplares disponiveis (std::to_string casta um int para string e resolve operacao text)
    }
    return "Indisponivel";                                                          // Retorno hardcoded padrao (nao entra no if)
}

int Livro::getQuantidadeDisponivel() const {                                        // Faz uma re-checagem forcada manual de tudo q ta livre
    int contador = 0;                                                               // Inicia contador do zero
    for (const ExemplarLivro& exemplar : exemplares) {                              // Usa listagem read-only
        if (exemplar.getStatus() == StatusEmprestimo::DISPONIVEL) {                 // Verifica disponivel
            contador++;                                                             // Aumenta contador de 1 em 1
        }
    }
    return contador;                                                                // Retorna os ganhos do laco
}

int Livro::getNroPaginas() const { return nroPaginas; }

void Livro::setCodigo(int novoCodigo) { this -> codigo = novoCodigo; }              // (Setter) this->codigo resolve conflitos e seta na classe o que veio em 'novoCodigo'

void Livro::setTitulo(string novoTitulo) { this -> titulo = novoTitulo; }

void Livro::setEdicao(int novaEdicao) { this -> edicao = novaEdicao; }

void Livro::setPreco(float novoPreco) { this -> preco = novoPreco; }

void Livro::setEditora(Editora& novaEditora) { this -> editora = novaEditora; }     // (Setter) Puxando pela localizacao na memoria (&) 

void Livro::setAnoPublicacao(int novoAno) { this -> anoPublicacao = novoAno; }

void Livro::setQuantidadeDeExemplares(int novaQuantidade) { this -> quantidadeDeExemplares = novaQuantidade; }

void Livro::setNroDiasPermitidoEmprestimo(int novoNroDias) { this -> nroDiasPermitidoEmprestimo = novoNroDias; }

void Livro::setAutor(vector<Autor> novoAutor) { this -> autor = novoAutor; }        // (Setter) Associa outro vetor vector<Autor> reescrevendo o atributo anterior

void Livro::setNroPaginas(int novoNroPaginas) { this -> nroPaginas = novoNroPaginas; }
