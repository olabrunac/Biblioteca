#include <iostream>
#include "Livro.h"

int main() {

// Instanciando 2 enderecos estáticos
    Endereco endRocco("Rua Antonio Correa", 12, "Jardim Andorinha", "Americana", "SP", "12345-678");
    Endereco endAleph("Rua Brigadeiro Soares", 34, "Boa Vista", "Bauru", "SP", "13456-789");

// Instanciando 2 enderecos dinamicos


// Instanciando Editora
    Editora rocco(123, "Rocco", endRocco);
    Editora aleph(456, "Aleph", endAleph);


// ----------------------------------------------------------------------------------

// Instanciando dois livros na forma estática
    cout << "Forma estática livro 1 e livro 2: " << endl;
    Livro l1("Jogos Vorazes", "Suzanne Collins", 01);
    l1.imprimir();
    cout << endl << "Exibindo os dados da editora: " << endl;
    l1.setEditora(rocco);
    l1.exibirDados();

    Livro l2("Duna", "Frank Herbert", 02);
    l2.imprimir();
    cout << endl << "Exibindo os dados da editora: " << endl;
    l2.setEditora(aleph);
    l2.exibirDados();

// Instanciando dois livros na forma dinâmica
    cout << endl << "Forma dinâmica livro 3 e livro 4: " << endl;
    Livro* l3 = new Livro("O Pequeno Príncipe", "Antoine de Saint-Exupéry", 03);
    l3 -> imprimir();
    cout << endl << "Exibindo os dados da editora: " << endl;
    l3 -> setEditora(rocco);
    l3 -> exibirDados();

    Livro* l4 = new Livro("Dom Casmurro", "Machado de Assis", 04);
    l4 -> imprimir();
    cout << endl << "Exibindo os dados da editora: " << endl;
    l4 -> setEditora(aleph);
    l4 -> exibirDados();


// Usando métodos acessores (set e get)
    cout << endl << "Usando set e get para criar o livro 5" << endl;
    
    Livro l5;
    l5.setTitulo("Jantar Secreto");
    l5.setAutor("Raphael Montes");
    l5.setID(05);
    l5.setEditora(rocco);
    l5.imprimir();
    l5.getEditora().imprimirEditora();
  


// Finalização exibindo os dados
    cout << endl << "Exibição final:" << endl;
    l1.imprimir();
    l2.imprimir();
    l3 -> imprimir();
    delete l3;                    // liberando a memória
    l4 -> imprimir();
    delete l4;                    // liberando a memória
    cout << endl << endl;

// ---------------------------------------------------------------------


}