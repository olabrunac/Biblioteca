#include <iostream>
#include <vector>
#include "Acervo.h"
#include "GerenciadorDeEmprestimos.h"
#include "Professor.h"
#include "Editora.h"
#include "Autor.h"

using std::cout;
using std::endl;
using std::vector;

int main() {
    
    Endereco endRocco;
    endRocco.setRua("Av. Paulista");
    endRocco.setCidade("São Paulo");

    Editora ediRocco;
    ediRocco.setNome("Rocco");
    ediRocco.setEndereco(endRocco);

    Autor suzanne;
    suzanne.setNome("Suzanne Collins");

    vector<Autor> listaAutores;
    listaAutores.push_back(suzanne);

    Livro l1;
    l1.setCodigo(111);
    l1.setTitulo("Jogos Vorazes");
    l1.setEditora(ediRocco);
    l1.setAutor(listaAutores);
    l1.criarExemplares(5);

    Acervo bilioteca;
    biblioteca.acrescentarLivro(l1);

    biblioteca.listarTodos();

    Professor valter;
    valter.setNome("Valter");
    valter.setCodigo(111);

    GerenciadorDeEmprestimos sistema;
    sistema.criarEmprestimo(valter, l1);

    sistema.listarTodosEmprestimosAtuais();

}