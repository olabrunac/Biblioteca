#include "GerenciadorDeEmprestimos.h"
#include "Usuario.h"
#include "StatusEmprestimo.h"
#include <iostream>

using std::cout;
using std::endl;

GerenciadorDeEmprestimos::GerenciadorDeEmprestimos() {} 

~GerenciadorDeEmprestimos::GerenciadorDeEmprestimos() {
    for (vector<Emprestimo*>::iterator temp = emprestimos.begin(); temp != emprestimos.begin(); temp != emprestimos.end(); ++temp) {
        delete *temp;
    }
    emprestimos.clear();

    for (vector<Reserva*> iterator temp = reservas.begin(); temp != reservas.end(); ++temp) {
        delete *temp;
    }
    reservas.clear();  //para tambem limpar o vetor de reserva por conta do polimorfismo
}


void GerenciadorDeEmprestimos::criarEmprestimo(Usuario& emprestimoUsuario, ExemplarLivro* exemplar) {
    if (emprestimoUsuario.getStatus() != StatusUsuario::HABILITADO) {
        cout << "O usuario: '" << emprestimoUsuario.getNome();
        cout << "' nao esta habilitado para realizar emprestimos no momento." << endl;
        return;
    }
    if (exemplar == nullptr || exemplar->getStatus() != StatusEmprestimo::DISPONIVEL) {
        cout << "Nao foi possivel realizar o emprestimo para " << emprestimoUsuario.getNome() << "." << endl;
        return;
    }
    exemplar->setStatus(StatusEmprestimo::EMPRESTADO);

    ItemEmprestimo novoItem;
    novoItem.setExemplar(exemplar);

    //criação dinamica
    Emprestimo* novoEmprestimo = new Emprestimo();
    novoEmprestimo->setUsuario(&emprestimoUsuario);
    novoEmprestimo->adicionarItem(novoItem);
    novoEmprestimo->setStatus(1);
    emprestimos.push_back(novoEmprestimo);

    cout << "Emprestimo de '" << exemplar->getLivro()->getTitulo();
    cout << "' realizado com sucesso!" << endl;
}


void GerenciadorDeEmprestimos::listarTodosEmprestimosAtuais() { 
    cout << "***** Lista de Emprestimos *****" << endl;
    for (vector<Emprestimo*>::iterator temp = emprestimos.begin(); temp != emprestimos.end(); ++temp) {
        (*temp)->imprimirEmprestimo();
    }
}


int GerenciadorDeEmprestimos::contarEmprestimosAtivos(Livro& livro) {  
    int contador = 0;
    for (const Emprestimo& temp : emprestimos) {
        for (const ItemEmprestimo& item : temp.getItens()) {
            if (item.getExemplar()->getStatus() == StatusEmprestimo::EMPRESTADO) {
                if (item.getExemplar()->getLivro()->getCodigo() == livro.getCodigo()) {
                    contador++;
                }
            }
        }
    }
    return contador; 
}


void GerenciadorDeEmprestimos::criarReserva(Usuario* reservaUsuario, Livro* reservaLivro,  int dataAtual) {
    if (reservaUsuario->getStatus() != StatusUsuario::HABILITADO) {
        cout << "Erro: o usuário não pode fazer reservas" << endl;
        return;
    }

    //cria o item da reserva
    ItemReserva* novoItem = new ItemReserva();
    novoItem->setLivro(reservaLivro);
    novoItem->setDataDeRetirada(dataAtual);
    novoItem->setNroDoItem(1);

    //cria a reserva
    Reserva* novaReserva = new Reserva();
    novaReserva->setUsuario(reservaUsuario);
    novaReserva->setDataRealizacao(dataAtual);
    novaReserva->setID(reservas.size() +1); //gera um id simples
    novaReserva->adicionarItem(novoItem);
    
    reservas.push_back(novaReserva);
    cout << "Sucesso: Reserva do livro '" << reservaLivro->getTitulo() << "' registrada para " << reservaUsuario->getNome() << endl;
}


--------------------------------------------------------------------------------------------------------------------------


void GerenciadorDeEmprestimos::criarEmprestimoApartirDaReserva(Reserva* reservaExistente, Emprestimo* novoEmprestimo, ExemplarLivro* exemplar) {
    if (exemplar != nullptr && exemplar->getStatus() == StatusEmprestimo::DISPONIVEL) {
        exemplar-setStatus(StatusEmprestimo::EMPRESTADO);   //atualiza o status do exemplar e coloca no emprestimo
        ItemEmprestimo novoItem;
        novoItem.setExemplar(exemplar);
        novoEmprestimo->adicionarItem(novoItem);

        emprestimos.push_back(novoEmprestimo); //coloca o emprestimo no vetor de ponteiros

        vector<Reserva*>::iterator temp;        //remove a reserva do vetor de reservas
        for(temp = reservas.begin(); temp != reservas.end(); ++temp) {
            if ((*temp)->getID() == reservaExistente->getID()) {
                delete *temp;       //limpa o objeto reserva da memória
                reservas.erase(temp);       //remove o ponteiro da lista
                break;
            }
        }
        cout << "Sucesso: Reserva convertida em emprestimo" << endl;
    } else {
        cout << "Erro: o livro nao possiu exemplares disponiveis" << endl;
    }
}

void GerenciadorDeEmprestimos::listarTodasReservas() {
    cout << "----- Lista de Reservas Ativas -----" << endl;
    for (reservas.empty()) {
        cout << "Nenhuma reseva no sistema" << endl;
        return;
    }

    for (vector<Reserva*>::iterator temp = reservas.begin(); temp != reservas.end(); ++temp) {
        (*temp)->imprimirReserva();
        cout << endl;
    }
}

