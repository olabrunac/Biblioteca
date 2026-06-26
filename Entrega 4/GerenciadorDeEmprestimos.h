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
        void criarEmprestimoApartirDaReserva(Reserva* reservaExistente, const Data& dataAtual);

        void criarReserva(Usuario* reservaUsuario, Livro* reservaLivro, Data& dataRealizacao);
        void listarTodosEmprestimosAtuais();
        void listarReservasDoLivro(Livro& listaLivro);
        void listarTodasReservas();
        void listarTodasReservasUsuario(Usuario* usuario) const;
        int contarEmprestimosAtivos(Livro& ativos) const;
        int contarReservasAtivas(Livro& livro) const;

        void listarEmprestimosDoUsuario(Usuario* usuario);
        void listarEmprestimosDoLivro(Livro& livro);

        bool realizarDevolucao(Usuario* usuario, int codigoLivro, const Data& dataDevolucao);
        bool cancelarReservaItem(Usuario* usuario, int codigoLivro);
        bool usuarioTemPendencias(Usuario* usuario) const;

        void atualizaPendenciasEmprestimos(Data& dataFutura);


        bool estaDisponivelnaData(Livro* testeLivro, const Data& dataInicial, const Data& dataFinal);
        Reserva* getReservaPorUsuario(Usuario* usuarioBuscado) const;
        Emprestimo* getEmprestimoPorUsuario(Usuario* usuarioBuscado) const;

};

#endif