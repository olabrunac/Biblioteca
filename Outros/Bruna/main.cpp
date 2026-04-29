#include <iostream>
#include <vector>
#include "Acervo.h"
#include "GerenciadorDeEmprestimos.h"
//#include "Professor.h"
#include "Editora.h"
#include "Autor.h"

using std::cout;
using std::endl;
using std::vector;

int main() {

    cout << "===== INICIO DO SISTEMA =====" << endl;

    // ---------------- ENDERECO / EDITORA ----------------

    Endereco endRocco;                              // Instancia um objeto na stack local chamado endRocco do tipo Endereco
    endRocco.setRua("Av. Paulista");                // Invoca o setter passando a string da rua
    endRocco.setCidade("São Paulo");                // Invoca o setter passando a string da cidade

    Editora ediRocco;
    ediRocco.setNome("Rocco");
    ediRocco.setEndereco(endRocco);                 // Aplica a composicao: atrela o objeto 'endRocco' pra dentro do objeto 'ediRocco'

    // ---------------- AUTORES ----------------

    Autor suzanne;                                  // Instancia o objeto da escritora Suzanne
    suzanne.setCodigo(10);                          // Define o ID ficticio dela
    suzanne.setNome("Suzanne Collins");             // Preenche a propriedade String com seu respectivo nome

    vector<Autor> listaAutores;                     // Inicializa um vetor generico de Autores (preparando para livros com multiplos autores)
    listaAutores.push_back(suzanne);                // Adiciona a autora Suzanne na ultima posicao dessa lista

    cout << endl;
    cout << "===== AUTOR =====" << endl;
    suzanne.imprimirAutor();

    // ---------------- LIVROS ----------------

    Livro l1;                                       // Prepara um novo registro no catalogo instanciando Livro (l1)
    l1.setCodigo(111);                              // Configura ID do catalogo
    l1.setTitulo("Jogos Vorazes");                  // Configura nome do titulo
    l1.setEditora(ediRocco);                        // Vincula o objeto Editora Rocco ao Livro
    l1.setAutor(listaAutores);                      // Passa o Array dinamico contendo os escritores desse Livro
    l1.criarExemplares(2); // poucos exemplares para testar limite // Dispara a funcao interna do livro que cria copias "fisicas" alocadas em memoria com base na qtde

    Livro l2;                                       // Instancia o livro O Gambito da Rainha
    l2.setCodigo(123);                              // ID
    l2.setTitulo("O Gambito da Rainha");            // Nome
    l2.setEditora(ediRocco);                        // Vincula a mesma editora Rocco
    l2.setAutor(listaAutores);                      // Reaproveita a mesma lista de autores
    l2.criarExemplares(1); // apenas 1 exemplar     // Cria e armazena rigorosamente um unico exemplar fisico

    // ---------------- ACERVO ----------------

    Acervo biblioteca;                              // Prepara a entidade 'colecao' geral chamada biblioteca

    biblioteca.acrescentarLivro(l1);                // Empurra a entidade l1 recem configurada pra dentro da biblioteca
    biblioteca.acrescentarLivro(l2);                // Empurra a entidade l2 tambem

    cout << endl;
    cout << "===== LISTA DE LIVROS =====" << endl;
    biblioteca.listarTodos();                       // Dispara o 'const iterator' que vai passar titulo a titulo cadastrado no acervo imprimindo tudo

    // ---------------- USUARIOS ----------------

    Usuario Matheus;                                // Inicializa Matheus
    Matheus.setCodigo(1);                           // ID
    Matheus.setNome("Matheus");                     // String

    Usuario Bruna;
    Bruna.setCodigo(2);
    Bruna.setNome("Bruna");

    Usuario Ryan;
    Ryan.setCodigo(3);
    Ryan.setNome("Ryan");

    Usuario Ana;
    Ana.setCodigo(4);
    Ana.setNome("Ana");

    // ---------------- GERENCIADOR ----------------

    GerenciadorDeEmprestimos sistema;               // Cria o grande controlador de locacao do programa

    cout << endl;
    cout << "===== REALIZANDO EMPRESTIMOS =====" << endl;

    sistema.criarEmprestimo(Matheus, l1.getExemplarDisponivel()); // Puxa uma copia live de l1 usando a propria classe livro e passa pro sistema locar p/ Matheus
    sistema.criarEmprestimo(Bruna, l1.getExemplarDisponivel());   // Puxa a copia 2/2 livre de l1 e o sistema empresta com sucesso a Bruna

    // Deve falhar (exemplares esgotados)
    sistema.criarEmprestimo(Ryan, l1.getExemplarDisponivel());    // Metodo de get do livro tentara buscar exemplar disponivel e retornara 'nullptr' pois Matheus e Bruna levaram as duas copias

    sistema.criarEmprestimo(Ana, l2.getExemplarDisponivel());     // Puxa a copia livre 1/1 do livro l2 e loca para Ana

    // Deve falhar (apenas 1 exemplar)
    sistema.criarEmprestimo(Ryan, l2.getExemplarDisponivel());    // Vai falhar da mesma forma pois a funcao interna devolvera 'nullptr'

    // ---------------- LISTAGEM ----------------

    cout << endl;
    cout << "===== EMPRESTIMOS ATUAIS =====" << endl;

    sistema.listarTodosEmprestimosAtuais();         // Mostra na tela os registros emissores unindo usuario e livro devidamente logados

    cout << endl;
    cout << "===== FIM DO SISTEMA =====" << endl;

    
    system("pause");                                // Impede de o executavel CMD fechar abruptamente antes do usuario analisar (Comando de windows)
    return 0;                                       // Avisa ao SO que tudo ocorreu sem engasgos
}