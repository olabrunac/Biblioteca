#ifndef INICIALIZADOR_H
#define INICIALIZADOR_H

#include <vector>
#include "Usuario.h"
#include "Aluno.h"
#include "Professor.h"
#include "Autor.h"
#include "Editora.h"
#include "Endereco.h"
#include "Livro.h"
#include "Emprestimo.h"


template <typename T>
class Inicializador {
public:
    static std::vector<T*> carregar();

    // Sobrecarga para tipos que dependem de Autores e Editoras
    static std::vector<T*> carregar(const std::vector<Autor*>& autores, const std::vector<Editora*>& editoras);

    // Sobrecarga para Emprestimo, que depende de Usuarios e Livros
    static std::vector<T*> carregar(const std::vector<Usuario*>& usuarios, const std::vector<Livro*>& livros);
};

// --- Inicialização de usuario ---
template <>
inline std::vector<Usuario*> Inicializador<Usuario>::carregar() {
    std::vector<Usuario*> usuarios;
    usuarios.push_back(new Aluno(1, "Matheus"));
    usuarios.push_back(new Aluno(2, "Bruna"));
    usuarios.push_back(new Aluno(3, "Ryan"));
    usuarios.push_back(new Professor(4, "Valter"));
    usuarios.push_back(new Professor(5, "Backes"));
    usuarios.push_back(new Aluno(6, "Aluno em debito", StatusUsuario::EM_DEBITO));
    usuarios.push_back(new Professor(7, "Professor em debito", StatusUsuario::EM_DEBITO));
    return usuarios;
}

// --- Inicialização de autor ---
template <>
inline std::vector<Autor*> Inicializador<Autor>::carregar() {
    std::vector<Autor*> autores;
    autores.push_back(new Autor(1, "Autor"));
    autores.push_back(new Autor(2, "Suzanne Collins"));
    autores.push_back(new Autor(3, "Walter Tevis"));
    autores.push_back(new Autor(4, "Mauricio de Souza"));
    return autores;
}

// --- Inicialização de editora ---
template <>
inline std::vector<Editora*> Inicializador<Editora>::carregar() {
    std::vector<Editora*> editoras;
    Endereco endEditora("Rua nao sei oq", 123, "Bairro tal", "Cidade etc", "Estado solido", "cep-123");
    Endereco endRocco("Rua Julio Diniz", 56, "Vila Olimpia", "São Paulo", "SP", "04547-090");
    Endereco endPanini("Alameda Caiapos", 425, "Barueri", "Sao Paulo", "SP", "06460-110");
    editoras.push_back(new Editora(1, "Editora", endEditora));
    editoras.push_back(new Editora(2, "Rocco", endRocco));
    editoras.push_back(new Editora(3, "Panini", endPanini));
    return editoras;
}

// --- Inicialização de livro ---
template <>
inline std::vector<Livro*> Inicializador<Livro>::carregar(const std::vector<Autor*>& autores, const std::vector<Editora*>& editoras) {
    std::vector<Livro*> livros;

    Livro* l1 = new Livro(201, "Livro", *editoras[0], {autores[1]}, 2);
    l1->setNroDiasPermitidoEmprestimo(7);
    livros.push_back(l1);
    
    Livro* l2 = new Livro(202, "Jogos Vorazes", *editoras[1], {autores[1]}, 2, 7, 2018, 323);
    livros.push_back(l2);

    Livro* l3 = new Livro(203, "Turma da Monica", *editoras[2], {autores[3]}, 3, 7, 2002, 132);
    livros.push_back(l3);

    Livro* l4 = new Livro(204, "Em Chamas", *editoras[1], {autores[2]}, 1, 7, 2013, 400);
    livros.push_back(l4);

    livros.push_back(new Livro(205, "Sem Exemplar", *editoras[2], {autores[0]}, 0, 7, 2026, 123));
    livros.push_back(new Livro(206, "Sem Dias", *editoras[0], {autores[1]}, 1, 0, 2026, 123));

    return livros;
}

// --- Inicialização de emprestimo ---
template <>
inline std::vector<Emprestimo*> Inicializador<Emprestimo>::carregar(const std::vector<Usuario*>& usuarios, const std::vector<Livro*>& livros) {
    std::vector<Emprestimo*> emprestimos;

    Data dataEmprestimo(1, 1, 2026); //data do emprestimo

    Usuario* usuario = usuarios[2];
    Livro* livro = livros[1];

    if (usuario && livro && livro->estaDisponivel()) {
        ExemplarLivro* exemplar = livro->getExemplarDisponivel();
        exemplar->setStatus(StatusEmprestimo::EMPRESTADO);

        ItemEmprestimo* item = new ItemEmprestimo();
        item->setExemplar(exemplar);
        item->setDataParaDevolucao(dataEmprestimo + livro->getNroDiasPermitidoEmprestimo());

        Emprestimo* emprestimo = new Emprestimo(usuario, dataEmprestimo, item->getDataParaDevolucao(), 0, 1);
        emprestimo->adicionarItem(item);
        emprestimos.push_back(emprestimo);
    }
    return emprestimos;
}

#endif // INICIALIZADOR_H
