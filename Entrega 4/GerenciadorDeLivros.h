#ifndef GERENCIADOR_DE_LIVROS_H
#define GERENCIADOR_DE_LIVROS_H

#include "Acervo.h"
#include "Autor.h"
#include "Editora.h"
#include "GerenciadorDeEmprestimos.h"
#include <vector>
#include <string>

class GerenciadorDeLivros {
private:
    Acervo acervo;
    std::vector<Autor*> autores;
    std::vector<Editora*> editoras;

    int proximoCodigoLivro;
    int proximoCodigoAutor;
    int proximoCodigoEditora;

public:
    GerenciadorDeLivros();
    ~GerenciadorDeLivros();

    void inicializarDados();

    void cadastrarLivro();
    void removerLivro(const GerenciadorDeEmprestimos& gerenciadorEmprestimos);
    void cadastrarAutor();
    void removerAutor();
    void cadastrarEditora();
    void removerEditora();

    Livro* buscarLivroPorCodigo(int codigo);
    Livro* buscarLivroPorNome(const std::string& nome);
    Autor* buscarAutorPorNome(const std::string& nome);
    Editora* buscarEditoraPorNome(const std::string& nome);

    Acervo& getAcervo();
};

#endif