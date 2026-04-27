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
        vector<Reserva> reservas; 
        vector<Emprestimo> emprestimos;     

    public:
        GerenciadorDeEmprestimos();

        void criarEmprestimo(Usuario& emprestimoUsuario, Livro& emprestimoLivro); //Passando por referência, pois o usuario e o exemplar já devem existirem e mais eficiente que por cópia
        void criarEmprestimoApartirDaReserva(Reserva novaReserva);

        void listarTodosEmprestimosAtuais();
        void listarReservasDoLivro(Livro& listaLivro);

        int contarEmprestimosAtivos(Livro& ativos);

        bool livroEstaDisponivel(Livro& livro);

};

#endif