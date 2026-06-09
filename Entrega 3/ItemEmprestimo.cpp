#include "ItemEmprestimo.h"
#include "ExemplarLivro.h"
#include <iostream>

using std::cout;
using std::endl;

ItemEmprestimo::ItemEmprestimo(){}

void ItemEmprestimo::imprimirItemEmprestimo()const {
    if (exemplar != nullptr) {
        exemplar->imprimirExemplarLivro(dataParaDevolucao.getDataInteira());
    }
}

Livro* ItemEmprestimo::getLivro() const{
    

    return exemplar->getLivro();


}

ExemplarLivro* ItemEmprestimo::getExemplar() const { return exemplar; }


Data ItemEmprestimo::getDataParaDevolucao() { return dataParaDevolucao; }


Data ItemEmprestimo::getDataQueFoiDevolvido() { return dataQueFoiDevolvido; }

void ItemEmprestimo::setExemplar(ExemplarLivro* novoExemplar) { this->exemplar = novoExemplar;}


void ItemEmprestimo::setDataParaDevolucao(Data novaDataParaDevolucao) { this -> dataParaDevolucao = novaDataParaDevolucao; }


void ItemEmprestimo::setDataQueFoiDevolvido(Data novaDataQueFoiDevolvido) { this -> dataQueFoiDevolvido = novaDataQueFoiDevolvido; }
