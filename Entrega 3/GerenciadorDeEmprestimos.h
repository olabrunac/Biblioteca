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
        vector<Reserva*> reservas; 
        vector<Emprestimo> emprestimos;   //*****MUDAR PARA PONTEIRO, VER ALTERAÇÕES NECESSÁRIAS */  

    public:
        GerenciadorDeEmprestimos();

        void criarEmprestimo(Usuario& emprestimoUsuario, ExemplarLivro* exemplar);
        //void criarEmprestimoApartirDaReserva(Reserva novaReserva);

        /*void criarReserva(Usuario& usuario, Livro& livro, Data data);*/
        void listarTodosEmprestimosAtuais();
        //void listarReservasDoLivro(Livro& listaLivro);
        /*void ListarTodasReservas() CRIAR ISSO    */
        int contarEmprestimosAtivos(Livro& ativos);

};

#endif