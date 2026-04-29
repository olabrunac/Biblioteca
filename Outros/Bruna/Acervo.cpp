#include "Acervo.h"
#include "Livro.h"
#include <iostream>

using std::cout;
using std::endl;
using std::iterator;

Acervo::Acervo() {}

void Acervo::acrescentarLivro(const Livro& novoLivro) { acervo.push_back(novoLivro); }  // Cadastra um novo livro no fim do vetor acervo

void Acervo::removerDoAcervo(const Livro& removerLivro) {                               // recebe o const livro& que será removido por referencia constante, evita copiar o objeto inteiro na memória
    cout << " <<<<< REMOVENDO O LIVRO >>>>> " << endl;
    for (vector<Livro>::const_iterator temp = acervo.cbegin(); temp != acervo.cend(); temp ++){ // iterador constante aponta para os elementos do vetor, começa no primeiro elemento graças ao acervo.cbegin() e percorre temp++ até o acervo.cend()
        if(temp->getCodigo() == removerLivro.getCodigo()){                              // compara o código de cada livro do acervo com o código que vai ser removido
            acervo.erase(temp);                                                         // deleta se achar
            cout << "Livro removido com sucesso" << endl;
            return;
        }
    }
    cout <<"Livro nao encontrado" << endl;
}

void Acervo::listarTodos() const {                                                      // Metodo listar, o 'const' aqui avisa ao compilador que este metodo nao vai modificar nenhum atributo da classe Acervo
    cout << "----- TODOS OS LIVROS -----" << endl;
    for (const Livro& temp: acervo) {                                                   // temporariamente coloca cada item do acervo no temp e executa o código dentro do for
        cout << temp.getTitulo() << ", "                                                // & (referencia) impede que o programa crie cópia do livro na memória em toda volta do laço
        << temp.getStatusAgora() << endl;
    }
}

void Acervo::listarLivrosDisponiveis() const {                                          // Outra funcao de visualizacao ('const'), focada nos disponiveis
    cout << "+++++ TODOS OS LIVROS DISPONIVEIS +++++" << endl;
    for (const Livro& temp: acervo) {                                                   // Utiliza 'range-based for' (for que varre todas as iteracoes do vetor automaticamente sem indice numerico)
        if (temp.estaDisponivel()) {                                                    // Valida usando a funcao interna da classe Livro
            cout << "Titulo: " << temp.getTitulo() << " | Codigo: " << temp.getCodigo() << endl; // Havendo disponibilidade, imprime formatado
        }
    }
}

void Acervo::listarLivrosIndisponiveis() const {                                        // Funcao parecida para imprimir os indisponiveis
    cout << "----- TODOS OS LIVROS INDISPONIVEIS -----" << endl;
    for (const Livro& temp : acervo ) {                                                 // De novo o for sobre os livros do acervo 
        if (!temp.estaDisponivel()) {                                                    // !temp inverte o resultado obtido pelo estádisponivel, nesse caso se um livro está indisponivel vai retornar true e entrar no if
            cout << "Titulo: " << temp.getTitulo() << " | Codigo: " << temp.getCodigo() << endl; // Imprime dados do indisponivel
        }
    }
}