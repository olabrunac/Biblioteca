#include "GerenciadorDeEmprestimos.h"
#include "Usuario.h"
#include "StatusEmprestimo.h"
#include <iostream>

using std::cout;
using std::endl;

GerenciadorDeEmprestimos::GerenciadorDeEmprestimos() {} 

GerenciadorDeEmprestimos::~GerenciadorDeEmprestimos() {
    for (vector<Emprestimo*>::iterator temp = emprestimos.begin(); temp != emprestimos.end(); ++temp) {
        delete *temp;
    }
    emprestimos.clear();

    for (vector<Reserva*>::iterator temp = reservas.begin(); temp != reservas.end(); ++temp) {
        delete *temp;
    }
    reservas.clear();  //para tambem limpar o vetor de reserva por conta do polimorfismo
}


void GerenciadorDeEmprestimos::criarEmprestimo(Usuario& emprestimoUsuario, ExemplarLivro* exemplar) {
    if (emprestimoUsuario.getStatus() != StatusUsuario::HABILITADO) {
        cout << "O usuario: '" << emprestimoUsuario.getNome()
             << "' nao esta habilitado para realizar emprestimos." << endl;
        return;
    }

    //alocacao dinamica
    Emprestimo* novoEmprestimo = new Emprestimo();
    novoEmprestimo->setUsuario(&emprestimoUsuario);
    novoEmprestimo->setStatus(1);

    int itensAdicionados = 0;

    //arruma a alocacao de memória caso nao tenha livro disponivel
    if (exemplar != nullptr && exemplar->getStatus() == StatusEmprestimo::DISPONIVEL) {
        exemplar->setStatus(StatusEmprestimo::EMPRESTADO);

        ItemEmprestimo* novoItem = new ItemEmprestimo();
        novoItem->setExemplar(exemplar);
        novoEmprestimo->adicionarItem(novoItem);

        itensAdicionados++;
    } else {
        cout << "-Nao foi possivel realizar o emprestimo para " << emprestimoUsuario.getNome() << "." << endl;
    }
    if (itensAdicionados > 0) {
        emprestimos.push_back(novoEmprestimo);
        cout << "+'" << exemplar->getLivro()->getTitulo() 
             << "' emprestado para: " << emprestimoUsuario.getNome() << " com sucesso!" << endl;
    } else {
        delete novoEmprestimo;
        cout << "-Nenhum item adicionado. Emprestimo cancelado." << endl;
    }
}

void GerenciadorDeEmprestimos::criarEmprestimo(Usuario& emprestimoUsuario, initializer_list<ExemplarLivro*> listaExemplares) {
    
    if (emprestimoUsuario.getStatus() != StatusUsuario::HABILITADO) {
        cout << "O usuario: '" << emprestimoUsuario.getNome();
        cout << "' nao esta habilitado para realizar emprestimos." << endl;
        return;
    }

    Emprestimo* novoEmprestimo = new Emprestimo();
    novoEmprestimo->setUsuario(&emprestimoUsuario);
    novoEmprestimo->setStatus(1);

    int itensAdicionados = 0;

    for (initializer_list<ExemplarLivro*>::const_iterator temp = listaExemplares.begin(); temp != listaExemplares.end(); ++temp) {
        ExemplarLivro* exemplar = *temp;

        //ve se o exemplar existe e ta disponivel
        if (exemplar != nullptr && exemplar->getStatus() == StatusEmprestimo::DISPONIVEL) {
            exemplar->setStatus(StatusEmprestimo::EMPRESTADO);
            
            ItemEmprestimo* novoItem = new ItemEmprestimo();
            novoItem->setExemplar(exemplar);
            novoEmprestimo->adicionarItem(novoItem);
            
            itensAdicionados++;
        }
    }

    if (itensAdicionados > 0) {
        emprestimos.push_back(novoEmprestimo);
        cout << "+" << itensAdicionados << " itens emprestados com sucesso para " << emprestimoUsuario.getNome() << "!" << endl;
    } else {
        //se a lista so tinha livros indisponiveis, cancela e limpa a memória
        delete novoEmprestimo;
        cout << "-Nenhum item adicionado. Emprestimo cancelado." << endl;
    }
}


void GerenciadorDeEmprestimos::listarTodosEmprestimosAtuais() { 
    for (vector<Emprestimo*>::iterator temp = emprestimos.begin(); temp != emprestimos.end(); ++temp) {
        (*temp)->imprimirEmprestimo();
    }
}


int GerenciadorDeEmprestimos::contarEmprestimosAtivos(Livro& livro) {  
    int contador = 0;
    for (vector<Emprestimo*>::const_iterator temp = emprestimos.begin(); temp != emprestimos.end(); ++temp) {
        for (vector<ItemEmprestimo*>::const_iterator item = (*temp)->getItens().begin(); item != (*temp)->getItens().end(); ++item) {
            if ((*item)->getExemplar()->getStatus() == StatusEmprestimo::EMPRESTADO) {
                if ((*item)->getExemplar()->getLivro()->getCodigo() == livro.getCodigo()) {
                    contador++;
                }
            }
        }
    }
    return contador; 
}


void GerenciadorDeEmprestimos::criarReserva(Usuario* reservaUsuario, Livro* reservaLivro, Data& dataRealizacao) {

    //Validação do Usuario
    if (reservaUsuario->getStatus() != StatusUsuario::HABILITADO) {
        cout << "Erro: o usuario '" << reservaUsuario->getNome() << "' nao pode fazer reservas." << endl;
        return; //1 return, Usuario não pode reservar
    }
    //Validação do Livro
    for(vector<Reserva*>::iterator itReserva = reservas.begin(); itReserva != reservas.end(); ++itReserva) { 
        if((*itReserva)->getUsuario() == reservaUsuario) { 
            
            //O usuário tem uma reserva. Delegamos a verificação à própria classe Reserva (Encapsulamento rigoroso)
            if ((*itReserva)->possuiLivro(reservaLivro)) {
                cout << "Erro: o usuario ja possui uma reserva ativa para o livro '" << reservaLivro->getTitulo() << "'." << endl;
                return; //2 return, Usuario já tem esse livro reservado
            }
           
            //Se chegou aqui, o livro não é repetido.Adicioná-lo à reserva existente
            ItemReserva* novoItem = new ItemReserva();
            novoItem->setLivro(reservaLivro);

            if (reservaLivro->estaDisponivel()) { //Se estiver disponivel já pode retirar
                
                cout << "Aviso: O livro '" << reservaLivro->getTitulo() << "' esta disponivel no momento. Considere realizar um emprestimo ao inves de uma reserva." << endl;
                novoItem->setDataDeRetirada(dataRealizacao); 
            }
            else {  
            
            novoItem->setDataDeRetirada(dataRealizacao + 7 ); //Se não estiver, data estimada
            
            } 

            //O numeroItem com base na quantidade que já existem
            novoItem->setNroDoItem((*itReserva)->getItens().size() + 1);      
            
            (*itReserva)->adicionarItem(novoItem);
            
            cout << "Sucesso: Livro '" << reservaLivro->getTitulo() << "' adicionado a reserva existente de " << reservaUsuario->getNome() << "." << endl;
            return; //3 return, livro adicionado a reserva existente
        }
    }
    
    //Quarto caso, o usuario não tenha nenhuma reserva, criamos uma nova do zero e adicionamos o livro nela.
    ItemReserva* novoItem = new ItemReserva();
    novoItem->setLivro(reservaLivro);
    novoItem->setDataDeRetirada(dataRealizacao + 7); 
    novoItem->setNroDoItem(1); // Como é uma reserva nova, este será obrigatoriamente o Item 1
    
    // Cria a reserva-mãe
    Reserva* novaReserva = new Reserva();
    novaReserva->setUsuario(reservaUsuario);
    novaReserva->setDataRealizacao(dataRealizacao);
    novaReserva->setID(reservas.size() + 1); // Gera um ID simples baseado no tamanho atual
    
    // Coloca o item na reserva e a reserva no sistema
    novaReserva->adicionarItem(novoItem);
    reservas.push_back(novaReserva);
    
    cout << "Sucesso: Nova reserva criada e livro '" << reservaLivro->getTitulo() << "' registrado para " << reservaUsuario->getNome() << "." << endl;

}



void GerenciadorDeEmprestimos::criarEmprestimoApartirDaReserva(Reserva* reservaExistente) {
    
     if (reservaExistente->getUsuario()->getStatus() != StatusUsuario::HABILITADO) { //Tinha esquecido da verificação do usuario
        cout << "Erro: o usuário associado a esta reserva não pode fazer empréstimos." << endl;
        return;
    }   

    // Aplicação estrita de iteradores em substituição de 'int i'
    for(vector<ItemReserva*>::const_iterator itItem = reservaExistente->getItens().begin(); itItem != reservaExistente->getItens().end(); ++itItem) { 
        if((*itItem)->getLivro()->getExemplarDisponivel() == nullptr) {
            cout << "Erro: o livro '" << (*itItem)->getLivro()->getTitulo() << "' nao possui exemplares disponiveis no momento" << endl;
            return;
        }
    }

    for(vector<ItemReserva*>::const_iterator itItem = reservaExistente->getItens().begin(); itItem != reservaExistente->getItens().end(); ++itItem){

        ExemplarLivro* exemplar = (*itItem)->getLivro()->getExemplarDisponivel();
        exemplar->setStatus(StatusEmprestimo::EMPRESTADO); //atualiza o status do exemplar e coloca no emprestimo
        
        ItemEmprestimo* novoItem = new ItemEmprestimo();
        novoItem->setExemplar(exemplar);

        Emprestimo* novoEmprestimo = new Emprestimo();
        novoEmprestimo->setUsuario(reservaExistente->getUsuario());
        novoEmprestimo->setStatus(1);
        novoEmprestimo->adicionarItem(novoItem);
        novoEmprestimo->setDataDeRetirada((*itItem)->getDataDeRetirada());
        emprestimos.push_back(novoEmprestimo);//coloca o emprestimo no vetor de ponteiros

    }
        vector<Reserva*>::iterator temp;        //remove a reserva do vetor de reservas
        for(temp = reservas.begin(); temp != reservas.end(); ++temp) {
            if ((*temp)->getID() == reservaExistente->getID()) {
                delete *temp;       //limpa o objeto reserva da memória
                reservas.erase(temp);       //remove o ponteiro da lista
                break;
            }
        }
        cout << "Sucesso: Reserva convertida em emprestimo" << endl;
}

 void GerenciadorDeEmprestimos::listarTodasReservas() {
    cout << "----- Lista de Reservas Ativas -----" << endl;
    
    if (reservas.empty()) {
        cout << "Nenhuma reserva no sistema." << endl;
        return; //Sai da função, nada para listar
    }
    //loop para imprimir cada reserva
    for (vector<Reserva*>::iterator temp = reservas.begin(); temp != reservas.end(); ++temp) {
        (*temp)->imprimirReserva();
        cout << endl;
    }
}

Reserva* GerenciadorDeEmprestimos::getReservaPorUsuario(Usuario* usuarioBuscado) {
    for (vector<Reserva*>::iterator it = reservas.begin(); it != reservas.end(); ++it) {
        if ((*it)->getUsuario() == usuarioBuscado) {
            return *it; // Achou! Devolve o ponteiro da reserva
        }
    }
    return nullptr; // Se o usuário não tiver nenhuma reserva, devolve vazio
}