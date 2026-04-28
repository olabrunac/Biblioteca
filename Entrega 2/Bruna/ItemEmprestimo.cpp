#include "ItemEmprestimo.h"
#include "ExemplarLivro.h"
#include <iostream>

using std::cout;
using std::endl;

ItemEmprestimo::ItemEmprestimo():dataParaDevolucao(0), dataQueFoiDevolvido(0), exemplar(nullptr) {}

void ItemEmprestimo::imprimirItemEmprestimo()const {
    if (exemplar != nullptr) {
        exemplar->imprimirExemplarLivro();
    }
}

ExemplarLivro* ItemEmprestimo::getExemplar() const { return exemplar; } // O '*' extrai o objeto "sólido" do endereço de memória, 

int ItemEmprestimo::getDataParaDevolucao() { return dataParaDevolucao; }

int ItemEmprestimo::getDataQueFoiDevolvido() { return dataQueFoiDevolvido; }

void ItemEmprestimo::setExemplar(ExemplarLivro* novoExemplar) { this->exemplar = novoExemplar;} //Como o novoExemplar é um ponteiro para um objeto ExemplarLivro

void ItemEmprestimo::setDataParaDevolucao(int novaDataParaDevolucao) { this -> dataParaDevolucao = novaDataParaDevolucao; }

void ItemEmprestimo::setDataQueFoiDevolvido(int novaDataQueFoiDevolvido) { this -> dataQueFoiDevolvido = novaDataQueFoiDevolvido; }
