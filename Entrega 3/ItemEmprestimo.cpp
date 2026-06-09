#include "ItemEmprestimo.h"
#include "ExemplarLivro.h"
#include <iostream>

using std::cout;
using std::endl;

ItemEmprestimo::ItemEmprestimo():dataParaDevolucao(0), dataQueFoiDevolvido(0), exemplar(nullptr) {}


ItemEmprestimo::~ItemEmprestimo() {}            //nao faz alocacao dinamica


void ItemEmprestimo::imprimirItemEmprestimo()const {
    if (exemplar != nullptr) {
        exemplar->imprimirExemplarLivro();
    }
}


ExemplarLivro* ItemEmprestimo::getExemplar() const { return exemplar; }


int ItemEmprestimo::getDataParaDevolucao() { return dataParaDevolucao; }


int ItemEmprestimo::getDataQueFoiDevolvido() { return dataQueFoiDevolvido; }


void ItemEmprestimo::setExemplar(ExemplarLivro* novoExemplar) { this->exemplar = novoExemplar;}


void ItemEmprestimo::setDataParaDevolucao(int novaDataParaDevolucao) { this -> dataParaDevolucao = novaDataParaDevolucao; }


void ItemEmprestimo::setDataQueFoiDevolvido(int novaDataQueFoiDevolvido) { this -> dataQueFoiDevolvido = novaDataQueFoiDevolvido; }