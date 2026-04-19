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

};

#endif