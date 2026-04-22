#ifndef GERENCIADORDEEMPRESTIMOS_H
#define GERENCIADORDEEMPRESTIMOS_H

#include "Usuario.h"
#include "Livro.h"
#include "Emprestimo.h"
#include "Reserva.h"
#include <vector>

using std::vector;

class GerenciadorDeEmprestimos {
    private:
        vector<Reserva> reserva; 
        vector<Emprestimo> emprestimo;     

    public:
        GerenciadorDeEmprestimos();

        void criarReserva(Usuario emprestimoUsuario, Livro emprestimoLivro, Reserva novaData);
        void criarEmprestimo(Usuario emprestimoUsuario, Livro emprestimoLivro);
        void criarEmprestimoApartirDaReserva(Reserva novaReserva);

        void listarTodosEmprestimosAtuais();
        void listarTodasReservas();
        void listarReservasDoLivro(Livro listaLivro);

};

#endif