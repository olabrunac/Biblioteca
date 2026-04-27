#include "GerenciadorDeEmprestimos.h"
#include "Usuario.h"
#include <iostream>

using std::cout;
using std::endl;

GerenciadorDeEmprestimos::GerenciadorDeEmprestimos() {}


void GerenciadorDeEmprestimos::criarEmprestimo(Usuario& emprestimoUsuario, Livro& emprestimoLivro) {
    if (emprestimoLivro.getQuantidadeDeExemplares() > 0) {
        Emprestimo emp;
        emp.setStatus(1);
        emprestimos.push_back(emp);
        cout << "Emprestimo realizado para: " << emprestimoUsuario.getNome() << endl;
    } else {
        cout << "ERRO: O livro: " << emprestimoLivro.getTitulo() << " não possui exemplares." << endl;
    }
}


void GerenciadorDeEmprestimos::listarTodosEmprestimosAtuais() {
    cout << "***** Lista de Emprestimos *****" << endl;
    for (auto& e : emprestimos) {
        e.imprimirEmprestimo();
    }
}


int GerenciadorDeEmprestimos::contarEmprestimosAtivos(Livro& livro) {
    int contador = 0;
    for (const Emprestimo& temp : emprestimos) {
        for (const ItemEmprestimo& item : temp.getItens()) {
            if (item.getExemplar()->getStatus() == StatusEmprestimo::EMPRESTADO) {
                contador++;
            }
        }
    }
    return contador;
}

/*
void GerenciadorDeEmprestimos::criarReserva(Usuario emprestimoUsuario, Livro emprestimoLivro, Reserva novaData) {
    this -> reservas.push_back(novaData);
    cout << "Reserva do livro: " << emprestimoLivro.getTitulo() << endl;
}

void GerenciadorDeEmprestimos::criarEmprestimoApartirDaReserva(Reserva novaReserva) {

}

void GerenciadorDeEmprestimos::listarTodasReservas() {
    cout << "----- Lista de Reservas -----" << endl;
    for (Reserva& temp : reservas) {
        temp.imprimirReserva();
    } cout << endl;
}
*/