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

    // -------------------- SETUP: DADOS INICIAIS --------------------
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

    vector<Autor*> listaAutoresl2 ({&walter});
    listaAutoresl2.push_back({ &mauricio });

    // ---------------- LIVROS ----------------


    Livro* l1 = new Livro(111, "Jogos Vorazes", ediRocco, vector<Autor*> {&suzanne}, 2);       // Livro com 2 exemplares para testar limite.
    l1->setNroDiasPermitidoEmprestimo(2);

    Livro* l2 = new Livro(222, "O Gambito da Rainha", ediRocco, listaAutoresl2, 1);           // Livro com 1 exemplar.
    l2->setNroDiasPermitidoEmprestimo(2);

    Livro* l3 = new Livro(333, "Turma da Monica", 3, 4.99f, ediPanini, 2021, 4, 7, vector<Autor*> {&mauricio}, 132);

    Livro* l4 = new Livro(444, "Em Chamas", 2, 59.90f, ediRocco, 2026, 3, 7, vector<Autor*> { & suzanne, &mauricio }, 400);

    // Livro com 0 exemplares, nasce indisponível.
    Livro* l5 = new Livro(555, "O Homem Que Caiu na Terra", 1, 49.90f, ediRocco, 1963, 0, 7, vector<Autor*> { &walter }, 256);


    // ---------------- ACERVO ----------------


    Acervo biblioteca;

    biblioteca.acrescentarLivro(l1);        // Adiciona um livro ao acervo.
    biblioteca.acrescentarLivro({l2, l3, l4, l5});  // Adiciona múltiplos livros de uma vez (sobrecarga de método).

    cout << endl;
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




    // -------------------- TESTES DE FUNCIONALIDADES --------------------


    GerenciadorDeEmprestimos sistema;

    Data dataHoje(10, 06, 2026);

    cout << endl << endl;
    cout << "===== TESTE 1: CRIAÇÃO DE EMPRÉSTIMOS DIRETOS =====" << endl;

    sistema.criarEmprestimo(Matheus, l1->getExemplarDisponivel(), dataHoje);
    sistema.criarEmprestimo(Bruna, l1->getExemplarDisponivel(), dataHoje);
    cout << endl;

    // TENTATIVA DE FALHA: Livro com exemplares esgotados.
    sistema.criarEmprestimo(Ryan, l1->getExemplarDisponivel(), dataHoje);
    cout << endl;

    // TENTATIVA DE FALHA: Livro que nunca teve exemplares.
    sistema.criarEmprestimo(Bruna, l5->getExemplarDisponivel(), dataHoje);
    cout << endl;

    // Empréstimo de múltiplos livros para um Professor.
    sistema.criarEmprestimo(Valter, {
        l1->getExemplarDisponivel(),            //jogos vorazes
        l2->getExemplarDisponivel(),            //gambito da rainha
        l3->getExemplarDisponivel(),            //turma da monica
        l4->getExemplarDisponivel(),            //em chamas
        l5->getExemplarDisponivel()             //o homem que caiu na terra
    }, dataHoje);
    cout << endl;

    // TENTATIVA DE FALHA: Usuário com status EM_DEBITO tenta criar empréstimo.
    Ryan.setStatus(StatusUsuario::EM_DEBITO);
    sistema.criarEmprestimo(Ryan, l4->getExemplarDisponivel(), dataHoje);
    cout << endl; 


    // -------------------- TESTE 2: CRIAÇÃO DE RESERVAS --------------------


    cout << endl;
    cout << "===== TESTANDO SISTEMA DE RESERVAS =====" << endl;
    
    // Criação de reservas para diferentes usuários e livros.
    sistema.criarReserva(&Ryan, l3, dataHoje);  // Ryan (em débito) reserva um livro.
    sistema.criarReserva(&Bruna, l5, dataHoje); // Bruna reserva um livro sem estoque.

    // Testes adicionais de reserva para o mesmo livro.
    sistema.criarReserva(&Backes, l3, dataHoje);
    sistema.criarReserva(&Joao,l3, dataHoje);
    sistema.criarReserva(&Mairon,l3, dataHoje);
    sistema.criarReserva(&Felipe,l3, dataHoje);
    // TENTATIVA DE FALHA: João tenta reservar o mesmo livro duas vezes.
    sistema.criarReserva(&Joao,l3, dataHoje); 

    cout << endl;
    sistema.listarTodasReservas();

    cout << endl;
    cout << "===== CONVERTENDO RESERVA EM EMPRESTIMO =====" << endl;
    
    // TENTATIVA DE FALHA: Converter reserva de usuário em débito.
    Reserva* reservaRyan = sistema.getReservaPorUsuario(&Ryan);
    if (reservaRyan != nullptr) {
        sistema.criarEmprestimoApartirDaReserva(reservaRyan, dataHoje);
    }

    // TENTATIVA DE FALHA: Converter reserva de livro sem estoque.
    Reserva* reservaBruna = sistema.getReservaPorUsuario(&Bruna);
    if (reservaBruna != nullptr) {
        sistema.criarEmprestimoApartirDaReserva(reservaBruna, dataHoje);
    }

    // ---------------- LISTAGEM ----------------


    cout << endl;
    cout << "===== EMPRESTIMOS ATUAIS =====" << endl;

    sistema.listarTodosEmprestimosAtuais();
    // CONSULTA: Visualização de todas as reservas de um determinado usuário.
    sistema.listarTodasReservasUsuario(&Backes);

    // -------------------- TESTE 3: REGRAS DE NEGÓCIO E CONSULTAS --------------------

    cout << endl;
    cout << "===== TESTANDO REGRAS DE NEGOCIO E CONSULTAS =====" << endl;

    // REGRA DE NEGÓCIO: Não permitir exclusão de livro emprestado.
    cout << "\nTentando remover 'Jogos Vorazes' (emprestado)..." << endl;
    if (sistema.contarEmprestimosAtivos(*l1) > 0 || sistema.contarReservasAtivas(*l1) > 0) {
        cout << "ERRO: Livro nao pode ser removido pois possui emprestimos ou reservas ativas." << endl;
    } else {
        biblioteca.removerDoAcervo(l1);
    }

    // REGRA DE NEGÓCIO: Não permitir exclusão de livro reservado.
    cout << "\nTentando remover 'O Homem Que Caiu na Terra' (reservado por Bruna)..." << endl;
    if (sistema.contarEmprestimosAtivos(*l5) > 0 || sistema.contarReservasAtivas(*l5) > 0) {
        cout << "ERRO: Livro nao pode ser removido pois possui emprestimos ou reservas ativas." << endl;
    } else {
        biblioteca.removerDoAcervo(l5);
    }

    // CONSULTAS EXIGIDAS:
    sistema.listarEmprestimosDoUsuario(&Valter);
    sistema.listarEmprestimosDoLivro(*l2);
    sistema.listarReservasDoLivro(*l5);

    cout << endl;
    cout << "===== FIM DO SISTEMA =====" << endl;

    // O destrutor do objeto 'biblioteca' (classe Acervo) é chamado aqui,
    // liberando a memória de todos os Livros* que foram alocados dinamicamente.
    return 0; 

}