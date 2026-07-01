#include "SistemaBiblioteca.h"
#include "GerenciadorDeLivros.h"
#include "GerenciadorDeUsuarios.h"
#include "GerenciadorDeEmprestimos.h"
#include "Erros.h"
#include "Usuario.h"
#include "Livro.h"
#include <iostream>
#include <limits>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::cerr;

SistemaBiblioteca::SistemaBiblioteca(GerenciadorDeLivros& gl, GerenciadorDeUsuarios& gu, GerenciadorDeEmprestimos& ge)
    : gerenciadorLivros(gl), gerenciadorUsuarios(gu), gerenciadorEmprestimos(ge) {
    
    cout << endl << "===== BEM-VINDO AO SISTEMA DA BIBLIOTECA =====" << endl;
    
    int dia, mes, ano;
    bool dataValida = false;
    do {
        cout << "\nPor favor, insira a data atual para iniciar o sistema." << endl;
        cout << "Dia: "; cin >> dia;
        cout << "Mes: "; cin >> mes;
        cout << "Ano: "; cin >> ano; cout << endl;

        // verifica se a entrada é um número
        if (cin.fail()) {
            cout << "Entrada invalida. Por favor, insira apenas numeros." << endl;
            cin.clear();
            limparBufferEntrada();
            continue; // Pula para a próxima iteração do loop
        }

        // Limpa o buffer de entrada após ler os números
        limparBufferEntrada();

        // Usa o método estático da classe Data para validar os valores.
        try {
            Data::testeDataValida(dia, mes, ano);
            dataAtual = Data(dia, mes, ano);
            dataValida = true;
        } catch (const Erros& e) {
            cerr << e.what() << " Por favor, tente novamente." << endl;
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



// loop do menu
void SistemaBiblioteca::executar() {
    int opcao;
    do {
        system("clear || cls"); // Limpa a tela
        gerenciadorLivros.getAcervo().listarTodos();    //pra listra os livros carregados
        mostrarMenuPrincipal();
        cin >> opcao;

        if (cin.fail()) {
            cout << "Entrada invalida. Por favor, insira um numero." << endl;
            cin.clear();
            limparBufferEntrada();
            opcao = -1; // Força o loop a continuar
        } else {
            limparBufferEntrada();
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
        limparBufferEntrada();

        switch (opcao) {
            case 1: try { gerenciadorLivros.cadastrarLivro(); } catch (const Erros& e) { cerr << e.what() << endl; } break;
            case 2: try { gerenciadorUsuarios.cadastrarUsuario(); } catch (const Erros& e) { cerr << e.what() << endl; } break;
            case 3: try { gerenciadorLivros.cadastrarAutor(); } catch (const Erros& e) { cerr << e.what() << endl; } break;
            case 4: try { gerenciadorLivros.cadastrarEditora(); } catch (const Erros& e) { cerr << e.what() << endl; } break;
            case 5: try { gerenciadorLivros.removerLivro(gerenciadorEmprestimos); } catch (const Erros& e) { cerr << e.what() << endl; } break;
            case 6: try { gerenciadorUsuarios.removerUsuario(gerenciadorEmprestimos); } catch (const Erros& e) { cerr << e.what() << endl; } break;
            case 7: try { gerenciadorLivros.removerAutor(); } catch (const Erros& e) { cerr << e.what() << endl; } break;
            case 8: try { gerenciadorLivros.removerEditora(); } catch (const Erros& e) { cerr << e.what() << endl; } break;
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
        limparBufferEntrada();

        switch (opcao) {
            case 1: {
                Usuario* usuario = nullptr;
                Livro* livro = nullptr;
                try {
                    cout << "--- Criar Emprestimo ---" << endl;
                    cout << "Codigo do Usuario: ";
                    int codUsuario;
                    cin >> codUsuario;
                    limparBufferEntrada();
                    usuario = gerenciadorUsuarios.buscarUsuarioPorCodigo(codUsuario);
                    if (usuario->getStatus() != StatusUsuario::HABILITADO) {        //tirei do gerenciadordeemprestimos para dar flag no usuario antes de tentar o emprestimo
                        throw ErroUsuarioNaoHabilitado();
                    }

                    int opcaoBusca;
                    do {
                        cout << "\nComo deseja buscar o livro?" << endl;
                        cout << "1. Pelo Codigo" << endl;
                        cout << "2. Pelo Titulo" << endl;
                        cout << "0. Voltar" << endl;
                        cout << "Escolha uma opcao: ";
                        cin >> opcaoBusca;

                        if (cin.fail()) {
                            cin.clear();
                            limparBufferEntrada();
                            cerr << "[ErroOpcaoInvalida]: A opcao digitada eh invalida. Por favor, insira um numero." << endl;
                            opcaoBusca = -1; // Força a repetição do loop
                        } else if (opcaoBusca < 0 || opcaoBusca > 2) {
                            cerr << "[ErroOpcaoInvalida]: Opcao nao existe. Tente novamente." << endl;
                        }
                    } while (opcaoBusca < 0 || opcaoBusca > 2);

                    limparBufferEntrada();

                    if (opcaoBusca == 0) break; // Volta para o menu de empréstimos

                    if (opcaoBusca == 1) {
                        int codLivro;
                        cout << "Digite o codigo do livro: ";
                        cin >> codLivro;
                        limparBufferEntrada();
                        livro = gerenciadorLivros.buscarLivroPorCodigo(codLivro);
                    } else if (opcaoBusca == 2) {
                        string titulo;
                        cout << "Digite o titulo do livro: ";
                        getline(cin, titulo);
                        livro = gerenciadorLivros.buscarLivroPorNome(titulo);
                    }    

                    ExemplarLivro* exemplar = livro->getExemplarDisponivel();
                    gerenciadorEmprestimos.criarEmprestimo(*usuario, exemplar, dataAtual);
                } catch (const ErroLivroIndisponivelE& e) {
                    cerr << e.what() << endl;
                    if (usuario && livro) { // Garante que usuario e livro foram encontrados antes de oferecer a reserva
                        cout << "Deseja fazer uma reserva para este livro? (S/N): ";
                        char resposta;
                        cin >> resposta;
                        limparBufferEntrada();
                        if (toupper(resposta) == 'S') {
                            try {
                                gerenciadorEmprestimos.criarReserva(usuario, livro, dataAtual);
                            } catch (const Erros& e_reserva) {
                                cerr << e_reserva.what() << endl;
                            }
                        }
                    }
                } catch (const Erros& e) {
                    cerr << e.what() << endl;
                    cout << "\nPressione Enter para continuar...";
                    cin.get();
                    return; // Retorna para o menu de Empréstimos e Reservas
                }
                break;
            }
            case 2: {
                try {
                    cout << "--- Devolucao de Emprestimo ---" << endl;
                    cout << "Codigo do Usuario: ";
                    int codUsuario;
                    cin >> codUsuario;
                    limparBufferEntrada();
                    Usuario* usuario = gerenciadorUsuarios.buscarUsuarioPorCodigo(codUsuario);

                    gerenciadorEmprestimos.listarEmprestimosDoUsuario(usuario);
                    cout << "\nDigite o codigo do livro a ser devolvido: ";
                    int codLivro;
                    cin >> codLivro;
                    limparBufferEntrada();
                    gerenciadorEmprestimos.realizarDevolucao(usuario, codLivro, dataAtual);
                } catch (const Erros& e) {
                    cerr << e.what() << endl;
                }
                break;
            }
            case 3: {
                Usuario* usuario = nullptr;
                Livro* livro = nullptr;
                try {
                    cout << "--- Criar Reserva ---" << endl;
                    cout << "Codigo do Usuario: ";
                    int codUsuario;
                    cin >> codUsuario;
                    limparBufferEntrada();
                    Usuario* usuario = gerenciadorUsuarios.buscarUsuarioPorCodigo(codUsuario);
                    if (usuario->getStatus() != StatusUsuario::HABILITADO) {        //tirei do gerenciadordeemprestimos para dar flag no usuario antes de tentar o emprestimo       
                        throw ErroUsuarioNaoHabilitado();
                    }

                    int opcaoBusca;
                    do {
                        cout << "\nComo deseja buscar o livro?" << endl;
                        cout << "1. Pelo Codigo" << endl;
                        cout << "2. Pelo Titulo" << endl;
                        cout << "0. Voltar" << endl;
                        cout << "Escolha uma opcao: ";
                        cin >> opcaoBusca;

                        if (cin.fail()) {
                            cin.clear();
                            limparBufferEntrada();
                            cerr << "[ErroOpcaoInvalida]: A opcao digitada eh invalida. Por favor, insira um numero." << endl;
                            opcaoBusca = -1;
                        } else if (opcaoBusca < 0 || opcaoBusca > 2) {
                            cerr << "[ErroOpcaoInvalida]: Opcao nao existe. Tente novamente." << endl;
                        }
                    } while (opcaoBusca < 0 || opcaoBusca > 2);

                    limparBufferEntrada();

                    if (opcaoBusca == 0) break;

                    if (opcaoBusca == 1) {
                        int codLivro;
                        cout << "Digite o codigo do livro: ";
                        cin >> codLivro;
                        limparBufferEntrada();
                        livro = gerenciadorLivros.buscarLivroPorCodigo(codLivro);
                    } else if (opcaoBusca == 2) {
                        string titulo;
                        cout << "Digite o titulo do livro: ";
                        getline(cin, titulo);
                        livro = gerenciadorLivros.buscarLivroPorNome(titulo);
                    }

                    int opcaoReserva;
                    do {
                        cout << "\nData para reserva: Quando pretende fazer a reserva?" << endl;
                        cout << "1. Hoje ou o mais rapido possivel" << endl;
                        cout << "2. Em uma data especifica" << endl;
                        cout << "0. Voltar" << endl;
                        cout << "Escolha uma opcao: ";
                        cin >> opcaoReserva;

                        if (cin.fail()) {
                            cin.clear();
                            limparBufferEntrada();
                            cerr << "[ErroOpcaoInvalida]: A opcao digitada eh invalida. Por favor, insira um numero." << endl;
                            opcaoReserva = -1;
                        } else if (opcaoReserva < 0 || opcaoReserva > 2) {
                            cerr << "[ErroOpcaoInvalida]: Opcao nao existe. Tente novamente." << endl;
                        } else if (opcaoReserva == 1) {
                            gerenciadorEmprestimos.criarReserva(usuario, livro, dataAtual);
                            limparBufferEntrada();
                        } else if (opcaoReserva == 2) {
                            int dia, mes, ano;
                            cout << "\nInsira a data da reserva (DD MM AAAA): ";
                            cin >> dia >> mes >> ano;
                            if (cin.fail() || !Data::testeDataValida(dia, mes, ano)) {
                                cerr << "[ErroData]: Data invalida. Tente novamente." << endl;
                                if(cin.fail()) cin.clear();
                                limparBufferEntrada();
                                opcaoReserva = -1; // Força repetição
                            } else {
                                Data dataReserva(dia, mes, ano);
                                gerenciadorEmprestimos.criarReserva(usuario, livro, dataReserva);
                                cout << "\nPressione Enter para continuar...1";
                                cin.get();
                            }
                        }
                    } while (opcaoReserva == -1);
                } catch (const Erros& e) {
                    cerr << e.what() << endl;
                    cout << "\nPressione Enter para continuar...2";
                    cin.get();
                    return; // Retorna para o menu de Empréstimos e Reservas
                }

                break;
            }
            case 4: {
                try {
                    cout << "--- Cancelar Reserva ---" << endl;
                    cout << "Codigo do Usuario: ";
                    int codUsuario;
                    cin >> codUsuario;
                    limparBufferEntrada();
                    Usuario* usuario = gerenciadorUsuarios.buscarUsuarioPorCodigo(codUsuario);

                    gerenciadorEmprestimos.listarTodasReservasUsuario(usuario);

                    cout << "\nDigite o codigo do livro para cancelar a reserva: ";
                    int codLivro;
                    cin >> codLivro;
                    limparBufferEntrada();

                    gerenciadorEmprestimos.cancelarReservaItem(usuario, codLivro);
                } catch (const Erros& e) {
                    cerr << e.what() << endl;
                }
                break;
            }
            case 5: {
                try {
                    cout << "--- Converter Reserva em Emprestimo ---" << endl;
                    cout << "Codigo do Usuario: ";
                    int codUsuario;
                    cin >> codUsuario;
                    limparBufferEntrada();
                    Usuario* usuario = gerenciadorUsuarios.buscarUsuarioPorCodigo(codUsuario);

                    Reserva* reserva = gerenciadorEmprestimos.getReservaPorUsuario(usuario);
                    if (!reserva) { throw ErroNenhumaReserva(); }

                    gerenciadorEmprestimos.criarEmprestimoApartirDaReserva(reserva, dataAtual);
                } catch (const Erros& e) {
                    cerr << e.what() << endl;
                }
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
        cout << "5. Listar todos os usuarios" << endl;
        cout << "6. Listar todos os autores" << endl;
        cout << "7. Listar todas as editoras" << endl;
        cout << "0. Voltar ao Menu Principal" << endl;
        cout << "Escolha uma opcao: ";
        cin >> opcao;
        limparBufferEntrada();

        switch (opcao) {
            case 1: 
                try {
                    gerenciadorEmprestimos.listarTodosEmprestimosAtuais(); 
                } catch (const Erros& e) { cerr << e.what() << endl; }
                try {
                    gerenciadorEmprestimos.listarTodasReservas(); 
                } catch (const Erros& e) { cerr << e.what() << endl; }
                break;

            case 2: {
                try {
                    cout << "--- Consulta por Livro ---" << endl;
                    cout << "Codigo do Livro: "; 
                    int codLivro;
                    cin >> codLivro;
                    limparBufferEntrada();
                    Livro* livro = gerenciadorLivros.buscarLivroPorCodigo(codLivro);
                    
                    gerenciadorEmprestimos.listarEmprestimosDoLivro(*livro);
                    gerenciadorEmprestimos.listarReservasDoLivro(*livro);
                } catch (const Erros& e) {
                    cerr << e.what() << endl;
                }
                break;
            }

            case 3: {
                try {
                    cout << "--- Consulta por Usuario ---" << endl;
                    cout << "Codigo do Usuario: "; 
                    int codUsuario;
                    cin >> codUsuario;
                    limparBufferEntrada();
                    Usuario* usuario = gerenciadorUsuarios.buscarUsuarioPorCodigo(codUsuario);
                    
                    gerenciadorEmprestimos.listarEmprestimosDoUsuario(usuario);
                    gerenciadorEmprestimos.listarTodasReservasUsuario(usuario);
                } catch (const Erros& e) {
                    cerr << e.what() << endl;
                }
                break;
            }
            case 4: 
                try { gerenciadorLivros.getAcervo().listarTodos(); }
                catch (const Erros& e) { cerr << e.what() << endl; }
                break;
            case 5:
                try { gerenciadorUsuarios.listarTodosUsuarios(); }
                catch (const Erros& e) { cerr << e.what() << endl; }
                break;
            case 6:
                try { gerenciadorLivros.listarTodosAutores(); }
                catch (const Erros& e) { cerr << e.what() << endl; }
                break;
            case 7:
                try { gerenciadorLivros.listarTodasEditoras(); }
                catch (const Erros& e) { cerr << e.what() << endl; }
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
    cout << "\n---- Menu Secreto ----" << endl;
    
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
            limparBufferEntrada();
            continue; // Pula para a próxima iteração do loop
        }

        limparBufferEntrada();

        try {
            Data::testeDataValida(dia, mes, ano);
            Data novaData(dia, mes, ano);
            if (novaData.getDataInteira() < dataAtual.getDataInteira()) {
                cout << "Erro: a nova data nao pode ser no passado" << endl;
            } else {
                dataAtual = novaData;
                dataValida = true;
                gerenciadorEmprestimos.atualizaPendenciasEmprestimos(dataAtual);
            }
        } catch (const Erros& e) {
            cerr << e.what() << " Por favor, tente novamente." << endl;
        }
    } while (!dataValida);
}