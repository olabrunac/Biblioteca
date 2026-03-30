#include "Biblioteca.h"
#include <iostream>
using namespace std;

int main(){
    // Instanciando dois livros de forma estatica
    Livro livro1("Dom Casmurro", "Machado de Assis", 1, "Garnier", 1899, "Romance");
    Livro livro2("O Cortico", "Aluisio Azevedo", 2, "Garnier", 1890, "Naturalismo");
    
    // Instanciando dois livros de forma dinamica
    Livro* livro3 = new Livro("Grande Sertao: Veredas", "Guimaraes Rosa", 3, "Jose Olympio", 1956, "Romance");
    Livro* livro4 = new Livro("Capitaes da Areia", "Jorge Amado", 4, "Jose Olympio", 1937, "Romance", false);

    // Exibindo dados dos livros estaticos
    cout << "=== Livros Estaticos ===" << endl << endl;
    livro1.imprimir();
    cout << endl;
    livro2.imprimir();

    // Exibindo dados dos livros dinamicos
    cout << endl << "=== Livros Dinamicos ===" << endl << endl;
    livro3->imprimir();
    cout << endl;
    livro4->imprimir();

    // Usando metodos assessores (getters)
    cout << endl << "=== Metodos Assessores ===" << endl << endl;
    cout << "Titulo: " << livro1.getTitulo() << endl;
    cout << "Autor: " << livro1.getAutor() << endl;
    cout << "ID: " << livro1.getId() << endl;
    cout << "Editora: " << livro1.getEditora() << endl;
    cout << "Ano: " << livro1.getAnoPublicacao() << endl;
    cout << "Genero: " << livro1.getGenero() << endl;
    cout << "Disponivel: " << livro1.taDisponivel() << endl;

    // Testando setDisponibilidade
    cout << endl << "=== Teste setDisponibilidade ===" << endl << endl;
    cout << "Livro 1 disponivel? " << livro1.taDisponivel() << endl;
    livro1.setDisponibilidade(false);
    cout << "Apos emprestimo: " << livro1.taDisponivel() << endl;

    // Liberando memoria dos livros dinamicos
    delete livro3;
    delete livro4;

    return 0;
}
