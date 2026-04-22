#include "GerenciadorDeEmprestimos.h"
#include "Usuario.h"
#include <iostream>

using std::cout;
using std::endl;

GerenciadorDeEmprestimos::GerenciadorDeEmprestimos() {}

void GerenciadorDeEmprestimos::criarReserva(Usuario emprestimoUsuario, Livro emprestimoLivro, Reserva novaData) {
    this -> reserva.push_back(novaData);
    cout << "Reserva do livro: " << emprestimoLivro.getTitulo() << endl;
}

void GerenciadorDeEmprestimos::criarEmprestimo(Usuario emprestimoUsuario, Livro emprestimoLivro) {
    if (emprestimoLivro.getQuantidadeDeExemplares() > 0) {
        Emprestimo emp;
        emp.setDataDeRetirada(30042026);
        emp.setStatus(1);
        emprestimo.push_back(emp);
        cout << "Emprestimo realizado para: " << emprestimoUsuario.getNome() << endl;
    } else {
        cout << "ERRO: O livro: " << emprestimoLivro.getTitulo() << " não possui exemplares." << endl;
    }
}

void GerenciadorDeEmprestimos::criarEmprestimoApartirDaReserva(Reserva novaReserva) {

}

void GerenciadorDeEmprestimos::listarTodosEmprestimosAtuais() {
    cout << "***** Lista de Emprestimos *****" << endl;
    for (Auto& e : emprestimo) {
        e.imprimirEmprestimo();
    }
}

void GerenciadorDeEmprestimos::listarTodasReservas() {
    cout << "----- Lista de Reservas -----" << endl;
    for (Reserva& temp : reserva) {
        temp.imprimirReserva();
    } cout << endl;
}

void GerenciadorDeEmprestimos::listarReservasDoLivro(Livro listaLivro) {
    cout << "Reservas para o livro: " << listaLivro.getTitulo() << endl;
}