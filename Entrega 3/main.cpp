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


    Endereco endRocco ("Rua Julio Diniz", 56, "Vila Olimpia", "São Paulo", "SP", "04547-090");

    Endereco endPanini("Alameda Caiapos", 425, "Barueri", "Sao Paulo", "SP", "06460-110");

    Editora ediRocco;
    ediRocco.setCodigo(11);
    ediRocco.setNome("Rocco");
    ediRocco.setEndereco(endRocco);

    Editora ediPanini(22, "Panini", endPanini);


    // ---------------- AUTORES ----------------


    Autor suzanne; suzanne.setCodigo(10); suzanne.setNome("Suzanne Collins");

    Autor walter(20, "Walter Tevis");

    Autor mauricio(30, "Mauricio de Souza");

    vector<Autor*> listaTodosAutores ( {&suzanne, &walter, &mauricio} ); //coloca varios autores em uma lista

    vector<Autor*> listaAutoresl2 ({&walter});
    listaAutoresl2.push_back({ &mauricio });

    /*
    cout << "===== AUTOR =====" << endl;
    //suzanne.imprimirAutor();                          //olha pra suzanne e imprime os dados lá dentro
    Autor::imprimirTodos(listaTodosAutores);            //static olha para Autor e imprime os dados dos autores que estao dentro do vetor indicado
    cout << endl;
    */


    // ---------------- LIVROS ----------------


    Livro* l1 = new Livro(111, "Jogos Vorazes", ediRocco, vector<Autor*> {&suzanne}, 2);       //dinamico heap, 2 exemplares para testar limite
    l1->setNroDiasPermitidoEmprestimo(2);

    Livro* l2 = new Livro(222, "O Gambito da Rainha", ediRocco, listaAutoresl2, 1);           //recebe uma lista de autores, 1 exemplar
    l2->setNroDiasPermitidoEmprestimo(2);

    //dinamico
    Livro* l3 = new Livro(333, "Turma da Monica", 3, 4.99f, ediPanini, 2021, 4, 7, vector<Autor*> {&mauricio}, 132);

    Livro* l4 = new Livro(444, "Em Chamas", 2, 59.90f, ediRocco, 2026, 3, 7, vector<Autor*> { & suzanne, &mauricio }, 400); //passando dois autores em vez de criar vetor

    //nasce com 0 exemplares, portanto indisponivel desde o inicio
    Livro* l5 = new Livro(555, "O Homem Que Caiu na Terra", 1, 49.90f, ediRocco, 1963, 0, 7, vector<Autor*> { &walter }, 256);


    // ---------------- ACERVO ----------------


    Acervo biblioteca;      //cria a biblioteca vazia (mas pode já criar com livros usando {})

    biblioteca.acrescentarLivro(l1);        //limitado a 1 livro por adicao
    biblioteca.acrescentarLivro({l2, l3, l4, l5});  //passando uma lista {} pode colocar quantos quiser

    cout << endl;
    //cout << "===== LISTA DE LIVROS =====" << endl;
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

    Professor Backes(5, "Backes"); //Testando disponibilidade Turma da Monica

    Aluno Joao(6, "Joao");

    Aluno Mairon(7, "Mairon");

    Aluno Felipe(8, "Felipe");




    // ---------------- GERENCIADOR ----------------


    GerenciadorDeEmprestimos sistema;

    Data dataHoje(10, 06, 2026);

    cout << endl << endl;
    cout << "===== REALIZANDO EMPRESTIMOS =====" << endl;

    sistema.criarEmprestimo(Matheus, l1->getExemplarDisponivel(), dataHoje);
    sistema.criarEmprestimo(Bruna, l1->getExemplarDisponivel(), dataHoje);
    cout << endl;

    // Deve falhar (exemplares esgotados)
    sistema.criarEmprestimo(Ryan, l1->getExemplarDisponivel(), dataHoje);
    cout << endl;

    // Deve falhar imediatamente (o l5 nasceu com 0 exemplares, retornara nullptr)
    sistema.criarEmprestimo(Bruna, l5->getExemplarDisponivel(), dataHoje);
    cout << endl;

    // Tentando emprestar vários livros, o sistema verifica um por um
    sistema.criarEmprestimo(Valter, {
        l1->getExemplarDisponivel(),            //jogos vorazes
        l2->getExemplarDisponivel(),            //gambito da rainha
        l3->getExemplarDisponivel(),            //turma da monica
        l4->getExemplarDisponivel(),            //em chamas
        l5->getExemplarDisponivel()             //o homem que caiu na terra
    }, dataHoje);
    cout << endl;

    Ryan.setStatus(StatusUsuario::EM_DEBITO);
    sistema.criarEmprestimo(Ryan, l4->getExemplarDisponivel(), dataHoje);
    cout << endl; 


    // ---------------- RESERVAS ----------------


    cout << endl;
    cout << "===== TESTANDO SISTEMA DE RESERVAS =====" << endl;
    
    // 1. Criando Reservas
    sistema.criarReserva(&Ryan, l3, dataHoje);  // Ryan reserva Turma da Monica (tem muito estoque)
    sistema.criarReserva(&Bruna, l5, dataHoje); // Bruna reserva l5 (estoque zerado)
    sistema.criarReserva(&Backes, l3, dataHoje);
    sistema.criarReserva(&Joao,l3, dataHoje);
    sistema.criarReserva(&Mairon,l3, dataHoje);
    sistema.criarReserva(&Felipe,l3, dataHoje);
    sistema.criarReserva(&Joao,l3, dataHoje);




    cout << endl;
    sistema.listarTodasReservas();

    cout << endl;
    cout << "===== CONVERTENDO RESERVA EM EMPRESTIMO =====" << endl;
    
    // 2. Convertendo a reserva do Ryan (Deve dar certo)
    Reserva* reservaRyan = sistema.getReservaPorUsuario(&Ryan);
    if (reservaRyan != nullptr) {
        sistema.criarEmprestimoApartirDaReserva(reservaRyan);
    }

    // 3. Convertendo a reserva da Bruna (Deve falhar no método, pois l5 não tem exemplar físico)
    Reserva* reservaBruna = sistema.getReservaPorUsuario(&Bruna);
    if (reservaBruna != nullptr) {
        sistema.criarEmprestimoApartirDaReserva(reservaBruna);
    }

    // ---------------- LISTAGEM ----------------


    cout << endl;
    cout << "===== EMPRESTIMOS ATUAIS =====" << endl;

    sistema.listarTodosEmprestimosAtuais();
    sistema.listarTodasReservasUsuario(&Backes);

    cout << endl;
    cout << "===== FIM DO SISTEMA =====" << endl;

    // delete l1, l2, l3, l4, l5; // O Acervo eh dono do l1, l2, l3, l4 e l5. Ele limpa a memoria sozinho!
  
    
    system("pause"); 
    return 0; 

}