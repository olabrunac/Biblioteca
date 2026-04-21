#ifndef EDITORA_H
#define EDITORA_H

#include "Endereco.h"
#include <string>

using std::string;

class Editora {
    private:
        int codigo;
        string nome;
        Endereco endereco;

    public:
        Editora();
        void imprimirEditora();

        int getCodigo();
        string getNome();
        Endereco getEndereco();

        void setCodigo(int novoCodigo);
        void setNome(string novoNome);
        void setEndereco(Endereco& novoEndereco);

};

#endif