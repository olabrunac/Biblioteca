#include "GerenciadorDeEmprestimos.h"
#include "Usuario.h"
#include <iostream>

using std::cout;
using std::endl;

GerenciadorDeEmprestimos::GerenciadorDeEmprestimos() {}


void GerenciadorDeEmprestimos::criarEmprestimo(Usuario& emprestimoUsuario, Livro& emprestimoLivro) {
    if (emprestimoUsuario.getStatus() != StatusUsuario::HABILITADO) {

        cout << "O usuario: '" << emprestimoUsuario.getNome();
        cout << "' não está habilitado para realizar empréstimos no momento." << endl;

        return;
        
    }

    //Lógica para verificar exemplares disponiveis

    int TotalExemplares = emprestimoLivro.getQuantidadeDeExemplares();
    int ExemplaresEmprestados = 0;

    // Percorre o histórico para contar quantos exemplares deste livro já saíram
    for (const Emprestimo& temp : emprestimos) {
        for (const ItemEmprestimo& item : temp.getItens()) {
            
            // Verifica se o item pertence ao livro X e se está emprestado
            if (item.getExemplar()->getLivro()->getCodigo() == emprestimoLivro.getCodigo()) {
                
                if (item.getExemplar()->getStatus() == StatusParaEmprestimo::EMPRESTADO) {
                    ExemplaresEmprestados++;
                }
            }
        }
    }

    //Comparar os emprestados com o total
   if (ExemplaresEmprestados >= TotalExemplares) {

        cout << "Não há exemplares disponíveis para o livro: "
             << emprestimoLivro.getTitulo() << endl;

        return;
    
    }

    Emprestimo novoEmprestimo;

    novoEmprestimo.setUsuario(&emprestimoUsuario);
    novoEmprestimo.setItens(emprestimoLivro);
    novoEmprestimo.setStatus(1);
    emprestimos.push_back(novoEmprestimo);

    cout << "Emprestimo de '" << emprestimoLivro.getTitulo();
    cout << "' realizado para: "
         << emprestimoUsuario.getNome() << endl;
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