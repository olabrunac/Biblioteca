#include "GerenciadorDeEmprestimos.h"
#include "Usuario.h"
#include "StatusEmprestimo.h"
#include <iostream>

#include "Erros.h"

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


void GerenciadorDeEmprestimos::criarEmprestimo(Usuario& emprestimoUsuario, ExemplarLivro* exemplar, const Data& dataAtual) { //1
    // REGRA DE NEGÓCIO: Verifica se o usuário está habilitado para empréstimos.
    if (emprestimoUsuario.getStatus() != StatusUsuario::HABILITADO) {
        
        throw ErroUsuarioNaoHabilitado();
    }

   // ve se o usuario ja tem algum emprestimo
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


void GerenciadorDeEmprestimos::criarEmprestimo(Usuario& emprestimoUsuario, initializer_list<ExemplarLivro*> listaExemplares, const Data& dataAtual) { //2
    
    // REGRA DE NEGÓCIO: Verifica se o usuário está habilitado para empréstimos.
    if (emprestimoUsuario.getStatus() != StatusUsuario::HABILITADO) {
      
        throw ErroUsuarioNaoHabilitado();
    }

    //adicionar a verificação de se o usuario já fez um emprestimo desse livro


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
            delete novoEmprestimo;
            throw ErroLivroIndisponivel(); // Erro mais apropriado, pois o livro existe mas não está disponível no período.
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
            throw ErroEmprestimoVazio();
    }
}


void GerenciadorDeEmprestimos::criarEmprestimoApartirDaReserva(Reserva* reservaExistente, const Data& dataAtual) { //3
    
    // REGRA DE NEGÓCIO: Verifica se o usuário da reserva está habilitado.
    if (reservaExistente->getUsuario()->getStatus() != StatusUsuario::HABILITADO) {
       throw ErroUsuarioNaoHabilitado();
    }   

    // 1. Validação: Verifica a disponibilidade de todos os livros na reserva.
    for(auto temp : reservaExistente->getItens()) { 
        if(temp->getLivro()->getExemplarDisponivel() == nullptr) {
            throw ErroLivroIndisponivel();
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


void GerenciadorDeEmprestimos::criarReserva(Usuario* reservaUsuario, Livro* reservaLivro, Data& dataRealizacao) { //4

    // 1. Validação do Usuario
    if (reservaUsuario->getStatus() != StatusUsuario::HABILITADO) {
        throw ErroUsuarioNaoHabilitado();
    }

    // 2. Busca se o usuário já possui um "Carrinho" de reservas aberto
    Reserva* reservaDoUsuario = getReservaPorUsuario(reservaUsuario);

    // 3. Validação do Livro Repetido
    if (reservaDoUsuario != nullptr && reservaDoUsuario->possuiLivro(reservaLivro)) {
        throw ErroUsuarioJaReservouLivro();
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


//-------------------- listagem --------------------


void GerenciadorDeEmprestimos::listarTodosEmprestimosAtuais() { //5
    for (auto temp : emprestimos) {
        temp->imprimirEmprestimo();
    }
}


void GerenciadorDeEmprestimos::listarReservasDoLivro(Livro& listaLivro) { //6
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
        ErroExemplarGuardado();
    } 
}


void GerenciadorDeEmprestimos::listarTodasReservas() { //7
    cout << endl << "----- Lista de Reservas Ativas -----" << endl;
    
    if (reservas.empty()) {
        throw ErroSistemaVazio();
    }
    // Itera sobre o vetor de reservas e chama o método de impressão de cada uma.
    for (auto temp : reservas) {
        temp->imprimirReserva();
        cout << endl;
    }
}


void GerenciadorDeEmprestimos::listarTodasReservasUsuario(Usuario* usuarioBuscado) const { //8
    if (usuarioBuscado == nullptr) {

      throw ErroUsuarioNaoExiste();
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
        throw ErroNenhumaReserva();
    } else { //Usar tratamento de exceções
        cout << "\nTotal de reservas encontradas: " << totalReservasEncontradas << endl;
    }
}


void GerenciadorDeEmprestimos::listarEmprestimosDoUsuario(Usuario* usuario) { //9
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
       throw ErroNenhumEmprestimo();
    } 
}


void GerenciadorDeEmprestimos::listarEmprestimosDoLivro(Livro& livro) { //10
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
       throw ErroExemplarGuardado();
    } 
}


//-------------------- contas --------------------


int GerenciadorDeEmprestimos::contarEmprestimosAtivos(Livro& livro) const {  //11
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


int GerenciadorDeEmprestimos::contarReservasAtivas(Livro& livro) const { //12
    int contador = 0;
    for (const auto& temp : reservas) {
        if (temp->possuiLivro(&livro)) {
            // Conta a reserva se ela contém o livro especificado.
            contador++;
        }
    }
    return contador;
}


//-------------------- ações --------------------


bool GerenciadorDeEmprestimos::realizarDevolucao(Usuario* usuario, int codigoLivro, const Data& dataDevolucao) { //13
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
                    
                    //remover do vetor emprestimos
                    return true;
                }
            }
        }
    }
    throw ErroNenhumEmprestimo();
    return false; 
}


bool GerenciadorDeEmprestimos::cancelarReservaItem(Usuario* usuario, int codigoLivro) { //14
    Reserva* reserva = getReservaPorUsuario(usuario);
    
    if (!reserva) {
        throw ErroNenhumaReserva();
        return false; // Retorno de segurança
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
        
        return true; // CORRETO: Retorna sucesso para quem chamou a função
    }
    
    throw ErroLivroNaoExisteAcervo();
    return false; // CORRETO: Retorno de segurança caso o compilador reclame do throw
}


bool GerenciadorDeEmprestimos::usuarioTemPendencias(Usuario* usuario) const { //15
    // Verifica se tem empréstimos ativos
    for (auto& temp : emprestimos) {
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


void GerenciadorDeEmprestimos::atualizaPendenciasEmprestimos(Data& dataFutura){ //16

    cout << "---------- VERIFICANDO EMPRESTIMOS ATRASADOS" << endl;

    for(auto& temp: emprestimos)

        if(temp->getStatus() == 1) //se o emprestimo está ativo
            //tendo o emprestimo ativo, agora verificamos se a dataFutura(quando utilizamos a função secreta novaData)
            //verifica se era para o emprestimo ser devolvido antes dessa data que foi passada
            if (Data(temp->getDataPrevistaDevolucao()) < dataFutura ){
                //usei o construtor de data, pois getDataPrevistaDevolucao é int

                temp->getUsuario()->setStatus(StatusUsuario::EM_DEBITO);
                //pega o usuario do emprestimo que atrasou e muda o status dele
                cout << "Empréstimo de:" << temp->getUsuario()->getNome() << " está atrasado" << endl;
                throw ErroUsuarioNaoHabilitado();
                


                //testar essa logica basica, depois adicionar qtd de dias atrasado

              
            }

}


bool GerenciadorDeEmprestimos::estaDisponivelnaData(Livro* testeLivro, const Data& dataInicial, const Data& dataFinal){ //17

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


Reserva* GerenciadorDeEmprestimos::getReservaPorUsuario(Usuario* usuarioBuscado) const { //18
    for (auto temp : reservas) {
        if (temp->getUsuario() == usuarioBuscado) {
            return temp; // Retorna o ponteiro para a reserva encontrada.
        }
    }
    return nullptr; // Retorna nulo se nenhuma reserva for encontrada para o usuário.
}


Emprestimo* GerenciadorDeEmprestimos::getEmprestimoPorUsuario(Usuario* usuarioBuscado) const { //19
    for (auto temp : emprestimos) {
        if (temp->getUsuario() == usuarioBuscado && temp->getStatus() == 1) {
            return temp;
        }
    }
    return nullptr;
}