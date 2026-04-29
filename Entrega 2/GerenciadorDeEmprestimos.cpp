#include "GerenciadorDeEmprestimos.h"
#include "Usuario.h"
#include "StatusEmprestimo.h"
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
    if (exemplar == nullptr || exemplar->getStatus() != StatusEmprestimo::DISPONIVEL) {         // valida se o exemplar está disponivel
        cout << "Nao foi possivel realizar o emprestimo para " << emprestimoUsuario.getNome() << "." << endl;
        return;
    }
    exemplar->setStatus(StatusEmprestimo::EMPRESTADO);

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
    for (vector<Emprestimo>::iterator temp = emprestimos.begin(); temp != emprestimos.end(); ++temp) {
        temp->imprimirEmprestimo();
    }
}


int GerenciadorDeEmprestimos::contarEmprestimosAtivos(Livro& livro) {  
    int contador = 0;                                                                       // Inicia a variavel que vai guardar o total encontrado
    for (const Emprestimo& temp : emprestimos) {                                            // Passo 1: Percorre todos os recibos de emprestimos do sistema
        for (const ItemEmprestimo& item : temp.getItens()) {                                // Passo 2: Olha cada item (livro fisico) listado dentro desse recibo
            if (item.getExemplar()->getStatus() == StatusEmprestimo::EMPRESTADO) {          // Passo 3: Verifica se o status dessa copia eh realmente "EMPRESTADO"
                if (item.getExemplar()->getLivro()->getCodigo() == livro.getCodigo()) {     // Passo 4: Verifica se o codigo dessa copia bate com o livro pesquisado
                    contador++;                                                             // Se passou nos passos 3 e 4, soma +1 na conta
                }
            }
        }
    }
    return contador;                                                                        // Devolve o numero total de copias desse livro que estao emprestadas
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
