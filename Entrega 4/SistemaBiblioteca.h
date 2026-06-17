#ifndef SISTEMA_BIBLIOTECA_H
#define SISTEMA_BIBLIOTECA_H

#include "Data.h"
#include <string>

// Declarações antecipadas das classes de gerenciamento
class GerenciadorDeLivros;
class GerenciadorDeUsuarios;
class GerenciadorDeEmprestimos;

class SistemaBiblioteca {
private:
    // Referências para os gerenciadores que contêm a lógica e os dados
    GerenciadorDeLivros& gerenciadorLivros;
    GerenciadorDeUsuarios& gerenciadorUsuarios;
    GerenciadorDeEmprestimos& gerenciadorEmprestimos;
    Data dataAtual;

    // Métodos de UI para os diferentes menus
    void mostrarMenuPrincipal();
    void menuCadastros();
    void menuEmprestimosEReservas();
    void menuConsultas();

public:
    // O construtor agora recebe referências para os gerenciadores
    SistemaBiblioteca(GerenciadorDeLivros& gl, GerenciadorDeUsuarios& gu, GerenciadorDeEmprestimos& ge);
    ~SistemaBiblioteca();
    void executar();
};

#endif // SISTEMA_BIBLIOTECA_H
