#include "GerenciadorDeUsuarios.h"
#include "Aluno.h"
#include "Professor.h"
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
    proximoCodigoUsuario = 6;
}

void GerenciadorDeUsuarios::cadastrarUsuario() {
    string nome;
    int tipo;

    cout << "--- Cadastro de Novo Usuario ---" << endl;
    cout << "Nome: "; getline(cin, nome);
    cout << "Tipo (1-Aluno, 2-Professor): "; cin >> tipo;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    int novoCodigo = proximoCodigoUsuario++;
    Usuario* novoUsuario = nullptr;

    if (tipo == 1) {
        novoUsuario = new Aluno(novoCodigo, nome);
    } else if (tipo == 2) {
        novoUsuario = new Professor(novoCodigo, nome);
    } else {
        cout << "Erro: Tipo de usuario invalido." << endl;
        proximoCodigoUsuario--; // Reverte o incremento do código se a operação falhar
        return;
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
        cout << "Erro: Usuario com codigo " << codigo << " nao encontrado." << endl;
        return;
    }

    // REGRA DE NEGÓCIO: Não remover usuário com pendências.
    if (gerenciadorEmprestimos.usuarioTemPendencias(usuario)) {
        cout << "ERRO: Usuario '" << usuario->getNome() << "' nao pode ser removido pois possui emprestimos ou reservas ativas." << endl;
        return;
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
    return nullptr;
}