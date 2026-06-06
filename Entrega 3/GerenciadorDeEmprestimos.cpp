#include "GerenciadorDeEmprestimos.h"
#include "Usuario.h"
#include "StatusEmprestimo.h"
#include <iostream>

using std::cout;
using std::endl;

GerenciadorDeEmprestimos::GerenciadorDeEmprestimos() {} 

~GerenciadorDeEmprestimos::GerenciadorDeEmprestimos() {
    for (vector<Emprestimo*>::iterator temp = emprestimos.begin(); temp != emprestimos.begin(); temp != emprestimos.end(); ++temp) {
        delete *temp;
    }
    emprestimos.clear();
}


void GerenciadorDeEmprestimos::criarEmprestimo(Usuario& emprestimoUsuario, ExemplarLivro* exemplar) {
    if (emprestimoUsuario.getStatus() != StatusUsuario::HABILITADO) {
        cout << "O usuario: '" << emprestimoUsuario.getNome();
        cout << "' nao esta habilitado para realizar emprestimos no momento." << endl;
        return;
    }
    if (exemplar == nullptr || exemplar->getStatus() != StatusEmprestimo::DISPONIVEL) {
        cout << "Nao foi possivel realizar o emprestimo para " << emprestimoUsuario.getNome() << "." << endl;
        return;
    }
    exemplar->setStatus(StatusEmprestimo::EMPRESTADO);

    ItemEmprestimo novoItem;
    novoItem.setExemplar(exemplar);

    //criação dinamica
    Emprestimo* novoEmprestimo = new Emprestimo();
    novoEmprestimo->setUsuario(&emprestimoUsuario);
    novoEmprestimo->adicionarItem(novoItem);
    novoEmprestimo->setStatus(1);
    emprestimos.push_back(novoEmprestimo);

    cout << "Emprestimo de '" << exemplar->getLivro()->getTitulo();
    cout << "' realizado com sucesso!" << endl;
}


void GerenciadorDeEmprestimos::listarTodosEmprestimosAtuais() { 
    cout << "***** Lista de Emprestimos *****" << endl;
    for (vector<Emprestimo*>::iterator temp = emprestimos.begin(); temp != emprestimos.end(); ++temp) {
        (*temp)->imprimirEmprestimo();
    }
}


int GerenciadorDeEmprestimos::contarEmprestimosAtivos(Livro& livro) {  
    int contador = 0;
    for (const Emprestimo& temp : emprestimos) {
        for (const ItemEmprestimo& item : temp.getItens()) {
            if (item.getExemplar()->getStatus() == StatusEmprestimo::EMPRESTADO) {
                if (item.getExemplar()->getLivro()->getCodigo() == livro.getCodigo()) {
                    contador++;
                }
            }
        }
    }
    return contador; 
}

/*
// Secao que esta comentada de proposito, provavel escopo para funcionalidades futuras
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
