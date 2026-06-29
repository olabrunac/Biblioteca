#include "GerenciadorDeEmprestimos.h"
#include "Usuario.h"
#include "StatusEmprestimo.h"
#include <iostream>

#include "Erros.h"

using std::cout;
using std::endl;


GerenciadorDeEmprestimos::GerenciadorDeEmprestimos() {} 


GerenciadorDeEmprestimos::~GerenciadorDeEmprestimos() {
    for (auto temp : emprestimos) {
        delete temp;
    }
    emprestimos.clear();

    for (auto temp : reservas) {
        delete temp;
    }
    reservas.clear();
}


void GerenciadorDeEmprestimos::criarEmprestimo(Usuario& emprestimoUsuario, ExemplarLivro* exemplar, const Data& dataAtual) { 
    if (emprestimoUsuario.getStatus() != StatusUsuario::HABILITADO) {  
        throw ErroUsuarioNaoHabilitado();
    }

    if (exemplar) {
        Livro* livroRequisitado = exemplar->getLivro();
        for (const auto& emprestimoExistente : emprestimos) {
            if (emprestimoExistente->getUsuario() == &emprestimoUsuario && emprestimoExistente->getStatus() == 1) {
                if (emprestimoExistente->possuiLivro(livroRequisitado)) {
                    throw ErroUsuarioJaEmprestouLivro();
                }
            }
        }
    }

    Emprestimo* emprestimoDoUsuario = getEmprestimoPorUsuario(&emprestimoUsuario);

    //cria o item de emprestimo
    ItemEmprestimo* novoItem = new ItemEmprestimo();
    novoItem->setExemplar(exemplar);
    exemplar->setStatus(StatusEmprestimo::EMPRESTADO);

    int diasPermitidos = exemplar->getLivro()->getNroDiasPermitidoEmprestimo();
    Data dataPrevistaItem = dataAtual + diasPermitidos;
    novoItem->setDataParaDevolucao(dataPrevistaItem);
    novoItem->setDataQueFoiDevolvido(0);

    if (emprestimoDoUsuario != nullptr) {
        //se o usuario ja tem emprestimo ativo, adiciona o novo item
        emprestimoDoUsuario->adicionarItem(novoItem);

        if (dataPrevistaItem > emprestimoDoUsuario->getDataPrevistaDevolucao()) {
            emprestimoDoUsuario->setDataPrevistaDevolucao(dataPrevistaItem);
        }
        cout << "+Livro '" << exemplar->getLivro()->getTitulo() << "' adicionado ao emprestimo de " << emprestimoUsuario.getNome() << " com sucesso!" << endl;

    } else {
        //senao cria o novo emprestimo do zero
        Emprestimo* novoEmprestimo = new Emprestimo();
        novoEmprestimo->setUsuario(&emprestimoUsuario);
        novoEmprestimo->setStatus(1);
        novoEmprestimo->setDataDeRetirada(dataAtual);
        novoEmprestimo->setDataDevolucao(0);
        novoEmprestimo->setDataPrevistaDevolucao(dataPrevistaItem);
        novoEmprestimo->adicionarItem(novoItem);

        emprestimos.push_back(novoEmprestimo);
        cout << "+Emprestimo criado para " << emprestimoUsuario.getNome() << " com o livro '" << exemplar->getLivro()->getTitulo() << "'." << endl;
        cout << "  Devolucao prevista para: ";
        dataPrevistaItem.imprimirData();
        cout << endl;
    }
}


void GerenciadorDeEmprestimos::criarEmprestimo(Usuario& emprestimoUsuario, initializer_list<ExemplarLivro*> listaExemplares, const Data& dataAtual) {
    if (emprestimoUsuario.getStatus() != StatusUsuario::HABILITADO) {
        throw ErroUsuarioNaoHabilitado();
    }

    Emprestimo* novoEmprestimo = new Emprestimo();
    novoEmprestimo->setUsuario(&emprestimoUsuario);
    novoEmprestimo->setStatus(1);
    novoEmprestimo->setDataDeRetirada(dataAtual);

    int itensAdicionados = 0;
    int maiorPrazoDias = 0;

    for (auto temp : listaExemplares) {
        ExemplarLivro* exemplar = temp;

        bool disponivelNoPeriodo = false;
        if (exemplar != nullptr) {
            disponivelNoPeriodo = estaDisponivelnaData(exemplar->getLivro(), dataAtual, dataAtual + exemplar->getLivro()->getNroDiasPermitidoEmprestimo());
        }
        if (exemplar != nullptr && exemplar->getStatus() == StatusEmprestimo::DISPONIVEL && disponivelNoPeriodo) {
            exemplar->setStatus(StatusEmprestimo::EMPRESTADO);
            ItemEmprestimo* novoItem = new ItemEmprestimo();
            novoItem->setExemplar(exemplar);
            
            int dias = exemplar->getLivro()->getNroDiasPermitidoEmprestimo();
            if (dias > maiorPrazoDias) maiorPrazoDias = dias;
            
            novoItem->setDataParaDevolucao(dataAtual + dias);
            novoItem->setDataQueFoiDevolvido(0);

            novoEmprestimo->adicionarItem(novoItem);
            itensAdicionados++;
        } else if (exemplar != nullptr && !disponivelNoPeriodo) {
            delete novoEmprestimo;
            throw ErroLivroIndisponivel(); 
        }
    }

    if (itensAdicionados > 0) {
        novoEmprestimo->setDataPrevistaDevolucao(dataAtual + maiorPrazoDias);
        novoEmprestimo->setDataDevolucao(0);
        emprestimos.push_back(novoEmprestimo);
        cout << "+" << itensAdicionados << " itens emprestados com sucesso para " << emprestimoUsuario.getNome() << "!" << endl;
    } else {
        delete novoEmprestimo;
            throw ErroEmprestimoVazio();
    }
}


void GerenciadorDeEmprestimos::criarEmprestimoApartirDaReserva(Reserva* reservaExistente, const Data& dataAtual) { 
    if (reservaExistente->getUsuario()->getStatus() != StatusUsuario::HABILITADO) {
       throw ErroUsuarioNaoHabilitado();
    }   

    for(auto temp : reservaExistente->getItens()) { 
        if(temp->getLivro()->getExemplarDisponivel() == nullptr) {
            throw ErroLivroIndisponivel();
            return;
        }
    }
    
    // inicia um objeto de emprestimo para todos os itens
    Emprestimo* novoEmprestimo = new Emprestimo();
    novoEmprestimo->setUsuario(reservaExistente->getUsuario());
    novoEmprestimo->setStatus(1);
    novoEmprestimo->setDataDeRetirada(dataAtual);
    novoEmprestimo->setDataDevolucao(0);
    int maiorPrazoDias = 0;

    //pega todos os itens da reserva e coloca no emprestimo
    for(auto tempItem : reservaExistente->getItens()){
        ExemplarLivro* exemplar = tempItem->getLivro()->getExemplarDisponivel();
        exemplar->setStatus(StatusEmprestimo::EMPRESTADO);
        
        ItemEmprestimo* novoItemEmprestimo = new ItemEmprestimo();
        novoItemEmprestimo->setExemplar(exemplar);

        // calcula a data de devolucao dos itens e atualiza o prazo do emprestimo
        int dias = exemplar->getLivro()->getNroDiasPermitidoEmprestimo();
        if (dias > maiorPrazoDias) maiorPrazoDias = dias;
        novoItemEmprestimo->setDataParaDevolucao(dataAtual + dias);
        novoItemEmprestimo->setDataQueFoiDevolvido(0);

        novoEmprestimo->adicionarItem(novoItemEmprestimo);
    }
    novoEmprestimo->setDataPrevistaDevolucao(dataAtual + maiorPrazoDias);
    emprestimos.push_back(novoEmprestimo);

    // remove a reserva do sistema
        for(auto temp = reservas.begin(); temp != reservas.end(); ++temp) {
            if ((*temp)->getID() == reservaExistente->getID()) {
                delete *temp;
                reservas.erase(temp);
                break;
            }
        }
        cout << "+Sucesso: Reserva convertida em emprestimo" << endl;
}


void GerenciadorDeEmprestimos::criarReserva(Usuario* reservaUsuario, Livro* reservaLivro, Data& dataRealizacao) { 

    if (reservaUsuario->getStatus() != StatusUsuario::HABILITADO) {
        throw ErroUsuarioNaoHabilitado();
    }

    // ve se o usuario já tem reservas
    Reserva* reservaDoUsuario = getReservaPorUsuario(reservaUsuario);

    // ve se tem livro repetido
    if (reservaDoUsuario != nullptr && reservaDoUsuario->possuiLivro(reservaLivro)) {
        throw ErroUsuarioJaReservouLivro();
    }

    Data dataDeRetirada = dataRealizacao; // a data de retirada do acervo
    
    //ve se tem livro disponivel, se sim nao precisa criar reserva
    if (reservaLivro->estaDisponivel()) { 
        cout << "!Aviso: O livro '" << reservaLivro->getTitulo() << "' esta disponivel fisicamente hoje. Considere realizar um emprestimo direto." << endl;
        return;
    } else {  
        // se nao tem, a pessoa entra na fila
        dataDeRetirada = dataRealizacao + 7; 
        cout << "!Aviso: Sem exemplares agora. Retirada programada para daqui a 7 dias." << endl;
        
        // cria a reserva
        ItemReserva* novoItem = new ItemReserva();
        novoItem->setLivro(reservaLivro);
        novoItem->setDataDeRetirada(dataDeRetirada);

        // se já tem reserva adiciona anexa a nova, senao cria do zero
        if (reservaDoUsuario != nullptr) {
            novoItem->setNroDoItem(reservaDoUsuario->getItens().size() + 1);      
            reservaDoUsuario->adicionarItem(novoItem);
            cout << "+Sucesso: Livro '" << reservaLivro->getTitulo() << "' adicionado a reserva existente de " << reservaUsuario->getNome() << "." << endl;
        
        } else {
            novoItem->setNroDoItem(1); 
            
            Reserva* novaReserva = new Reserva();
            novaReserva->setUsuario(reservaUsuario);
            novaReserva->setDataRealizacao(dataRealizacao);
            novaReserva->setID(reservas.size() + 1); 
            novaReserva->adicionarItem(novoItem);
            
            reservas.push_back(novaReserva);
            cout << "+Sucesso: Reserva ID " << novaReserva->getID() << " criada e '" << reservaLivro->getTitulo() << "' registrado para " << reservaUsuario->getNome() << "." << endl;
        }
        cout << "+Operacao de reserva concluida." << endl;
    }

}


//-------------------- listagem --------------------


void GerenciadorDeEmprestimos::listarTodosEmprestimosAtuais() {
    for (auto temp : emprestimos) {
        temp->imprimirEmprestimo();
    }
}


void GerenciadorDeEmprestimos::listarReservasDoLivro(Livro& listaLivro) {
    cout << "----- Reservas para o livro: '" << listaLivro.getTitulo() << "' -----" << endl;
    bool encontrou = false; 

    for (auto temp : reservas) {
        if (temp->possuiLivro(&listaLivro)) {
            for (auto tempItem : temp->getItens()) {
                if (tempItem->getLivro() == &listaLivro) {
                    encontrou = true;
                    cout << "- Reservado por: " << temp->getUsuario()->getNome()
                         << " (Cod: " << temp->getUsuario()->getCodigo() << ") | Retirada prevista para: ";
                    tempItem->getDataDeRetirada().imprimirData();
                    cout << endl;
                }
            }
        }
    }

    if (!encontrou) {
        ErroExemplarGuardado();
    } 
}


void GerenciadorDeEmprestimos::listarTodasReservas() {
    cout << endl << "----- Lista de Reservas Ativas -----" << endl;
    
    if (reservas.empty()) {
        throw ErroSistemaVazio();
    }

    for (auto temp : reservas) {
        temp->imprimirReserva();
        cout << endl;
    }
}


void GerenciadorDeEmprestimos::listarTodasReservasUsuario(Usuario* usuarioBuscado) const { 
    if (usuarioBuscado == nullptr) {
      throw ErroUsuarioNaoExiste();
    }

    cout << "\n----- Reservas Ativas de: " << usuarioBuscado->getNome() << " -----" << endl;
    int totalReservasEncontradas = 0;

    for (const auto& temp : reservas) {
        if (temp->getUsuario() == usuarioBuscado) {
            totalReservasEncontradas++;          
            cout << "\n[ Ocorrencia #" << totalReservasEncontradas << " ]" << endl;
            temp->imprimirReserva();      
            cout << "-----------------------------------" << endl;
        }
    }

    if (totalReservasEncontradas == 0) {
        throw ErroNenhumaReserva();
    } else {
        cout << "\nTotal de reservas encontradas: " << totalReservasEncontradas << endl;
    }
}


void GerenciadorDeEmprestimos::listarEmprestimosDoUsuario(Usuario* usuario) { 
    bool encontrou = false;
    for (const auto& temp : emprestimos) {
        if (temp->getUsuario() == usuario) {
        if (temp->getUsuario() == usuario && temp->getStatus() == 1) { // só emprestimos ativos
            temp->imprimirEmprestimo();
            encontrou = true;
        }
    }
    if (!encontrou) {
       throw ErroNenhumEmprestimo();
    } 
}}



void GerenciadorDeEmprestimos::listarEmprestimosDoLivro(Livro& livro) { 
    cout << "\n----- Emprestimos para o livro: '" << livro.getTitulo() << "' -----" << endl;
    bool encontrou = false;
    for (const auto& temp : emprestimos) {
        for (const auto& tempItem : temp->getItens()) {
            if (tempItem->getExemplar()->getLivro()->getCodigo() == livro.getCodigo()) {
                cout << "- Emprestado para: " << temp->getUsuario()->getNome()
                     << " (Cod: " << temp->getUsuario()->getCodigo() << ") | Exemplar ID: " << tempItem->getExemplar()->getNroExemplar();
                cout << " | Devolucao: ";
                tempItem->getDataParaDevolucao().imprimirData();
                cout << endl;
                encontrou = true;
            }
        }
    }
    if (!encontrou) {
       throw ErroExemplarGuardado();
    } 
}


//-------------------- contas --------------------


int GerenciadorDeEmprestimos::contarEmprestimosAtivos(Livro& livro) const { 
    int contador = 0;
    for (auto tempEmprestimo : emprestimos) {
        for (auto temp : tempEmprestimo->getItens()) {
            if (temp->getExemplar()->getStatus() == StatusEmprestimo::EMPRESTADO) {
                if (temp->getExemplar()->getLivro()->getCodigo() == livro.getCodigo()) {
                    contador++;
                }
            }
        }
    }
    return contador; 
}


int GerenciadorDeEmprestimos::contarReservasAtivas(Livro& livro) const { 
    int contador = 0;
    for (const auto& temp : reservas) {
        if (temp->possuiLivro(&livro)) {
            contador++;
        }
    }
    return contador;
}


//-------------------- ações --------------------


bool GerenciadorDeEmprestimos::realizarDevolucao(Usuario* usuario, int codigoLivro, const Data& dataDevolucao) { 
    for (auto temp : emprestimos) {
        // procura o emprestimo do usuario e depois o livro
        if (temp->getUsuario() == usuario && temp->getStatus() == 1) {
            for (auto tempItem : temp->getItens()) {
                if (tempItem->getExemplar()->getLivro()->getCodigo() == codigoLivro && tempItem->getExemplar()->getStatus() == StatusEmprestimo::EMPRESTADO) {
                    
                    // faz a devolução
                    tempItem->getExemplar()->setStatus(StatusEmprestimo::DISPONIVEL);
                    tempItem->setDataQueFoiDevolvido(dataDevolucao.getDataInteira());
                    
                    cout << "Devolucao do livro '" << tempItem->getExemplar()->getLivro()->getTitulo() << "' realizada com sucesso." << endl;
                    
                    // verifica se devolveu
                    bool todosDevolvidos = true;
                    for (auto tempCheck : temp->getItens()) {
                        if (tempCheck->getExemplar()->getStatus() == StatusEmprestimo::EMPRESTADO) {
                            todosDevolvidos = false;
                            break;
                        }
                    }
                    if (todosDevolvidos) {
                        temp->setStatus(0); // finaliza o emprestimo
                        cout << "Todos os itens deste emprestimo foram devolvidos." << endl;
                    }
                    return true;
                }
            }
        }
    }
    throw ErroNenhumEmprestimo();
    return false; 
}


bool GerenciadorDeEmprestimos::cancelarReservaItem(Usuario* usuario, int codigoLivro) { 
    Reserva* reserva = getReservaPorUsuario(usuario);
    
    if (!reserva) {
        throw ErroNenhumaReserva();
        return false;
    }

    if (reserva->removerItemPorLivro(codigoLivro)) {
        cout << "Item da reserva cancelado com sucesso." << endl;
        
        // remove a reserva vazia
        if (reserva->getItens().empty()) {
            cout << "A reserva ficou vazia e foi removida do sistema." << endl;
            for (auto temp = reservas.begin(); temp != reservas.end(); ++temp) {
                if (*temp == reserva) {
                    delete *temp;
                    reservas.erase(temp);
                    break;
                }
            }
        }
        
        return true;
    }
    
    throw ErroLivroNaoExisteAcervo();
    return false; 
}


bool GerenciadorDeEmprestimos::usuarioTemPendencias(Usuario* usuario) const { 
    for (auto& temp : emprestimos) {
        if (temp->getUsuario() == usuario && temp->getStatus() == 1) {
            return true;
        }
    }
    // checa por reservas
    if (getReservaPorUsuario(usuario) != nullptr) {
        return true;
    }
    return false;
}


void GerenciadorDeEmprestimos::atualizaPendenciasEmprestimos(Data& dataFutura){ 

    cout << "---------- VERIFICANDO EMPRESTIMOS ATRASADOS" << endl;

    for(auto& temp: emprestimos)

        if(temp->getStatus() == 1) //se o emprestimo está ativo
            //tendo o emprestimo ativo, agora verificamos se a dataFutura(quando utilizamos a função secreta novaData)
            //verifica se era para o emprestimo ser devolvido antes dessa data que foi passada
            if (Data(temp->getDataPrevistaDevolucao()) < dataFutura ){
                //usei o construtor de data, pois getDataPrevistaDevolucao é int

                temp->getUsuario()->setStatus(StatusUsuario::EM_DEBITO);
                //pega o usuario do emprestimo que atrasou e muda o status dele
                cout << "Emprestimo de:" << temp->getUsuario()->getNome() << " esta atrasado" << endl;
                throw ErroUsuarioNaoHabilitado();
                


                //testar essa logica basica, depois adicionar qtd de dias atrasado

              
            }

}


bool GerenciadorDeEmprestimos::estaDisponivelnaData(Livro* testeLivro, const Data& dataInicial, const Data& dataFinal){ 
    int ContadorConflito = 0;

    for (const auto& temp : reservas){
        
        if(temp->possuiLivro(testeLivro)){  //Se no vetor de reservas já tem reserva desse livro
            ItemReserva* item = temp->getItemPorLivro(testeLivro);
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
    for (const auto& temp : emprestimos ){

        if(temp->possuiLivro(testeLivro) && temp->getStatus() == 1){ //Se ele já foi Emprestado
            if(temp->getDataPrevistaDevolucao() > dataInicial){ //Se vai ser devolvido depois da data Inicial

            ContadorConflito++;
            }
            
        }
    }
        if(ContadorConflito >= testeLivro->getQuantidadeDeExemplares()){     
              
            return false;
        }
        
    return true;

}


Reserva* GerenciadorDeEmprestimos::getReservaPorUsuario(Usuario* usuarioBuscado) const { 
    for (auto temp : reservas) {
        if (temp->getUsuario() == usuarioBuscado) {
            return temp;
        }
    }
    return nullptr;
}


Emprestimo* GerenciadorDeEmprestimos::getEmprestimoPorUsuario(Usuario* usuarioBuscado) const { 
    for (auto temp : emprestimos) {
        if (temp->getUsuario() == usuarioBuscado && temp->getStatus() == 1) {
            return temp;
        }
    }
    return nullptr;
}


void GerenciadorDeEmprestimos::setEmprestimos(const std::vector<Emprestimo*>& novosEmprestimos) {
    this->emprestimos = novosEmprestimos;
}
