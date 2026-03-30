#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H
#include <string>

using namespace std;

class Livro{
    private:
        string titulo;
        string autor;
        int id;
        bool disponivel;
        string editora;
        int anoPublicacao;
        string genero;
    public:
        Livro(string titulo, string autor, int id, string editora, int anoPublicacao, string genero, bool disponivel = true);
        void imprimir();
        string getTitulo();
        string getAutor();
        int getId();
        string getEditora();
        int getAnoPublicacao();
        string getGenero();
        void setDisponibilidade(bool disponivel);
        bool taDisponivel();

};

#endif







/* 
class Usuario{
    private:
        string nome;
        int id;
            
    public:
        Usuario(string nome, int id);
        void imprimir();
        string getNome();
        int getId();
 };





classe Livro (RF01)
    titulo
        titulo livro string
    autor
        pegar autor string
    id
        int identificador do livro

classe Usuario (RF02)
    nome
        nome usuario string
    id
        int identificador do usuario


classe ItemEmprestimo (RF04)
    livro
        Livro* livro

    quantidade
        int quantidade

classe Emprestimo (RF03, RF05)
    id
        int identificador do emprestimo
    usuario
        Usuario* usuario

    data
        string data


    itens (vector de ItemEmprestimo)

*/
