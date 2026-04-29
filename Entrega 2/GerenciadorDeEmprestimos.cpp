#include "GerenciadorDeEmprestimos.h"
#include "Usuario.h"
#include <iostream>

using std::cout;
using std::endl;

GerenciadorDeEmprestimos::GerenciadorDeEmprestimos() {}


void GerenciadorDeEmprestimos::criarEmprestimo(Usuario& emprestimoUsuario, ExemplarLivro* exemplar) {
    if (emprestimoUsuario.getStatus() != StatusUsuario::HABILITADO) {                               // valida se o usuário pode fazer emprestimos
        cout << "O usuario: '" << emprestimoUsuario.getNome();
        cout << "' nao esta habilitado para realizar emprestimos no momento." << endl;
        return;
    }
    if (exemplar == nullptr || exemplar->getStatus() != StatusParaEmprestimo::DISPONIVEL) {         // valida se o exemplar está disponivel
        cout << "Nao foi possivel realizar o emprestimo para " << emprestimoUsuario.getNome() << "." << endl;
        return;
    }
    exemplar->setStatus(StatusParaEmprestimo::EMPRESTADO);

    ItemEmprestimo novoItem;
    novoItem.setExemplar(exemplar);                                                                 //vincula o novoItem ao exemplar que está sendo emprestado

    Emprestimo novoEmprestimo;
    novoEmprestimo.setUsuario(&emprestimoUsuario);
    novoEmprestimo.adicionarItem(novoItem); 
    novoEmprestimo.setStatus(1);
    emprestimos.push_back(novoEmprestimo);                                                          //adiciona o novoItem na lista de itens dentro do novoEMprestimo

    cout << "Emprestimo de '" << exemplar->getLivro()->getTitulo();
    cout << "' realizado para: "
         << emprestimoUsuario.getNome() << endl;
}


void GerenciadorDeEmprestimos::listarTodosEmprestimosAtuais() {
    cout << "***** Lista de Emprestimos *****" << endl;
    for (auto& temp : emprestimos) {
        temp.imprimirEmprestimo();
    }
}


int GerenciadorDeEmprestimos::contarEmprestimosAtivos(Livro& livro) {
    int contador = 0;
    for (const Emprestimo& temp : emprestimos) {
        for (const ItemEmprestimo& item : temp.getItens()) {
            if (item.getExemplar()->getStatus() == StatusParaEmprestimo::EMPRESTADO) {
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
