#include "ItemEmprestimo.h"
#include <iostream>

using std::cout;
using std::endl;

ItemEmprestimo::ItemEmprestimo() {}

void ItemEmprestimo::imprimirItemEmprestimo() {
    cout << "Data para devolver: " << dataParaDevolucao << endl;
    cout << "Data que foi devolvido: " << dataQueFoiDevolvido << endl;
}

int ItemEmprestimo::getDataParaDevolucao() { return dataParaDevolucao; }

int ItemEmprestimo::getDataQueFoiDevolvido() { return dataQueFoiDevolvido; }

void ItemEmprestimo::setDataParaDevolucao(int novaDataParaDevolucao) { this -> dataParaDevolucao = novaDataParaDevolucao; }

void ItemEmprestimo::setDataQueFoiDevolvido(int novaDataQueFoiDevolvido) { this -> dataQueFoiDevolvido = novaDataQueFoiDevolvido; }
