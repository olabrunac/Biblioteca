#include "Biblioteca.h"
#include <iostream>
using namespace std;

Livro::Livro(string titulo, string autor, int id, string editora, int anoPublicacao, string genero, bool disponivel){
    this->titulo = titulo;
    this->autor = autor;
    this->id = id;
    this->editora = editora;
    this->anoPublicacao = anoPublicacao;
    this->genero = genero;
    this->disponivel = disponivel;
}

void Livro::imprimir(){
    cout << "Título: " << this->titulo << endl;
    cout << "Autor: " << this->autor << endl;
    cout << "ID: " << this->id << endl;
    cout << "Editora: " << this->editora << endl;
    cout << "Ano: " << this->anoPublicacao << endl;
    cout << "Gênero: " << this->genero << endl;
    cout << "Disponível: " << (this->disponivel ? "Sim" : "Não") << endl;
}

string Livro::getTitulo(){ return this->titulo; }
string Livro::getAutor(){ return this->autor; }
int Livro::getId(){ return this->id; }
string Livro::getEditora(){ return this->editora; }
int Livro::getAnoPublicacao(){ return this->anoPublicacao; }
string Livro::getGenero(){ return this->genero; }

void Livro::setDisponibilidade(bool disponivel){
    this->disponivel = disponivel;
}
bool Livro::taDisponivel(){
    return this->disponivel;
}

    


/*
Usuario::Usuario(string nome, int id){
    this->nome = nome;
    this->id = id;
}


void Usuario::imprimir(){
    cout << "Nome: "<< this->nome<<endl;
    cout<<"ID: "<<this->id<<endl;

}

string Usuario::getNome(){return this->nome; }
int Usuario::getId(){return this->id; }
*/