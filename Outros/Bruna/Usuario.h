#ifndef USUARIO_H
#define USUARIO_H

#include "StatusUsuario.h"

#include <string>
using std::string;


class Usuario {
    private:
        int codigo;
        string nome;
        StatusUsuario status;

    public:
        Usuario();
        void imprimirUsuario() const;

        int getCodigo() const;
        string getNome() const;
        StatusUsuario getStatus()const;

        void setCodigo(int novoCodigo);
        void setNome(string novoNome);
        void setStatus(StatusUsuario novoStatus);
};

#endif