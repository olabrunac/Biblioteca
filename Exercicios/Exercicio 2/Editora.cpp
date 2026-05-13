#include "Editora.h"



// Construtor
    Editora::Editora(int c, string n, Endereco& end) : codigo(c), nome(n), endereco(end) {}
    Editora::Editora(int, string) {}
    Editora::Editora() {}

// Imprimir Editora
    void Editora::imprimirEditora() {
        cout << "Editora: " << nome << ", Código: " << codigo << endl;
        endereco.imprimirEndereco();
        cout << endl;
    }
// set e get Codigo
    void Editora::setCodigo(int codigo) { this -> codigo = codigo; }
    int Editora::getCodigo() { return codigo; }

// set e get Nome
    void Editora::setNome(string nome) { this -> nome = nome; }
    string Editora::getNome() { return nome; }

// set e get Endereco
    void Editora::setEndereco(Endereco& end) { this -> endereco = end; }
    Endereco Editora::getEndereco() { return this -> endereco; }