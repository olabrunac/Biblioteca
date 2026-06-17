#ifndef GERENCIADOR_DE_USUARIOS_H
#define GERENCIADOR_DE_USUARIOS_H

#include "Usuario.h"
#include "GerenciadorDeEmprestimos.h"
#include <vector>
#include <string>

class GerenciadorDeUsuarios {
private:
    std::vector<Usuario*> usuarios;
    int proximoCodigoUsuario;

public:
    GerenciadorDeUsuarios();
    ~GerenciadorDeUsuarios();

    void inicializarDados();
    void cadastrarUsuario();
    void removerUsuario(const GerenciadorDeEmprestimos& gerenciadorEmprestimos);
    Usuario* buscarUsuarioPorCodigo(int buscaCodigo);
};

#endif