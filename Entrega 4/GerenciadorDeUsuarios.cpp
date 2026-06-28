#include "GerenciadorDeUsuarios.h"
#include "Aluno.h"
#include "Professor.h"
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


void GerenciadorDeUsuarios::setUsuarios(const std::vector<Usuario*>& novosUsuarios) {
    this->usuarios = novosUsuarios;
    if (!novosUsuarios.empty()) {
        proximoCodigoUsuario = novosUsuarios.back()->getCodigo() + 1;
    }
}


void GerenciadorDeUsuarios::cadastrarUsuario() {
    string nome;
    int tipo;

    cout << "--- Cadastro de Novo Usuario ---" << endl;
    cout << "Nome: "; getline(cin, nome);

    // Verifica se o usuário já existe
    for (const auto& usuario : usuarios) {
        if (usuario->getNome() == nome) {
            throw ErroUsuarioJaExiste(nome);
        }
    }

    cout << "Tipo (1-Aluno, 2-Professor): "; cin >> tipo;
    limparBufferEntrada();

    int novoCodigo = proximoCodigoUsuario++;
    Usuario* novoUsuario = nullptr;

    if (tipo == 1) {
        novoUsuario = new Aluno(novoCodigo, nome);
    } else if (tipo == 2) {
        novoUsuario = new Professor(novoCodigo, nome);
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
    limparBufferEntrada();

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
    limparBufferEntrada();

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