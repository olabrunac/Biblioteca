#include <iostream>
#include <vector>
#include "Acervo.h"
#include "GerenciadorDeEmprestimos.h"
#include "Professor.h"
#include "Aluno.h"
#include "Editora.h"
#include "Autor.h"

using std::cout;
using std::endl;
using std::vector;

int main() {

    cout << "===== INICIO DO SISTEMA =====" << endl;


    // ---------------- ENDERECO / EDITORA ----------------


    Endereco endRocco;
    endRocco.setRua("Rua Julio Diniz");
    endRocco.setNumero(56);
    endRocco.setBairro("Vila Olimpia");
    endRocco.setCidade("São Paulo");
    endRocco.setEstado("SP");
    endRocco.setCep("04547-090");

    Endereco endPanini("Alameda Caiapos", 425, "Barueri", "Sao Paulo", "SP", "06460-110");

    Editora ediRocco;
    ediRocco.setCodigo(11);
    ediRocco.setNome("Rocco");
    ediRocco.setEndereco(endRocco);

    Editora ediPanini(22, "Panini", endPanini);


    // ---------------- AUTORES ----------------


    Autor suzanne;
    suzanne.setCodigo(10);
    suzanne.setNome("Suzanne Collins");

    Autor walter(20, "Walter Tevis");
    Autor mauricio(30, "Mauricio de Souza");

    vector<Autor*> listaTodosAutores;
    listaTodosAutores.push_back(&suzanne); //passa o endereço dos autores em vez dos objetos
    listaTodosAutores.push_back(&walter);
    listaTodosAutores.push_back(&mauricio);

    vector<Autor*> listaAutoresl2 ({&walter, &mauricio}); //coloca 2 autores em uma lista

    cout << endl;
    cout << "===== AUTOR =====" << endl;
    suzanne.imprimirAutor();


    // ---------------- LIVROS ----------------


    Livro l1;                              //estatico stack
    l1.setCodigo(111);
    l1.setTitulo("Jogos Vorazes");
    l1.setEditora(ediRocco);
    l1.setAutor(vector<Autor*> {&suzanne});
    l1.criarExemplares(2);                  // poucos exemplares para testar limite

    Livro* l2 = new Livro();                //dinamico heap
    l2->setCodigo(222);
    l2->setTitulo("O Gambito da Rainha");
    l2->setEditora(ediRocco);
    l2->setAutor(listaAutoresl2);           //recebe uma lista de autores
    l2->setQuantidadeDeExemplares(1);
    l2->setNroDiasPermitidoEmprestimo(7);
    l2->criarExemplares(1);               // apenas 1 exemplar

    //estatico, codigo, titulo, exemplares, preco, editora, ano, exemplares, dias p/emprestimo, autor, paginas
    Livro l3(333, "Turma da Monica", 3, 48, ediPanini, 2021, 4, 7, vector<Autor*> {&mauricio}, 132);

    //dinamico
    Livro* l4 = new Livro(444, "Em Chamas", 2, 59.90f, ediRocco, 2026, 3, 7, vector<Autor*>{&suzanne, &mauricio}); //passando dois autores em vez de criar vetor


    // ---------------- ACERVO ----------------


    Acervo biblioteca;      //cria a biblioteca vazia (mas pode já criar com livros usando {})

    biblioteca.acrescentarLivro(&l1);        //limitado a 1 livro por adicao
    biblioteca.acrescentarLivro({l2, &l3});  //passando uma lista {} pode colocar quantos quiser

    cout << endl;
    cout << "===== LISTA DE LIVROS =====" << endl;
    biblioteca.listarTodos();


    // ---------------- USUARIOS ----------------


    Aluno Matheus;
    Matheus.setCodigo(1);
    Matheus.setNome("Matheus");

    Aluno Bruna;
    Bruna.setCodigo(2);
    Bruna.setNome("Bruna");

    Aluno Ryan(3, "Ryan");

    Professor Valter(4, "Valter");


    // ---------------- GERENCIADOR ----------------


    GerenciadorDeEmprestimos sistema;

    cout << endl;
    cout << "===== REALIZANDO EMPRESTIMOS =====" << endl;

    sistema.criarEmprestimo(Matheus, l1.getExemplarDisponivel());
    sistema.criarEmprestimo(Bruna, l1.getExemplarDisponivel());

    // Deve falhar (exemplares esgotados)
    sistema.criarEmprestimo(Ryan, l1.getExemplarDisponivel());

    sistema.criarEmprestimo(Ryan, l2.getExemplarDisponivel());

    // Tentando emprestar vários livros, o sistema verifica um por um
    sistema.criarEmprestimo(Valter, {
        l1.getExemplarDisponivel(), 
        l2->getExemplarDisponivel(),
        l3.getExemplarDisponivel(),
        l4->getExemplarDisponivel()
    });


    // ---------------- LISTAGEM ----------------


    cout << endl;
    cout << "===== EMPRESTIMOS ATUAIS =====" << endl;

    sistema.listarTodosEmprestimosAtuais();

    cout << endl;
    cout << "===== FIM DO SISTEMA =====" << endl;

    delete l2;
    delete l4;
    
    system("pause"); 
    return 0; 

}