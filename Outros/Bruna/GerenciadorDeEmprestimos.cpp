#include "GerenciadorDeEmprestimos.h"
#include "Usuario.h"
#include "StatusEmprestimo.h"
#include <iostream>

using std::cout;
using std::endl;

GerenciadorDeEmprestimos::GerenciadorDeEmprestimos() {}  


void GerenciadorDeEmprestimos::criarEmprestimo(Usuario& emprestimoUsuario, ExemplarLivro* exemplar) { // Passa referencia de Usuario e recebe um ponteiro ('*') do exemplar fisico do livro
    if (emprestimoUsuario.getStatus() != StatusUsuario::HABILITADO) {
        cout << "O usuario: '" << emprestimoUsuario.getNome();
        cout << "' nao esta habilitado para realizar emprestimos no momento." << endl;
        return;
    }
    if (exemplar == nullptr || exemplar->getStatus() != StatusEmprestimo::DISPONIVEL) {         // valida se o exemplar está disponivel. 'nullptr' significa se o ponteiro e invalido/nao achou copia
        cout << "Nao foi possivel realizar o emprestimo para " << emprestimoUsuario.getNome() << "." << endl;
        return;
    }
    exemplar->setStatus(StatusEmprestimo::EMPRESTADO);                                      // Acessa o objeto Exemplar na memoria pelo ponteiro usando '->' e altera para EMPRESTADO

    ItemEmprestimo novoItem;                                                                // Inicia um objeto temporario tipo ItemEmprestimo
    novoItem.setExemplar(exemplar);                                                         //vincula o novoItem ao exemplar que está sendo emprestado

    Emprestimo novoEmprestimo;                                                              // Cria o objeto em si do 'recibo' do emprestimo
    novoEmprestimo.setUsuario(&emprestimoUsuario);                                          // Passa o endereco literal ('&') deste usuario por parametro 
    novoEmprestimo.adicionarItem(novoItem);                                                 // Inclui o item recem-criado no recibo
    novoEmprestimo.setStatus(1);                                                            // Informa um status inteiro de valor 1 (por exemplo: ativo)
    emprestimos.push_back(novoEmprestimo);                                                  //adiciona o novoEmprestimo criado dentro do acervo mestre do gerenciador

    cout << "Emprestimo de '" << exemplar->getLivro()->getTitulo();                         // Utiliza encadeamento para pegar o livro do exemplar e depois o titulo do livro
    cout << "' realizado para: "
         << emprestimoUsuario.getNome() << endl;
}


void GerenciadorDeEmprestimos::listarTodosEmprestimosAtuais() { 
    cout << "***** Lista de Emprestimos *****" << endl;
    for (vector<Emprestimo>::iterator temp = emprestimos.begin(); temp != emprestimos.end(); ++temp) { // Aqui usa-se explicitamente um 'iterator' que funciona como um ponteiro caminhando os blocos do vector
        temp->imprimirEmprestimo();                                                         // Desreferencia o iterador para executar imprimirEmprestimo() deste elemento
    }
}


int GerenciadorDeEmprestimos::contarEmprestimosAtivos(Livro& livro) {  
    int contador = 0;                                                                       // Inicia a variavel que vai guardar o total encontrado
    for (const Emprestimo& temp : emprestimos) {                                            // Percorre todos os recibos de emprestimos do sistema
        for (const ItemEmprestimo& item : temp.getItens()) {                                // Olha cada item (livro fisico) listado dentro desse recibo
            if (item.getExemplar()->getStatus() == StatusEmprestimo::EMPRESTADO) {          // Verifica se o status dessa copia eh realmente "EMPRESTADO"
                if (item.getExemplar()->getLivro()->getCodigo() == livro.getCodigo()) {     // Verifica se o codigo dessa copia bate com o livro pesquisado
                    contador++;                                                             // Se passou nos passos 3 e 4, soma +1 na conta
                }
            }
        }
    }
    return contador;                                                                        // Devolve o numero total de copias desse livro que estao emprestadas
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
