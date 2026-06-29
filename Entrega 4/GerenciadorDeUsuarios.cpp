#include "GerenciadorDeUsuarios.h"
#include "Aluno.h"
#include "Professor.h"
#include "Pesquisador.h"
#include "Erros.h"
#include <iostream>
#include <limits>

using std::cout;
using std::cin;
using std::endl;
using std::string;


GerenciadorDeUsuarios::GerenciadorDeUsuarios() : proximoCodigoUsuario(0) {}


GerenciadorDeUsuarios::~GerenciadorDeUsuarios() {
    for (auto temp : usuarios) {
        delete temp;
    }
    usuarios.clear();
}


void GerenciadorDeUsuarios::inicializarDados() {
    usuarios.push_back(new Aluno(1, "Matheus"));
    usuarios.push_back(new Aluno(2, "Bruna"));
    usuarios.push_back(new Aluno(3, "Ryan"));
    usuarios.push_back(new Professor(4, "Valter"));
    usuarios.push_back(new Professor(5, "Backes"));
    usuarios.push_back(new Aluno(6, "Aluno Em Debito", StatusUsuario::EM_DEBITO));
    usuarios.push_back(new Professor(7, "Professor Em Debito", StatusUsuario::EM_DEBITO));
    usuarios.push_back(new Pesquisador(8, "Pedro"));
}

int GerenciadorDeUsuarios::ProximoCodigo() {

    int maiorCodigo = 0;

    for (auto usuario : usuarios) {

        if (usuario->getCodigo() > maiorCodigo) {
            maiorCodigo = usuario->getCodigo();
        }
    }

    return maiorCodigo + 1;
}

void GerenciadorDeUsuarios::cadastrarUsuario() {
    string nome;
    int tipo;

    cout << "--- Cadastro de Novo Usuario ---" << endl;
    cout << "Nome: "; getline(cin, nome);
    cout << "Tipo (1-Aluno, 2-Professor, 3-Pesquisador): "; cin >> tipo;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    int novoCodigo = ProximoCodigo();
    Usuario* novoUsuario = nullptr;

    if (tipo == 1) {
        novoUsuario = new Aluno(novoCodigo, nome);
    } else if (tipo == 2) {
        novoUsuario = new Professor(novoCodigo, nome);
    } else if (tipo == 3) {
        novoUsuario = new Pesquisador(novoCodigo, nome);
    } else {
        proximoCodigoUsuario--; // Reverte o incremento do código se a operação falhar
        throw ErroTipoUsuarioInvalido();
    }

    usuarios.push_back(novoUsuario);
    cout << "Usuario '" << nome << "' cadastrado com sucesso! (Codigo: " << novoCodigo << ")" << endl;
}


void GerenciadorDeUsuarios::removerUsuario(const GerenciadorDeEmprestimos& gerenciadorEmprestimos) {
    cout << "--- Remocao de Usuario ---" << endl;
    cout << "Digite o codigo do usuario a ser removido: ";
    int codigo;
    cin >> codigo;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    Usuario* usuario = buscarUsuarioPorCodigo(codigo);
    if (!usuario) {
        throw ErroUsuarioNaoExiste();
    }

    // REGRA DE NEGÓCIO: Não remover usuário com pendências.
    if (gerenciadorEmprestimos.usuarioTemPendencias(usuario)) {
        throw ErroUsuarioComPendencias();
    }

    char confirmacao;
    cout << "Tem certeza que deseja remover o usuario '" << usuario->getNome() << "' (Codigo: " << codigo << ")? (S/N): ";
    cin >> confirmacao;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (toupper(confirmacao) == 'S') {
        for (auto it = usuarios.begin(); it != usuarios.end(); ++it) {
            if ((*it)->getCodigo() == codigo) {
                delete *it;
                usuarios.erase(it);
                cout << "Usuario removido com sucesso." << endl;
                return;
            }
        }
    } else {
        cout << "Remocao cancelada." << endl;
    }
}


Usuario* GerenciadorDeUsuarios::buscarUsuarioPorCodigo(int buscaCodigo) {
    for (auto temp : usuarios) {
        if (temp->getCodigo() == buscaCodigo) return temp;
    }
    throw ErroUsuarioNaoExiste();
}