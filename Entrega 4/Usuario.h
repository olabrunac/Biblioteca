#ifndef USUARIO_H
#define USUARIO_H

#include "StatusUsuario.h"

#include <string>
using std::string;


class Usuario {
    protected:
        int codigo;
        string nome;
        StatusUsuario status;

    public:
        Usuario();
        // Destrutor virtual para garantir que o destrutor da classe derivada (Aluno/Professor) seja chamado corretamente.
        virtual ~Usuario();
        Usuario(int novoCodigo, string novoNome, StatusUsuario novoStatus = StatusUsuario::HABILITADO);
        // Método virtual puro (abstrato) para polimorfismo. Força as classes filhas a implementarem sua própria versão.
        virtual void imprimirUsuario() const = 0;

        int getCodigo() const;
        string getNome() const;
        StatusUsuario getStatus()const;

        void setCodigo(int novoCodigo);
        void setNome(string novoNome);
        void setStatus(StatusUsuario novoStatus);
};

#endif