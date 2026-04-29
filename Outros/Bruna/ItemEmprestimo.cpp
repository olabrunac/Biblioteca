#include "ItemEmprestimo.h"
#include "ExemplarLivro.h"
#include <iostream>

using std::cout;
using std::endl;

ItemEmprestimo::ItemEmprestimo():dataParaDevolucao(0), dataQueFoiDevolvido(0), exemplar(nullptr) {} // Construtor inicia valores numericos zerados e marca o exemplar que ele guarda como nulo inicialmente

void ItemEmprestimo::imprimirItemEmprestimo()const {                    // (Read-only) Mostra informacoes do item
    if (exemplar != nullptr) {
        exemplar->imprimirExemplarLivro();                              // Delega a tarefa de exibir informacoes fisicas para a propria classe Exemplar (usando ponteiro '->')
    }
}

ExemplarLivro* ItemEmprestimo::getExemplar() const { return exemplar; } // O '*' extrai o objeto "sólido" do endereço de memória, (Ele diz que seu retorno sera estritamente o endereco do objeto, o ponteiro ExemplarLivro)

int ItemEmprestimo::getDataParaDevolucao() { return dataParaDevolucao; }

int ItemEmprestimo::getDataQueFoiDevolvido() { return dataQueFoiDevolvido; }

void ItemEmprestimo::setExemplar(ExemplarLivro* novoExemplar) { this->exemplar = novoExemplar;}

void ItemEmprestimo::setDataParaDevolucao(int novaDataParaDevolucao) { this -> dataParaDevolucao = novaDataParaDevolucao; }

void ItemEmprestimo::setDataQueFoiDevolvido(int novaDataQueFoiDevolvido) { this -> dataQueFoiDevolvido = novaDataQueFoiDevolvido; }