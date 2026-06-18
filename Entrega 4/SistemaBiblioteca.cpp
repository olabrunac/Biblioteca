#include "SistemaBiblioteca.h"
#include "GerenciadorDeLivros.h"
#include "GerenciadorDeUsuarios.h"
#include "GerenciadorDeEmprestimos.h"
#include "Usuario.h"
#include "Livro.h"
#include <iostream>
#include <limits>

using std::cout;
using std::cin;
using std::endl;
using std::string;

// Construtor: Recebe os gerenciadores e solicita a data atual.
SistemaBiblioteca::SistemaBiblioteca(GerenciadorDeLivros& gl, GerenciadorDeUsuarios& gu, GerenciadorDeEmprestimos& ge)
    : gerenciadorLivros(gl), gerenciadorUsuarios(gu), gerenciadorEmprestimos(ge) {
    
    cout << endl << "===== BEM-VINDO AO SISTEMA DA BIBLIOTECA =====" << endl;
    
    int dia, mes, ano;
    bool dataValida = false;
    do {
        cout << "\nPor favor, insira a data atual para iniciar o sistema." << endl;
        cout << "Dia: "; cin >> dia;
        cout << "Mes: "; cin >> mes;
        cout << "Ano: "; cin >> ano;

        // verifica se a entrada é um número
        if (cin.fail()) {
            cout << "Entrada invalida. Por favor, insira apenas numeros." << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue; // Pula para a próxima iteração do loop
        }

        // Limpa o restante da linha do buffer de entrada
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        // Usa o método estático da classe Data para validar os valores.
        if (Data::testeDataValida(dia, mes, ano)) {
            dataAtual = Data(dia, mes, ano);
            dataValida = true;
        } else {
            cout << "Data invalida! Por favor, tente novamente." << endl;
        }

    } while (!dataValida);
}

SistemaBiblioteca::~SistemaBiblioteca() {}

void SistemaBiblioteca::mostrarMenuPrincipal() {
    cout << "\n===== MENU PRINCIPAL =====" << endl;
    cout << "Data Atual: ";
    dataAtual.imprimirData(); cout << endl << endl;
    cout << "1. Cadastros" << endl;
    cout << "2. Emprestimos e Reservas" << endl;
    cout << "3. Consultas" << endl;
    cout << "0. Sair do Sistema" << endl;
    cout << "Escolha uma opcao: ";
}

// Método principal que executa o loop do menu.
void SistemaBiblioteca::executar() {
    int opcao;
    do {
        system("clear || cls"); // Limpa a tela
        mostrarMenuPrincipal();
        cin >> opcao;

        if (cin.fail()) {
            cout << "Entrada invalida. Por favor, insira um numero." << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            opcao = -1; // Força o loop a continuar
        } else {
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        switch (opcao) {
            case 1: menuCadastros(); break;
            case 2: menuEmprestimosEReservas(); break;
            case 3: menuConsultas(); break;
            case 9: menuNovaData(); break;                      //menu para mudar a data
            case 0: break; // Sair
            default:
                cout << "Opcao invalida! Tente novamente." << endl;
                break;
        }
        if (opcao != 0) {
            cout << "\nPressione Enter para continuar...";
            cin.get();
        }

    } while (opcao != 0);
}

void SistemaBiblioteca::menuCadastros() {
    int opcao;
    do {
        system("clear || cls");
        cout << "\n--- Menu de Cadastros ---" << endl;
        cout << "1. Cadastrar Livro" << endl;
        cout << "2. Cadastrar Usuario" << endl;
        cout << "3. Cadastrar Autor" << endl;
        cout << "4. Cadastrar Editora" << endl;
        cout << "--- Remocoes ---" << endl;
        cout << "5. Remover Livro" << endl;
        cout << "6. Remover Usuario" << endl;
        cout << "7. Remover Autor" << endl;
        cout << "8. Remover Editora" << endl;
        cout << "0. Voltar ao Menu Principal" << endl;
        cout << "Escolha uma opcao: ";
        cin >> opcao;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (opcao) {
            case 1: gerenciadorLivros.cadastrarLivro(); break;
            case 2: gerenciadorUsuarios.cadastrarUsuario(); break;
            case 3: gerenciadorLivros.cadastrarAutor(); break;
            case 4: gerenciadorLivros.cadastrarEditora(); break;
            case 5: gerenciadorLivros.removerLivro(gerenciadorEmprestimos); break;
            case 6: gerenciadorUsuarios.removerUsuario(gerenciadorEmprestimos); break;
            case 7: gerenciadorLivros.removerAutor(); break;
            case 8: gerenciadorLivros.removerEditora(); break;
            case 0: break;
            default: cout << "Opcao invalida!" << endl; break;
        }
        if (opcao != 0) {
            cout << "\nPressione Enter para continuar...";
            cin.get();
        }
    } while (opcao != 0);
}

void SistemaBiblioteca::menuEmprestimosEReservas() {
    int opcao;
    do {
        system("clear || cls");
        cout << "\n--- Menu de Emprestimos e Reservas ---" << endl;
        cout << "1. Realizar Emprestimo" << endl;
        cout << "2. Devolver Emprestimo" << endl;
        cout << "3. Realizar Reserva" << endl;
        cout << "4. Cancelar Reserva" << endl;
        cout << "5. Converter Reserva em Emprestimo" << endl;
        cout << "0. Voltar ao Menu Principal" << endl;
        cout << "Escolha uma opcao: ";
        cin >> opcao;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (opcao) {
            case 1: {
                cout << "--- Criar Emprestimo ---" << endl;
                cout << "Codigo do Usuario: ";
                int codUsuario;
                cin >> codUsuario;
                cin.ignore();
                Usuario* usuario = gerenciadorUsuarios.buscarUsuarioPorCodigo(codUsuario);
                if (!usuario) { cout << "Erro: Usuario nao encontrado." << endl; break; }

                cout << "Codigo do Livro: ";
                cout << "Como deseja buscar o livro?" << endl;
                cout << "1. Pelo Codigo" << endl;
                cout << "2. Pelo Titulo" << endl;
                cout << "Escolha uma opcao: ";
                int opcaoBusca;
                cin >> opcaoBusca;
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                Livro* livro = nullptr;
                if (opcaoBusca == 1) {
                    int codLivro;
                    cout << "Digite o codigo do livro: ";
                    cin >> codLivro;
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    livro = gerenciadorLivros.buscarLivroPorCodigo(codLivro);
                } else if (opcaoBusca == 2) {
                    string titulo;
                    cout << "Digite o titulo do livro: ";
                    getline(cin, titulo);
                    livro = gerenciadorLivros.buscarLivroPorNome(titulo);
                } else {
                    cout << "Opcao invalida." << endl;
                    break;
                }

                if (!livro) { cout << "Erro: Livro nao encontrado." << endl; break; }

                ExemplarLivro* exemplar = livro->getExemplarDisponivel();
                if (!exemplar) { cout << "Nao ha exemplares disponiveis." << endl; break; }

                gerenciadorEmprestimos.criarEmprestimo(*usuario, exemplar, dataAtual);
                break;
            }
            case 2: {
                cout << "--- Devolucao de Emprestimo ---" << endl;
                cout << "Codigo do Usuario: ";
                int codUsuario;
                cin >> codUsuario;
                Usuario* usuario = gerenciadorUsuarios.buscarUsuarioPorCodigo(codUsuario);
                if (!usuario) { cout << "Erro: Usuario nao encontrado." << endl; break; }

                gerenciadorEmprestimos.listarEmprestimosDoUsuario(usuario);
                cout << "\nDigite o codigo do livro a ser devolvido: ";
                int codLivro;
                cin >> codLivro;
                gerenciadorEmprestimos.realizarDevolucao(usuario, codLivro, dataAtual);
                break;
            }
            case 3: {
                cout << "--- Criar Reserva ---" << endl;
                cout << "Codigo do Usuario: ";
                int codUsuario;
                cin >> codUsuario;
                cin.ignore();
                Usuario* usuario = gerenciadorUsuarios.buscarUsuarioPorCodigo(codUsuario);
                if (!usuario) { cout << "Erro: Usuario nao encontrado." << endl; break; }

                cout << "Codigo do Livro: ";
                cout << "Como deseja buscar o livro?" << endl;
                cout << "1. Pelo Codigo" << endl;
                cout << "2. Pelo Titulo" << endl;
                cout << "Escolha uma opcao: ";
                int opcaoBusca;
                cin >> opcaoBusca;
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                Livro* livro = nullptr;
                if (opcaoBusca == 1) {
                    int codLivro;
                    cout << "Digite o codigo do livro: ";
                    cin >> codLivro;
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    livro = gerenciadorLivros.buscarLivroPorCodigo(codLivro);
                } else if (opcaoBusca == 2) {
                    string titulo;
                    cout << "Digite o titulo do livro: ";
                    getline(cin, titulo);
                    livro = gerenciadorLivros.buscarLivroPorNome(titulo);
                } else {
                    cout << "Opcao invalida." << endl;
                    break;
                }

                if (!livro) { cout << "Erro: Livro nao encontrado." << endl; break; }

                cout << "Data para reserva: Quando pretende fazer a reserva?" << endl;
                cout << "1. Hoje ou o mais rápido possível" << endl;
                cout << "2. Em uma data especifica" << endl;
                cout << "Escolha uma opcao: ";
                int opcaoReserva;
                cin >> opcaoReserva;

                if (opcaoReserva == 1) {
                    
                    gerenciadorEmprestimos.criarReserva(usuario, livro, dataAtual);
                    break;
                } else if (opcaoReserva == 2) {
                
                bool dataValidaReserva = false;
                Data dataReserva;
                int diaReserva, mesReserva, anoReserva;


                cout << "\nPor favor, insira a data para a reserva." << endl;
                cout << "Dia: "; cin >> diaReserva;
                cout << "Mes: "; cin >> mesReserva;
                cout << "Ano: "; cin >> anoReserva;

        // verifica se a entrada é um número
        if (cin.fail()) {
            cout << "Entrada invalida. Por favor, insira apenas numeros." << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue; // Pula para a próxima iteração do loop
        }

        // Limpa o restante da linha do buffer de entrada
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        // Usa o método estático da classe Data para validar os valores.
        if (Data::testeDataValida(diaReserva, mesReserva, anoReserva)) {
            dataReserva = Data(diaReserva, mesReserva,anoReserva);
            dataValidaReserva = true;
            gerenciadorEmprestimos.criarReserva(usuario, livro, dataReserva);
            break;
        } else {

            cout << "Data invalida! Por favor, tente novamente." << endl;
        }   
                
                } else {
                    cout << "Opcao invalida." << endl;
                    break;
                }

            }
            case 4: {
                cout << "--- Cancelar Reserva ---" << endl;
                cout << "Codigo do Usuario: ";
                int codUsuario;
                cin >> codUsuario;
                Usuario* usuario = gerenciadorUsuarios.buscarUsuarioPorCodigo(codUsuario);
                if (!usuario) { cout << "Erro: Usuario nao encontrado." << endl; break; }

                gerenciadorEmprestimos.listarTodasReservasUsuario(usuario);
                cout << "\nDigite o codigo do livro para cancelar a reserva: ";
                int codLivro;
                cin >> codLivro;
                gerenciadorEmprestimos.cancelarReservaItem(usuario, codLivro);
                break;
            }
            case 5: {
                cout << "--- Converter Reserva em Emprestimo ---" << endl;
                cout << "Codigo do Usuario: ";
                int codUsuario;
                cin >> codUsuario;
                Usuario* usuario = gerenciadorUsuarios.buscarUsuarioPorCodigo(codUsuario);
                if (!usuario) { cout << "Erro: Usuario nao encontrado." << endl; break; }

                Reserva* reserva = gerenciadorEmprestimos.getReservaPorUsuario(usuario);
                if (!reserva) { cout << "Nenhuma reserva encontrada para este usuario." << endl; break; }

                gerenciadorEmprestimos.criarEmprestimoApartirDaReserva(reserva, dataAtual);
                break;
            }
            case 0: break;
            default: cout << "Opcao invalida!" << endl; break;
        }
        if (opcao != 0) {
            cout << "\nPressione Enter para continuar...";
            cin.get();
        }
    } while (opcao != 0);
}

void SistemaBiblioteca::menuConsultas() {
    int opcao;
    do {
        system("clear || cls");
        cout << "\n--- Menu de Consultas ---" << endl;
        cout << "1. Listar todos os emprestimos e reservas" << endl;
        cout << "2. Consultar por Livro" << endl;
        cout << "3. Consultar por Usuario" << endl;
        cout << "4. Listar todos os livros no acervo" << endl;
        cout << "0. Voltar ao Menu Principal" << endl;
        cout << "Escolha uma opcao: ";
        cin >> opcao;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (opcao) {
            case 1: 
                gerenciadorEmprestimos.listarTodosEmprestimosAtuais(); 
                gerenciadorEmprestimos.listarTodasReservas(); 
                break;
            case 2: {
                cout << "--- Consulta por Livro ---" << endl;
                cout << "Codigo do Livro: "; 
                int codLivro;
                cin >> codLivro;
                Livro* livro = gerenciadorLivros.buscarLivroPorCodigo(codLivro);
                if (!livro) { cout << "Erro: Livro nao encontrado." << endl; break; }
                gerenciadorEmprestimos.listarEmprestimosDoLivro(*livro);
                gerenciadorEmprestimos.listarReservasDoLivro(*livro);
                break;
            }
            case 3: {
                cout << "--- Consulta por Usuario ---" << endl;
                cout << "Codigo do Usuario: "; 
                int codUsuario;
                cin >> codUsuario;
                Usuario* usuario = gerenciadorUsuarios.buscarUsuarioPorCodigo(codUsuario);
                if (!usuario) { cout << "Erro: Usuario nao encontrado." << endl; break; }
                gerenciadorEmprestimos.listarEmprestimosDoUsuario(usuario);
                gerenciadorEmprestimos.listarTodasReservasUsuario(usuario);
                break;
            }
            case 4: 
                gerenciadorLivros.getAcervo().listarTodos(); 
                break;
            case 0: break;
            default: cout << "Opcao invalida!" << endl; break;
        }
        if (opcao != 0) {
            cout << "\nPressione Enter para continuar...";
            cin.get();
        }
    } while (opcao != 0);
}

void SistemaBiblioteca::menuNovaData() { //o menu ainda nao atualiza os status
    cout << "\nMenu Secreto shhhhhh" << endl;
    
    int dia, mes, ano;
    bool dataValida = false;
    do {
        cout << "\nInsira a nova data para atualizar o sistema. (tem que ser igual ou posterior a atual)" << endl;
        cout << "Dia: "; cin >> dia;
        cout << "Mes: "; cin >> mes;
        cout << "Ano: "; cin >> ano;

        if (cin.fail()) {
            cout << "Entrada invalida. Por favor, insira apenas numeros." << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue; // Pula para a próxima iteração do loop
        }

        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (Data::testeDataValida(dia, mes, ano)) {
            Data novaData(dia, mes, ano);
            if (novaData.getDataInteira() < dataAtual.getDataInteira()) {
                cout << "Erro: a nova data nao pode ser no passado" << endl;
            } else {
                dataAtual = novaData;
                dataValida = true;
            }
        } else {
            cout << "Data invalida! Por favor, tente novamente." << endl;
        }
    } while (!dataValida);
}