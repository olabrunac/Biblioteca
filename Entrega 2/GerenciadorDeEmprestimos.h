#ifndef GERENCIADORDEEMPRESTIMOS_H
#define GERENCIADORDEEMPRESTIMOS_H

#include "Usuario.h"
#include "Livro.h"
#include "Emprestimo.h"
//#include "Reserva.h"
#include <vector>

using std::vector;

class GerenciadorDeEmprestimos {
    private:
        //vector<Reserva> reservas; 
        vector<Emprestimo> emprestimos;     

    public:
        GerenciadorDeEmprestimos();

        void criarEmprestimo(Usuario& emprestimoUsuario, ExemplarLivro* exemplar); // Simplifica o código apenas checando se tem exemplar disponivel,
        //void criarEmprestimoApartirDaReserva(Reserva novaReserva);

        void listarTodosEmprestimosAtuais();
        //void listarReservasDoLivro(Livro& listaLivro);

        int contarEmprestimosAtivos(Livro& ativos);

};

#endif