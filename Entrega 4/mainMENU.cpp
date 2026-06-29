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
};


// https://docs.google.com/spreadsheets/u/2/d/e/2PACX-1vSPL6P46-GgutUZDF2t3kon_SIr0xOYO2Kf4SJz4oCtQm06wjtniDFAXQ1xnsLkvAzNsAiaxoDCroIv/pubhtml para visualisar o que foi carregado no sistema