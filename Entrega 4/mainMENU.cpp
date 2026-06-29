#include <iostream>
#include "SistemaBiblioteca.h"
#include "Inicializador.h"
#include "GerenciadorDeLivros.h"
#include "GerenciadorDeUsuarios.h"
#include "GerenciadorDeEmprestimos.h"

using std::cout;
using std::endl;
using std::vector;

int main() {

    GerenciadorDeLivros gerenciadorLivros;
    GerenciadorDeUsuarios gerenciadorUsuarios;
    GerenciadorDeEmprestimos gerenciadorEmprestimos;


    SistemaBiblioteca sistema(gerenciadorLivros, gerenciadorUsuarios, gerenciadorEmprestimos);


    vector<Usuario*> usuariosIniciais = Inicializador<Usuario>::carregar();
    vector<Autor*> autoresIniciais = Inicializador<Autor>::carregar();
    vector<Editora*> editorasIniciais = Inicializador<Editora>::carregar();
    vector<Livro*> livrosIniciais = Inicializador<Livro>::carregar(autoresIniciais, editorasIniciais);
    vector<Emprestimo*> emprestimosIniciais = Inicializador<Emprestimo>::carregar(usuariosIniciais, livrosIniciais);


    gerenciadorUsuarios.setUsuarios(usuariosIniciais);
    gerenciadorLivros.setAutores(autoresIniciais);
    gerenciadorLivros.setEditoras(editorasIniciais);
    gerenciadorLivros.setLivros(livrosIniciais);
    gerenciadorEmprestimos.setEmprestimos(emprestimosIniciais);

    sistema.executar();

    return 0; 
}