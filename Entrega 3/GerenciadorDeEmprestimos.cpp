#include "GerenciadorDeEmprestimos.h"
#include "Usuario.h"
#include "StatusEmprestimo.h"
#include <iostream>

using std::cout;
using std::endl;

GerenciadorDeEmprestimos::GerenciadorDeEmprestimos() {} 


GerenciadorDeEmprestimos::~GerenciadorDeEmprestimos() {
    // Libera a memória de todos os empréstimos criados dinamicamente.
    for (auto temp : emprestimos) {
        delete temp;
    }
    emprestimos.clear();

    // Libera a memória de todas as reservas criadas dinamicamente.
    for (auto temp : reservas) {
        delete temp;
    }
    reservas.clear();
}


void GerenciadorDeEmprestimos::criarEmprestimo(Usuario& emprestimoUsuario, ExemplarLivro* exemplar, const Data& dataAtual) {
    // REGRA DE NEGÓCIO: Verifica se o usuário está habilitado para empréstimos.
    if (emprestimoUsuario.getStatus() != StatusUsuario::HABILITADO) {
        cout << "O usuario: '" << emprestimoUsuario.getNome();
        cout << "' nao esta habilitado para realizar emprestimos." << endl;
        return;
    }

    Emprestimo* novoEmprestimo = new Emprestimo();
    novoEmprestimo->setUsuario(&emprestimoUsuario);
    novoEmprestimo->setStatus(1);
    novoEmprestimo->setDataDeRetirada(dataAtual);

    int itensAdicionados = 0;

    // Verifica se o exemplar é válido e está disponível.
    bool disponivelNoPeriodo = false;
    if (exemplar != nullptr) {
        Livro* livro = exemplar->getLivro();
        disponivelNoPeriodo = estaDisponivelnaData(livro, dataAtual, dataAtual + livro->getNroDiasPermitidoEmprestimo());
    }
    
    if (exemplar != nullptr && exemplar->getStatus() == StatusEmprestimo::DISPONIVEL && disponivelNoPeriodo) {
        exemplar->setStatus(StatusEmprestimo::EMPRESTADO); // usuario pode fazer imprestimo

        ItemEmprestimo* novoItem = new ItemEmprestimo();
        novoItem->setExemplar(exemplar);
        
        int diasPermitidos = exemplar->getLivro()->getNroDiasPermitidoEmprestimo();
        Data dataPrevista = dataAtual + diasPermitidos;

        novoItem->setDataParaDevolucao(dataPrevista);
        novoItem->setDataQueFoiDevolvido(0); // Inicializa como não devolvido

        novoEmprestimo->adicionarItem(novoItem);
        novoEmprestimo->setDataPrevistaDevolucao(dataPrevista);
        novoEmprestimo->setDataDevolucao(0); // Inicializa como não devolvido

        itensAdicionados++;
    } else {
        if (exemplar != nullptr && !disponivelNoPeriodo) {
            cout << "-Nao foi possivel realizar o emprestimo: O livro '" << exemplar->getLivro()->getTitulo() << "' ja possui reservas para este periodo." << endl;
        } else {
            cout << "-Nao foi possivel realizar o emprestimo para " << emprestimoUsuario.getNome() << "." << endl;
        }
    }
    if (itensAdicionados > 0) {
        emprestimos.push_back(novoEmprestimo);
        cout << "+'" << exemplar->getLivro()->getTitulo();
        cout << "' emprestado para: " << emprestimoUsuario.getNome() << " com sucesso!" << endl;
        cout << "  Devolucao prevista para: ";
        novoEmprestimo->getDataPrevistaDevolucao().imprimirData();
        cout << endl;
    } else {
        // Se nenhum item foi adicionado, o empréstimo não é criado e a memória é liberada.
        delete novoEmprestimo;
        cout << "-Nenhum item adicionado. Emprestimo cancelado." << endl;
    }
}


void GerenciadorDeEmprestimos::criarEmprestimo(Usuario& emprestimoUsuario, initializer_list<ExemplarLivro*> listaExemplares, const Data& dataAtual) {
    
    // REGRA DE NEGÓCIO: Verifica se o usuário está habilitado para empréstimos.
    if (emprestimoUsuario.getStatus() != StatusUsuario::HABILITADO) {
        cout << "O usuario: '" << emprestimoUsuario.getNome();
        cout << "' nao esta habilitado para realizar emprestimos." << endl;
        return;
    }

    Emprestimo* novoEmprestimo = new Emprestimo();
    novoEmprestimo->setUsuario(&emprestimoUsuario);
    novoEmprestimo->setStatus(1);
    novoEmprestimo->setDataDeRetirada(dataAtual);

    int itensAdicionados = 0;
    int maiorPrazoDias = 0;

    for (auto temp : listaExemplares) {
        ExemplarLivro* exemplar = temp;

        // Verifica se o exemplar é válido e está disponível.
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
            cout << "Aviso: O livro '" << exemplar->getLivro()->getTitulo() << "' possui conflito com reservas futuras." << endl;
        }
    }

    if (itensAdicionados > 0) {
        novoEmprestimo->setDataPrevistaDevolucao(dataAtual + maiorPrazoDias);
        novoEmprestimo->setDataDevolucao(0);
        emprestimos.push_back(novoEmprestimo);
        cout << "+" << itensAdicionados << " itens emprestados com sucesso para " << emprestimoUsuario.getNome() << "!" << endl;
    } else {
        // Se a lista de entrada não continha exemplares válidos, cancela a operação.
        delete novoEmprestimo;
        cout << "-Nenhum item adicionado. Emprestimo cancelado." << endl;
    }
}


void GerenciadorDeEmprestimos::listarTodosEmprestimosAtuais() { 
    for (auto temp : emprestimos) {
        temp->imprimirEmprestimo();
    }
}


// Função de apoio para a regra de negócio que impede a exclusão de livros em uso.
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

// Função de apoio para a regra de negócio que impede a exclusão de livros em uso.
int GerenciadorDeEmprestimos::contarReservasAtivas(Livro& livro) const {
    int contador = 0;
    for (const auto& temp : reservas) {
        if (temp->possuiLivro(&livro)) {
            // Conta a reserva se ela contém o livro especificado.
            contador++;
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
    
    // Verifica se o livro tem algum exemplar físico disponível no momento.
    if (reservaLivro->estaDisponivel()) { 
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


void GerenciadorDeEmprestimos::criarEmprestimoApartirDaReserva(Reserva* reservaExistente, const Data& dataAtual) {
    
    // REGRA DE NEGÓCIO: Verifica se o usuário da reserva está habilitado.
    if (reservaExistente->getUsuario()->getStatus() != StatusUsuario::HABILITADO) {
        cout << "Erro: o usuário associado a esta reserva não pode fazer empréstimos." << endl;
        return;
    }   

    // 1. Validação: Verifica a disponibilidade de todos os livros na reserva.
    for(auto temp : reservaExistente->getItens()) { 
        if(temp->getLivro()->getExemplarDisponivel() == nullptr) {
            cout << "Erro: o livro '" << temp->getLivro()->getTitulo() << "' nao possui exemplares disponiveis no momento" << endl;
            return;
        }
    }
    
    // 2. Criação: Inicia um único objeto de Empréstimo para todos os itens.
    Emprestimo* novoEmprestimo = new Emprestimo();
    novoEmprestimo->setUsuario(reservaExistente->getUsuario());
    novoEmprestimo->setStatus(1);
    novoEmprestimo->setDataDeRetirada(dataAtual);
    novoEmprestimo->setDataDevolucao(0);
    int maiorPrazoDias = 0;

    // 3. Processamento: Itera sobre os itens da reserva e os adiciona ao novo empréstimo.
    for(auto tempItem : reservaExistente->getItens()){
        ExemplarLivro* exemplar = tempItem->getLivro()->getExemplarDisponivel();
        exemplar->setStatus(StatusEmprestimo::EMPRESTADO);
        
        ItemEmprestimo* novoItemEmprestimo = new ItemEmprestimo();
        novoItemEmprestimo->setExemplar(exemplar);

        // Calcula a data de devolução para cada item e atualiza o prazo geral do empréstimo.
        int dias = exemplar->getLivro()->getNroDiasPermitidoEmprestimo();
        if (dias > maiorPrazoDias) maiorPrazoDias = dias;
        novoItemEmprestimo->setDataParaDevolucao(dataAtual + dias);
        novoItemEmprestimo->setDataQueFoiDevolvido(0);

        novoEmprestimo->adicionarItem(novoItemEmprestimo);
    }
    novoEmprestimo->setDataPrevistaDevolucao(dataAtual + maiorPrazoDias);
    emprestimos.push_back(novoEmprestimo);

    // 4. Limpeza: Remove a reserva original do sistema após a conversão.
        for(auto temp = reservas.begin(); temp != reservas.end(); ++temp) {
            if ((*temp)->getID() == reservaExistente->getID()) {
                delete *temp;       // Libera a memória do objeto Reserva.
                reservas.erase(temp);       // Remove o ponteiro do vetor.
                break;
            }
        }
        cout << "+Sucesso: Reserva convertida em emprestimo" << endl;
}


void GerenciadorDeEmprestimos::listarTodasReservas() {
    cout << endl << "----- Lista de Reservas Ativas -----" << endl;
    
    if (reservas.empty()) {
        cout << "Nenhuma reserva no sistema." << endl;
        return;
    }
    // Itera sobre o vetor de reservas e chama o método de impressão de cada uma.
    for (auto temp : reservas) {
        temp->imprimirReserva();
        cout << endl;
    }
}

void GerenciadorDeEmprestimos::listarTodasReservasUsuario(Usuario* usuarioBuscado) const {
    if (usuarioBuscado == nullptr) {
        cout << "Erro: Usuario invalido (ponteiro nulo)." << endl;
        return;
    }

    cout << "\n----- Reservas Ativas de: " << usuarioBuscado->getNome() << " -----" << endl;
    
    int totalReservasEncontradas = 0;

    for (const auto& temp : reservas) {
        // Se a reserva pertencer ao usuário que estamos buscando
        if (temp->getUsuario() == usuarioBuscado) {
            totalReservasEncontradas++;
            
            cout << "\n[ Ocorrencia #" << totalReservasEncontradas << " ]" << endl;
            
            // Aqui usamos a própria classe Reserva para imprimir seus detalhes e seus itens!
            temp->imprimirReserva(); 
            
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

        if(temp->possuiLivro(testeLivro)){ //Se ele já foi Emprestado
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
            return temp; // Retorna o ponteiro para a reserva encontrada.
        }
    }
    return nullptr; // Retorna nulo se nenhuma reserva for encontrada para o usuário.
}

bool GerenciadorDeEmprestimos::realizarDevolucao(Usuario* usuario, int codigoLivro, const Data& dataDevolucao) {
    for (auto temp : emprestimos) {
        // Procura um empréstimo ativo do usuário
        if (temp->getUsuario() == usuario && temp->getStatus() == 1) {
            for (auto tempItem : temp->getItens()) {
                // Procura o livro específico que ainda não foi devolvido
                if (tempItem->getExemplar()->getLivro()->getCodigo() == codigoLivro && tempItem->getExemplar()->getStatus() == StatusEmprestimo::EMPRESTADO) {
                    
                    // Realiza a devolução
                    tempItem->getExemplar()->setStatus(StatusEmprestimo::DISPONIVEL);
                    tempItem->setDataQueFoiDevolvido(dataDevolucao.getDataInteira());
                    
                    cout << "Devolucao do livro '" << tempItem->getExemplar()->getLivro()->getTitulo() << "' realizada com sucesso." << endl;
                    
                    // Opcional: verificar se todos os itens do empréstimo foram devolvidos para finalizar o empréstimo
                    bool todosDevolvidos = true;
                    for (auto tempCheck : temp->getItens()) {
                        if (tempCheck->getExemplar()->getStatus() == StatusEmprestimo::EMPRESTADO) {
                            todosDevolvidos = false;
                            break;
                        }
                    }
                    if (todosDevolvidos) {
                        temp->setStatus(0); // Marca o empréstimo como finalizado
                        cout << "Todos os itens deste emprestimo foram devolvidos." << endl;
                    }

                    return true;
                }
            }
        }
    }
    cout << "Nenhum emprestimo ativo encontrado para este livro e usuario." << endl;
    return false;
}

bool GerenciadorDeEmprestimos::cancelarReservaItem(Usuario* usuario, int codigoLivro) {
    Reserva* reserva = getReservaPorUsuario(usuario);
    if (!reserva) {
        cout << "Erro: Nenhuma reserva encontrada para o usuario " << usuario->getNome() << "." << endl;
        return false;
    }

    if (reserva->removerItemPorLivro(codigoLivro)) {
        cout << "Item da reserva cancelado com sucesso." << endl;
        // Se a reserva ficou vazia, remove ela completamente
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
    
    cout << "Erro: Livro com codigo " << codigoLivro << " nao encontrado na reserva deste usuario." << endl;
    return false;
}

void GerenciadorDeEmprestimos::listarEmprestimosDoUsuario(Usuario* usuario) {
    // CONSULTA: Visualização de todos os empréstimos de um determinado usuário.
    cout << "\n----- Emprestimos do usuario: " << usuario->getNome() << " -----" << endl;
    bool encontrou = false;
    for (const auto& temp : emprestimos) {
        if (temp->getUsuario() == usuario) {
            temp->imprimirEmprestimo();
            encontrou = true;
        }
    }
    if (!encontrou) {
        cout << "Nenhum emprestimo ativo para este usuario." << endl;
    }
}

void GerenciadorDeEmprestimos::listarEmprestimosDoLivro(Livro& livro) {
    // CONSULTA: Visualização de todos os empréstimos de um determinado livro.
    cout << "\n----- Emprestimos para o livro: '" << livro.getTitulo() << "' -----" << endl;
    bool encontrou = false;
    for (const auto& temp : emprestimos) {
        for (const auto& tempItem : temp->getItens()) {
            if (tempItem->getExemplar()->getLivro()->getCodigo() == livro.getCodigo()) {
                cout << "- Emprestado para: " << temp->getUsuario()->getNome();
                cout << " (Cod: " << temp->getUsuario()->getCodigo() << ") | Exemplar ID: " << tempItem->getExemplar()->getNroExemplar();
                cout << " | Devolucao: ";
                tempItem->getDataParaDevolucao().imprimirData();
                cout << endl;
                encontrou = true;
            }
        }
    }
    if (!encontrou) {
        cout << "Nenhum exemplar deste livro esta emprestado no momento." << endl;
    }
}

void GerenciadorDeEmprestimos::listarReservasDoLivro(Livro& listaLivro) {
    // CONSULTA: Visualização de todas as reservas de um determinado livro.
    cout << "----- Reservas para o livro: '" << listaLivro.getTitulo() << "' -----" << endl;
    bool encontrou = false;

    for (auto temp : reservas) {
        if (temp->possuiLivro(&listaLivro)) {
            for (auto tempItem : temp->getItens()) {
                if (tempItem->getLivro() == &listaLivro) {
                    encontrou = true;
                    cout << "- Reservado por: " << temp->getUsuario()->getNome();
                    cout << " (Cod: " << temp->getUsuario()->getCodigo() << ") | Retirada prevista para: ";
                    tempItem->getDataDeRetirada().imprimirData();
                    cout << endl;
                }
            }
        }
    }

    if (!encontrou) {
        cout << "Nenhum usuario reservou este livro no momento." << endl;
    }
}

bool GerenciadorDeEmprestimos::usuarioTemPendencias(Usuario* usuario) const {
    // Verifica se tem empréstimos ativos
    for (auto temp : emprestimos) {
        if (temp->getUsuario() == usuario && temp->getStatus() == 1) {
            return true;
        }
    }
    // Verifica se tem reservas
    if (getReservaPorUsuario(usuario) != nullptr) {
        return true;
    }
    return false;
}
