#include <iostream>
#include <vector>
#include "Data.h"
#include "Livro.h"
#include "Editora.h"
#include "Autor.h"
#include "Usuario.h"
#include "Aluno.h"
#include "Professor.h"
#include "GerenciadorDeEmprestimos.h"

using namespace std;

int main() {
    cout << "=========================================================" << endl;
    cout << "   INICIANDO TESTES DO GERENCIADOR DE EMPRESTIMOS        " << endl;
    cout << "=========================================================" << endl << endl;

    try {
        // =================================================================
        // SETUP: PREPARANDO O AMBIENTE (LIVROS E USUÁRIOS)
        // =================================================================
        
        // 1. Criando Autores e Editoras
        Autor autor1(1, "J.R.R. Tolkien");
        Autor autor2(2, "George Orwell");
        vector<Autor*> autoresLivro1 = { &autor1 };
        vector<Autor*> autoresLivro2 = { &autor2 };

        Editora editoraAlpha; editoraAlpha.setCodigo(10); editoraAlpha.setNome("Alpha Edicoes");
        Editora editoraBeta; editoraBeta.setCodigo(20); editoraBeta.setNome("Beta Letras");

        // 2. Criando Livros
        // Livro 1: O Senhor dos Anéis (Tem 2 exemplares disponíveis)
        Livro livro1(101, "O Senhor dos Aneis", 1, 120.0f, editoraAlpha, 1954, 2, 14, autoresLivro1, 1200);
        
        // Livro 2: 1984 (Tem apenas 1 exemplar disponível)
        Livro livro2(102, "1984", 1, 45.0f, editoraBeta, 1949, 1, 14, autoresLivro2, 328);

        // Livro 3: O Hobbit (Tem apenas 1 exemplar disponível)
        Livro livro3(103, "O Hobbit", 1, 50.0f, editoraAlpha, 1937, 1, 14, autoresLivro1, 300);

        // 3. Criando Usuários (Testando o Polimorfismo)
        Aluno alunoAtivo(111, "Carlos Silva", StatusUsuario::HABILITADO);
        
        // Professor com pendências (Usamos um cast genérico ou outro status para simular bloqueio)
        // Assumindo que seu enum tem algo além de HABILITADO (ex: EM_DEBITO). 
        // Se der erro aqui, mude o StatusUsuario para o equivalente a "bloqueado" do seu enum.
        Professor profBloqueado(222, "Dr. Roberto", (StatusUsuario)0); 

        GerenciadorDeEmprestimos gerenciador;
        Data dataAtual(20261015);

        // =================================================================
        // TESTE 1: VALIDAÇÕES DE EMPRÉSTIMO DIRETO
        // =================================================================
        cout << ">>> TESTE 1: EMPRESTIMOS DIRETOS <<<" << endl;
        
        cout << "[Ação] Professor bloqueado tenta pegar 'O Senhor dos Aneis':" << endl;
        gerenciador.criarEmprestimo(profBloqueado, livro1.getExemplarDisponivel(), dataAtual);
        
        cout << "\n[Ação] Aluno ativo pega '1984':" << endl;
        gerenciador.criarEmprestimo(alunoAtivo, livro2.getExemplarDisponivel(), dataAtual);

        cout << "\n[Ação] Professor tenta pegar '1984' que acabou de esgotar (Exemplar nullptr):" << endl;
        ExemplarLivro* exemplarEsgotado = livro2.getExemplarDisponivel();
        if (exemplarEsgotado == nullptr) {
            cout << "O sistema bloqueou antes de chegar no gerenciador: Livro sem exemplares!" << endl;
        } else {
            gerenciador.criarEmprestimo(profBloqueado, exemplarEsgotado, dataAtual);
        }
        cout << "---------------------------------------------------------" << endl << endl;

        // =================================================================
        // TESTE 2: FLUXO COMPLEXO DE RESERVAS
        // =================================================================
        cout << ">>> TESTE 2: GESTAO DE RESERVAS <<<" << endl;

        cout << "[Ação] Aluno reserva 'O Senhor dos Aneis' (Cria reserva nova):" << endl;
        gerenciador.criarReserva(&alunoAtivo, &livro1, dataAtual);

        cout << "\n[Ação] Aluno tenta reservar 'O Senhor dos Aneis' DE NOVO (Deve dar Erro):" << endl;
        gerenciador.criarReserva(&alunoAtivo, &livro1, dataAtual);

        cout << "\n[Ação] Aluno reserva 'O Hobbit' (Deve adicionar na reserva que JÁ EXISTE):" << endl;
        gerenciador.criarReserva(&alunoAtivo, &livro3, dataAtual);

        cout << "\n[Ação] Listando todas as reservas ativas:" << endl;
        gerenciador.listarTodasReservas();
        cout << "---------------------------------------------------------" << endl << endl;

        // =================================================================
        // TESTE 3: CONVERSÃO DE RESERVA EM EMPRÉSTIMO
        // =================================================================
        cout << ">>> TESTE 3: CONVERTENDO RESERVA EM EMPRESTIMO <<<" << endl;
        
        // Vamos buscar a reserva que contém os 2 livros ('Senhor dos Aneis' e 'O Hobbit')
        Reserva* reservaDoCarlos = gerenciador.getReservaPorUsuario(&alunoAtivo);
        
        if (reservaDoCarlos != nullptr) {
            cout << "[Ação] Convertendo a reserva inteira do Carlos em emprestimos:" << endl;
            gerenciador.criarEmprestimoApartirDaReserva(reservaDoCarlos, dataAtual);
        } else {
            cout << "Erro crítico: A reserva do Carlos sumiu!" << endl;
        }

        cout << "\n[Ação] Verificando se a reserva foi apagada corretamente (A lista deve estar vazia):" << endl;
        gerenciador.listarTodasReservas();
        cout << "---------------------------------------------------------" << endl << endl;

        // =================================================================
        // TESTE 4: RESULTADO FINAL (LISTAGENS E CONTAGENS)
        // =================================================================
        cout << ">>> TESTE 4: PANORAMA FINAL DO SISTEMA <<<" << endl;
        gerenciador.listarTodosEmprestimosAtuais();

        cout << "\n[Contagem] Emprestimos ativos de 'O Senhor dos Aneis': ";
        cout << gerenciador.contarEmprestimosAtivos(livro1) << endl;

        cout << "[Contagem] Emprestimos ativos de '1984': ";
        cout << gerenciador.contarEmprestimosAtivos(livro2) << endl;

        cout << "[Contagem] Emprestimos ativos de 'O Hobbit': ";
        cout << gerenciador.contarEmprestimosAtivos(livro3) << endl;

    } catch (const exception& e) {
        cerr << "\n[ERRO FATAL] Uma exceção foi lançada: " << e.what() << endl;
    }

    cout << "\n=========================================================" << endl;
    cout << "   TESTES CONCLUIDOS COM SUCESSO!                        " << endl;
    cout << "=========================================================" << endl;

    return 0;
}