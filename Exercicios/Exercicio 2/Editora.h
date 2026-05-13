#ifndef EDITORA_H
#define EDITORA_H
#include <iostream>
#include "Endereco.h"
using namespace std;

class Editora {
    private:
    int codigo;
    string nome;
    Endereco endereco;

    public:
    Editora(int c, string n, Endereco& endereco);
    Editora(int,  string);
    Editora();
    void imprimirEditora();

    void setCodigo(int codigo);
    int getCodigo();
    void setNome(string nome);
    string getNome();
    void setEndereco(Endereco& endereco);
    Endereco getEndereco();
};


#endif