#ifndef GERENCIADORDEEMPRESTIMOS_H
#define GERENCIADORDEEMPRESTIMOS_H

#include "Usuario.h"
#include "Professor.h"
#include "Aluno.h"
#include "Livro.h"
#include "Emprestimo.h"
#include "Data.h"
#include "Reserva.h"
#include <vector>
#include <initializer_list>

using std::vector;
using std::initializer_list;


class GerenciadorDeEmprestimos {
    private:
        vector<Reserva*> reservas; 
        vector<Emprestimo*> emprestimos;   //ponteiro 

    public:
        GerenciadorDeEmprestimos();
        ~GerenciadorDeEmprestimos();

        void criarEmprestimo(Usuario& emprestimoUsuario, ExemplarLivro* exemplar, const Data& dataAtual);
        void criarEmprestimo(Usuario& emprestimoUsuario, initializer_list<ExemplarLivro*> listaExemplares, const Data& dataAtual);
        void criarEmprestimoApartirDaReserva(Reserva* reservaExistente);

        void criarReserva(Usuario* reservaUsuario, Livro* reservaLivro, Data& dataRealizacao); //reserva com uma data int, aprimorar depois
        void listarTodosEmprestimosAtuais();
        //void listarReservasDoLivro(Livro& listaLivro);
        void listarTodasReservas();
        void listarTodasReservasUsuario(Usuario* usuario);
        int contarEmprestimosAtivos(Livro& ativos);


        bool estaDisponivelnaData(Livro* testeLivro, const Data& dataInicial, const Data& dataFinal);
        Reserva* getReservaPorUsuario(Usuario* usuarioBuscado);

};

#endif