#include "Emprestimo.h"
#include "Livro.h"
#include "ItemEmprestimo.h"
#include "ExemplarLivro.h"
#include "StatusEmprestimo.h"  
#include <iostream>

using std::cout;
using std::endl;
using std::iterator;

Emprestimo::Emprestimo(): usuario(nullptr), status(0) {}                 //cria o emprestimo com um ponteiro que nao associa a nenhum usuário

void Emprestimo::imprimirEmprestimo() {                                  
    cout << "+++ Detalhes Emprestimo +++" << endl;                       
    if (usuario != nullptr) {                                            // Checa se ponteiro foi resolvido (diferente do endereco nulo)
        cout << "Usuario: "; 
        usuario->imprimirUsuario(); 
    } else {
        cout << "Usuario: (Nao especificado)" << endl;                   // caso base
    }
    cout << "Livros Emprestados:" << endl;
    for (vector<ItemEmprestimo>::const_iterator temp = itens.cbegin(); temp != itens.cend(); ++temp) { // iterador aponta para os elementos do vetor, começa no primeiro elemento graças ao itens.cbegin() e percorre temp++ até o itens.cend()
        temp -> imprimirItemEmprestimo();                                // Emite a exibicao pro item que o iterador estiver apontando agora
    }
}

void Emprestimo::adicionarItem(const ItemEmprestimo& novoItem) { //Apenas adiciona um item, o gerenciadorDeEmprestimos que lida com o status dos exemplares
    if (novoItem.getExemplar() != nullptr) {                             // Se o exemplar inserido de fato existe e nao deu falha (nulo)
        itens.push_back(novoItem);                                       // Anexa o novoItem nas ultimas posicoes do vetor
    } else {                                                             // Senao...
        cout << "Erro: item invalido." << endl;                          // Aviso visual de que tentaram anexar uma falha
    }
}

int Emprestimo::getDataDeRetirada() const { return dataDeRetirada; }     // (Getter) Retorna o dia em int. 'const' impede essa funcao de alterar dados sem querer

int Emprestimo::getDataPrevistaDevolucao() const { return dataPrevistaDevolucao; }

int Emprestimo::getDataDevolucao() const { return dataDevolucao; }

int Emprestimo::getStatus() const { return status; }

Usuario* Emprestimo::getUsuario() const {return usuario;}                // (Getter) Devolve o ponteiro de memoria para classe Usuario

const vector<ItemEmprestimo>& Emprestimo::getItens() const { return itens; } // Devolve vetor itens. 'const vector&' significa que estamos devolvendo o acesso a eles porem apenas para LEITURA

void Emprestimo::setDataDeRetirada(int novaDataDeRetirada) { this -> dataDeRetirada = novaDataDeRetirada; } 

void Emprestimo::setDataPrevistaDevolucao(int novaDataPrevistaDevolucao) { this -> dataPrevistaDevolucao = novaDataPrevistaDevolucao; } 

void Emprestimo::setDataDevolucao(int novaDataDevolucao) { this -> dataDevolucao = novaDataDevolucao; } 

void Emprestimo::setStatus(int novoStatus) { this -> status = novoStatus;} 

void Emprestimo::setUsuario(Usuario* novoUsuario) {this-> usuario = novoUsuario;} // Atualiza localmente com a posicao na memoria de um dado objeto Usuario

void Emprestimo::setItens(Livro& novoLivro){                            
    ItemEmprestimo ItemAdicionado;                                      // cria um objeto em branco do tipo ItemEmprestimo
    ExemplarLivro* Exemplar = novoLivro.getExemplarDisponivel();        // procura qual cópia está disponivel e retorna um ponteiro para ele
    if (Exemplar != nullptr) {                                          // Se o ponteiro retornado e' valido (ou seja, achou sim uma copia livre)
        ItemAdicionado.setExemplar(Exemplar);                           //vai vincular o livro ao ponteiro do exemplar disponivel
        Exemplar->setStatus(StatusEmprestimo::EMPRESTADO);              // altera o status desse exemplar
        itens.push_back(ItemAdicionado);                                //pega o registro do exemplar e o adiciona no final do vetor itens
    } else {
        cout << "Erro: Nenhum exemplar disponivel para o livro." << endl;    // caso base
    }
}
