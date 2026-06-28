#include "ItemEmprestimo.h"
#include "ExemplarLivro.h"
#include <iostream>

using std::cout;
using std::endl;


ItemEmprestimo::ItemEmprestimo() : exemplar(nullptr), dataQueFoiDevolvido(0) {}


void ItemEmprestimo::imprimirItemEmprestimo()const {
    if (exemplar != nullptr) {
        exemplar->imprimirExemplarLivro(dataParaDevolucao.getDataInteira());
    }
}


//-------------------- sets e gets --------------------


ExemplarLivro* ItemEmprestimo::getExemplar() const { return exemplar; }


Data ItemEmprestimo::getDataParaDevolucao() const { return dataParaDevolucao; }


int ItemEmprestimo::getDataQueFoiDevolvido() const { return dataQueFoiDevolvido; }


Livro* ItemEmprestimo::getLivro() const{
    if (exemplar != nullptr) {
        return exemplar->getLivro();
    }
    return nullptr;
}


void ItemEmprestimo::setExemplar(ExemplarLivro* novoExemplar) { this->exemplar = novoExemplar;}


void ItemEmprestimo::setDataParaDevolucao(Data novaDataParaDevolucao) { this -> dataParaDevolucao = novaDataParaDevolucao; }


void ItemEmprestimo::setDataQueFoiDevolvido(int novaDataQueFoiDevolvido) { this -> dataQueFoiDevolvido = novaDataQueFoiDevolvido; }
