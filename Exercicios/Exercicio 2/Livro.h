#ifndef LIVRO_H
#define LIVRO_H
#include <iostream>
#include "Editora.h"
using namespace std;

class Livro {
    private:
    string titulo;
    string autor;
    int id;
    Editora editora;
    
    public:
    Livro(string t, string a, int i);
    Livro();
    void imprimir();
    void exibirDados();

    void setTitulo(string titulo);
    string getTitulo();
    void setAutor(string autor);
    string getAutor();
    void setID(int id);
    int getID();
    void setEditora(Editora& editora);
    Editora getEditora();
};

#endif