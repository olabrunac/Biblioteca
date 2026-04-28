#include <iostream>
#include <vector>
#include "Acervo.h"
#include "GerenciadorDeEmprestimos.h"
//#include "Professor.h"
#include "Editora.h"
#include "Autor.h"

using std::cout;
using std::endl;
using std::vector;

int main() {

    cout << "===== INICIO DO SISTEMA =====" << endl;

    // ---------------- ENDERECO / EDITORA ----------------

    Endereco endRocco;
    endRocco.setRua("Av. Paulista");
    endRocco.setCidade("São Paulo");

    Editora ediRocco;
    ediRocco.setNome("Rocco");
    ediRocco.setEndereco(endRocco);

    // ---------------- AUTORES ----------------

    Autor suzanne;
    suzanne.setCodigo(10);
    suzanne.setNome("Suzanne Collins");

    vector<Autor> listaAutores;
    listaAutores.push_back(suzanne);

    cout << endl;
    cout << "===== AUTOR =====" << endl;
    suzanne.imprimirAutor();

    // ---------------- LIVROS ----------------

    Livro l1;
    l1.setCodigo(111);
    l1.setTitulo("Jogos Vorazes");
    l1.setEditora(ediRocco);
    l1.setAutor(listaAutores);
    l1.criarExemplares(2); // poucos exemplares para testar limite

    Livro l2;
    l2.setCodigo(123);
    l2.setTitulo("O Gambito da Rainha");
    l2.setEditora(ediRocco);
    l2.setAutor(listaAutores);
    l2.criarExemplares(1); // apenas 1 exemplar

    // ---------------- ACERVO ----------------

    Acervo biblioteca;

    biblioteca.acrescentarLivro(l1);
    biblioteca.acrescentarLivro(l2);

    cout << endl;
    cout << "===== LISTA DE LIVROS =====" << endl;
    biblioteca.listarTodos();

    // ---------------- USUARIOS ----------------

    Usuario Matheus;
    Matheus.setCodigo(1);
    Matheus.setNome("Matheus");

    Usuario Bruna;
    Bruna.setCodigo(2);
    Bruna.setNome("Bruna");

    Usuario Ryan;
    Ryan.setCodigo(3);
    Ryan.setNome("Ryan");

    Usuario Ana;
    Ana.setCodigo(4);
    Ana.setNome("Ana");

    // ---------------- GERENCIADOR ----------------

    GerenciadorDeEmprestimos sistema;

    cout << endl;
    cout << "===== REALIZANDO EMPRESTIMOS =====" << endl;

    sistema.criarEmprestimo(Matheus, l1);
    sistema.criarEmprestimo(Bruna, l1);

    // Deve falhar (exemplares esgotados)
    sistema.criarEmprestimo(Ryan, l1);

    sistema.criarEmprestimo(Ana, l2);

    // Deve falhar (apenas 1 exemplar)
    sistema.criarEmprestimo(Ryan, l2);

    // ---------------- LISTAGEM ----------------

    cout << endl;
    cout << "===== EMPRESTIMOS ATUAIS =====" << endl;

    sistema.listarTodosEmprestimosAtuais();

    cout << endl;
    cout << "===== FIM DO SISTEMA =====" << endl;

    system("pause");

    return 0;
}