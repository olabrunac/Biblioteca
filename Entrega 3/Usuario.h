#ifndef USUARIO_H
#define USUARIO_H

#include "StatusUsuario.h"

#include <string>
using std::string;


class Usuario {
    protected:  //pra permitir a herança
        int codigo;
        string nome;
        StatusUsuario status;

    public:
        Usuario();
        virtual ~Usuario();   // Destrutor virtual
        virtual void imprimirUsuario() const = 0;  //

        int getCodigo() const;
        string getNome() const;
        StatusUsuario getStatus()const;

        void setCodigo(int novoCodigo);
        void setNome(string novoNome);
        void setStatus(StatusUsuario novoStatus);
};

#endif