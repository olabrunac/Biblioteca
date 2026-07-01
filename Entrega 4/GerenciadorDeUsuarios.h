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

    void cadastrarUsuario();
    int ProximoCodigo();
    void removerUsuario(const GerenciadorDeEmprestimos& gerenciadorEmprestimos);
    void setUsuarios(const std::vector<Usuario*>& novosUsuarios);
    Usuario* buscarUsuarioPorCodigo(int buscaCodigo);
    Usuario* buscarUsuarioPorNome(const std::string& nome);
    void listarTodosUsuarios() const;
};

#endif