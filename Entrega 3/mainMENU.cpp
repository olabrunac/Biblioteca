#include <iostream>
#include "SistemaBiblioteca.h"
#include "GerenciadorDeLivros.h"
#include "GerenciadorDeUsuarios.h"
#include "GerenciadorDeEmprestimos.h"

using std::cout;
using std::endl;

int main() {
    // 1. Cria as instâncias dos gerenciadores
    GerenciadorDeLivros gerenciadorLivros;
    GerenciadorDeUsuarios gerenciadorUsuarios;
    GerenciadorDeEmprestimos gerenciadorEmprestimos;

    // 2. Inicializa com os dados de exemplo
    gerenciadorLivros.inicializarDados();
    gerenciadorUsuarios.inicializarDados();

    // 3. Cria a camada de UI, passando os gerenciadores para ela
    SistemaBiblioteca sistema(gerenciadorLivros, gerenciadorUsuarios, gerenciadorEmprestimos);
    sistema.executar();

    return 0; 
}