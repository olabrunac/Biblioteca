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
        Usuario(int novoCodigo, string novoNome, StatusUsuario novoStatus = StatusUsuario::HABILITADO);
        virtual void imprimirUsuario() const;  

        int getCodigo() const;
        string getNome() const;
        StatusUsuario getStatus()const;

        void setCodigo(int novoCodigo);
        void setNome(string novoNome);
        void setStatus(StatusUsuario novoStatus);
};

#endif