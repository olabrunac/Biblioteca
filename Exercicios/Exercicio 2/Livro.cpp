#include "Livro.h"



// Construtor
    Livro::Livro(string t, string a, int i): titulo(t), autor(a), id(i) {}
    Livro::Livro() {}

// Exibir dados do livro
    void Livro::imprimir() {
        cout << "Titulo: " << titulo << ", Autor: " << autor << ", ID: " << id << endl;
    }
// Exibir dados do livro e editora
    void Livro::exibirDados() {
        cout << "Titulo: " << titulo << endl;
        editora.imprimirEditora();
        cout << endl;
    }


// Definindo set e get do Titulo
    void Livro::setTitulo(string t) { this-> titulo = t; }
    string Livro::getTitulo() { return titulo; }

// Definindo set e get do Autor
    void Livro::setAutor(string autor) { this-> autor = autor; }
    string Livro::getAutor() { return autor; }

// Definindo set e get do ID
    void Livro::setID(int id) { this-> id = id; }
    int Livro::getID() { return id; }

// Definindo set e get da editora
    void Livro::setEditora(Editora& editora) { this -> editora = editora; }
    Editora Livro::getEditora() { return this -> editora; }
