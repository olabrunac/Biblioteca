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


void GerenciadorDeEmprestimos::criarEmprestimo(Usuario& emprestimoUsuario, ExemplarLivro* exemplar, const Data& dataAtual) {
    if (emprestimoUsuario.getStatus() != StatusUsuario::HABILITADO) {
        cout << "O usuario: '" << emprestimoUsuario.getNome();
        cout << "' nao esta habilitado para realizar emprestimos." << endl;
        return;
    }

    //alocacao dinamica
    Emprestimo* novoEmprestimo = new Emprestimo();
    novoEmprestimo->setUsuario(&emprestimoUsuario);
    novoEmprestimo->setStatus(1);
    novoEmprestimo->setDataEmprestimo(dataAtual);

    int itensAdicionados = 0;

    //arruma a alocacao de memória caso nao tenha livro disponivel
    if (exemplar != nullptr && exemplar->getStatus() == StatusEmprestimo::DISPONIVEL) {
        exemplar->setStatus(StatusEmprestimo::EMPRESTADO);

        ItemEmprestimo* novoItem = new ItemEmprestimo();
        novoItem->setExemplar(exemplar);
        novoEmprestimo->adicionarItem(novoItem);
        
        int diasPermitidos = exemplar->getLivro()->getNroDiasPermitidoEmprestimo();
        Data dataPrevista = dataAtual + diasPermitidos;
        novoEmprestimo->setDataPrevistaDevolucao(dataPrevista);
        novoItem->setDataParaDevolucao(dataPrevista.getDataInteira());

        itensAdicionados++;
    } else {
        cout << "-Nao foi possivel realizar o emprestimo para " << emprestimoUsuario.getNome() << "." << endl;
    }
    if (itensAdicionados > 0) {
        emprestimos.push_back(novoEmprestimo);
        cout << "+'" << exemplar->getLivro()->getTitulo();
        cout << "' emprestado para: " << emprestimoUsuario.getNome() << " com sucesso!" << endl;
    } else {
        delete novoEmprestimo;
        cout << "-Nenhum item adicionado. Emprestimo cancelado." << endl;
    }
}


void GerenciadorDeEmprestimos::criarEmprestimo(Usuario& emprestimoUsuario, initializer_list<ExemplarLivro*> listaExemplares, const Data& dataAtual) {
    
    if (emprestimoUsuario.getStatus() != StatusUsuario::HABILITADO) {
        cout << "O usuario: '" << emprestimoUsuario.getNome();
        cout << "' nao esta habilitado para realizar emprestimos." << endl;
        return;
    }

    Emprestimo* novoEmprestimo = new Emprestimo();
    novoEmprestimo->setUsuario(&emprestimoUsuario);
    novoEmprestimo->setStatus(1);
    novoEmprestimo->setDataEmprestimo(dataAtual);

    int itensAdicionados = 0;
    int maiorPrazoDias = 0;

    for (initializer_list<ExemplarLivro*>::const_iterator temp = listaExemplares.begin(); temp != listaExemplares.end(); ++temp) {
        ExemplarLivro* exemplar = *temp;

        //ve se o exemplar existe e ta disponivel
        if (exemplar != nullptr && exemplar->getStatus() == StatusEmprestimo::DISPONIVEL) {
            exemplar->setStatus(StatusEmprestimo::EMPRESTADO);
            ItemEmprestimo* novoItem = new ItemEmprestimo();
            novoItem->setExemplar(exemplar);
            novoEmprestimo->adicionarItem(novoItem);
            
            int dias = exemplar->getLivro()->getNroDiasPermitidoEmprestimo();
            if (dias > maiorPrazoDias) maiorPrazoDias = dias;
            
            novoItem->setDataParaDevolucao((dataAtual + dias).getDataInteira());
            
            itensAdicionados++;
        }
    }

    if (itensAdicionados > 0) {
        novoEmprestimo->setDataPrevistaDevolucao(dataAtual + maiorPrazoDias);
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

    // 1. Validação do Usuario
    if (reservaUsuario->getStatus() != StatusUsuario::HABILITADO) {
        cout << "-Erro: o usuario '" << reservaUsuario->getNome() << "' esta em debito e nao pode reservar." << endl;
        return;
    }

    // 2. Busca se o usuário já possui um "Carrinho" de reservas aberto
    Reserva* reservaDoUsuario = getReservaPorUsuario(reservaUsuario);

    // 3. Validação do Livro Repetido
    if (reservaDoUsuario != nullptr && reservaDoUsuario->possuiLivro(reservaLivro)) {
        cout << "-Erro: o usuario ja possui uma reserva ativa para o livro '" << reservaLivro->getTitulo() << "'." << endl;
        return; 
    }

    // 4. Teste de Disponibilidade para definir a Data de Retirada
    Data dataDeRetirada = dataRealizacao; // Nasce como hoje
    Data limiteDisponibilidade = dataRealizacao + reservaLivro->getNroDiasPermitidoEmprestimo();
    
    if (estaDisponivelnaData(reservaLivro, dataRealizacao, limiteDisponibilidade)) { 
        cout << "!Aviso: O livro '" << reservaLivro->getTitulo() << "' esta disponivel fisicamente hoje. Considere realizar um emprestimo direto." << endl;
        // Data de retirada continua sendo hoje
    } else {  
        // Se não tem disponível, a pessoa entra na fila. 
        // Adicionamos 7 dias como uma estimativa padrão de espera (já que calcular o dia exato da volta do empréstimo mais próximo exige outro algoritmo).
        dataDeRetirada = dataRealizacao + 7; 
        cout << "!Aviso: Sem exemplares agora. Retirada programada para daqui a 7 dias." << endl;
    } 

    // 5. Criando o Item de Reserva independentemente de ser reserva nova ou velha
    ItemReserva* novoItem = new ItemReserva();
    novoItem->setLivro(reservaLivro);
    novoItem->setDataDeRetirada(dataDeRetirada);

    // 6. Decisão de Roteamento: Colocar na reserva existente OU criar uma nova
    if (reservaDoUsuario != nullptr) {
        // Usuário JÁ TEM reserva, apenas anexa
        novoItem->setNroDoItem(reservaDoUsuario->getItens().size() + 1);      
        reservaDoUsuario->adicionarItem(novoItem);
        cout << "+Sucesso: Livro '" << reservaLivro->getTitulo() << "' adicionado a reserva existente de " << reservaUsuario->getNome() << "." << endl;
    
    } else {
        // Usuário NÃO TEM reserva, cria do zero
        novoItem->setNroDoItem(1); 
        
        Reserva* novaReserva = new Reserva();
        novaReserva->setUsuario(reservaUsuario);
        novaReserva->setDataRealizacao(dataRealizacao);
        novaReserva->setID(reservas.size() + 1); 
        novaReserva->adicionarItem(novoItem);
        
        reservas.push_back(novaReserva);
        cout << "+Sucesso: Reserva ID " << novaReserva->getID() << " criada e '" << reservaLivro->getTitulo() << "' registrado para " << reservaUsuario->getNome() << "." << endl;
    }
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
        cout << "+Sucesso: Reserva convertida em emprestimo" << endl;
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

void GerenciadorDeEmprestimos::listarTodasReservasUsuario(Usuario* usuarioBuscado) {
    if (usuarioBuscado == nullptr) {
        cout << "Erro: Usuario invalido (ponteiro nulo)." << endl;
        return;
    }

    cout << "\n----- Reservas Ativas de: " << usuarioBuscado->getNome() << " -----" << endl;
    
    int totalReservasEncontradas = 0;

    for (vector<Reserva*>::iterator temp = reservas.begin(); temp != reservas.end(); ++temp) {
        // Se a reserva pertencer ao usuário que estamos buscando
        if ((*temp)->getUsuario() == usuarioBuscado) {
            totalReservasEncontradas++;
            
            cout << "\n[ Ocorrencia #" << totalReservasEncontradas << " ]" << endl;
            
            // Aqui usamos a própria classe Reserva para imprimir seus detalhes e seus itens!
            (*temp)->imprimirReserva(); 
            
            cout << "-----------------------------------" << endl;
        }
    }

    // Feedback final
    if (totalReservasEncontradas == 0) {
        cout << "Nenhuma reserva ativa encontrada para este usuario." << endl;
    } else {
        cout << "\nTotal de reservas encontradas: " << totalReservasEncontradas << endl;
    }
}

bool GerenciadorDeEmprestimos::estaDisponivelnaData(Livro* testeLivro, const Data& dataInicial, const Data& dataFinal){

    int ContadorConflito = 0;

    //Verificação das reservas
    for (vector<Reserva*>::iterator temp = reservas.begin(); temp != reservas.end(); ++temp){
        
        if((*temp)->possuiLivro(testeLivro)){  //Se no vetor de reservas já tem reserva desse livro
            ItemReserva* item = ((*temp))->getItemPorLivro(testeLivro);
            //Variaveis de data para comparação
            Data Retirada = item->getDataDeRetirada();
            Data EsperadaDevolucao = Retirada + testeLivro->getNroDiasPermitidoEmprestimo();
        
            //Verificacao das datas, 1 expressão: se dataFinal for antes da retirada de uma reserva já existente, PODE
                                    //2 expressão: se dataInicial for depois da devolução, PODE
            bool PeriodoDiferente = (dataFinal < Retirada) || (dataInicial > EsperadaDevolucao);
                if(!PeriodoDiferente){ //Se o bool for false, indica conflito

                    ContadorConflito++; 

                }
        }

    }
    //Verificação dos Emprestimos    
    for (vector<Emprestimo*>::iterator temp = emprestimos.begin(); temp != emprestimos.end(); ++temp ){

        if((*temp)->possuiLivro(testeLivro)){ //Se ele já foi Emprestado
            if((*temp)->getDataPrevistaDevolucao() > dataInicial){ //Se vai ser devolvido depois da data Inicial

            ContadorConflito++;
            }
            
        }
    }
        if(ContadorConflito >= testeLivro->getQuantidadeDeExemplares()){     
              
            return false;
        }
        
    return true;

}


Reserva* GerenciadorDeEmprestimos::getReservaPorUsuario(Usuario* usuarioBuscado) {
    for (vector<Reserva*>::iterator temp = reservas.begin(); temp != reservas.end(); ++temp) {
        if ((*temp)->getUsuario() == usuarioBuscado) {
            return *temp; // Achou! Devolve o ponteiro da reserva
        }
    }
    return nullptr; // Se o usuário não tiver nenhuma reserva, devolve vazio
}
