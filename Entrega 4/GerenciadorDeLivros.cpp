#include "GerenciadorDeLivros.h"
#include "Endereco.h"
#include "GerenciadorDeEmprestimos.h"
#include "Erros.h"
#include <iostream>
#include <limits>
#include <cctype>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;


GerenciadorDeLivros::GerenciadorDeLivros() : proximoCodigoLivro(0), proximoCodigoAutor(0), proximoCodigoEditora(0) {}


GerenciadorDeLivros::~GerenciadorDeLivros() {
    // O acervo já cuida de deletar os livros
    for (auto temp : autores) {
        delete temp;
    }
    autores.clear();

    for (auto temp : editoras) {
        delete temp;
    }
    editoras.clear();
}


void GerenciadorDeLivros::inicializarDados() {
    // ---- EDITORAS ----
    Endereco endEditora("Rua nao sei oq", 123, "Bairro tal", "Cidade etc", "Estado solido", "cep-123");
    Endereco endRocco("Rua Julio Diniz", 56, "Vila Olimpia", "São Paulo", "SP", "04547-090");
    Endereco endPanini("Alameda Caiapos", 425, "Barueri", "Sao Paulo", "SP", "06460-110");
    editoras.push_back(new Editora(1, "Editora", endEditora));
    editoras.push_back(new Editora(2, "Rocco", endRocco));
    editoras.push_back(new Editora(3, "Panini", endPanini));
    proximoCodigoEditora = 4;

    // ---- AUTORES ----
    autores.push_back(new Autor(1, "Autor"));
    autores.push_back(new Autor(2, "Suzanne Collins"));
    autores.push_back(new Autor(3, "Walter Tevis"));
    autores.push_back(new Autor(4, "Mauricio de Souza"));
    proximoCodigoAutor = 5;

    // ---- LIVROS ---- (codigo, titulo, editora, autores, exemplares, dias permitidos, ano, paginas)
    Livro* l1 = new Livro(201, "Livro", *editoras[0], vector<Autor*> {autores[1]}, 2);
    l1->setNroDiasPermitidoEmprestimo(7);
    acervo.acrescentarLivro(l1);

    Livro* l2 = new Livro(202, "Jogos Vorazes", *editoras[0], vector<Autor*> {autores[2], autores[4]}, 2, 7, 2018, 323);
    acervo.acrescentarLivro(l2);

    Livro* l3 = new Livro(203, "Turma da Monica", *editoras[1], vector<Autor*> {autores[4]}, 3, 7, 2002, 132);
    acervo.acrescentarLivro(l3);

    Livro* l4 = new Livro(204, "Em Chamas", *editoras[0], vector<Autor*> {autores[3]}, 1, 7, 2013, 400);
    acervo.acrescentarLivro(l4);

    Livro* l5 = new Livro(205, "Sem Exemplar", *editoras[1], vector<Autor*> { autores[1] }, 0, 7, 2026, 123); //para testar emprestimo sem exemplar disponivel
    acervo.acrescentarLivro(l5);

    Livro* l6 = new Livro(206, "Sem Dias", *editoras[0], vector<Autor*> {autores[1]}, 1, 0, 2026, 123); //para testar livro que o limite de dias é 0
    acervo.acrescentarLivro(l6);

    proximoCodigoLivro = 207;


}


//-------------------- cadastra e remove --------------------


void GerenciadorDeLivros::cadastrarLivro() {
    int qtd, dias;
    string titulo, nomeEditora, nomeAutor;
    
    cout << "--- Cadastro de Novo Livro ---" << endl;
    cout << "Titulo: "; getline(cin, titulo);
    cout << "Nome da Editora: "; getline(cin, nomeEditora);
    cout << "Nome do Autor: "; getline(cin, nomeAutor);
    cout << "Quantidade de exemplares: "; cin >> qtd;
    cout << "Dias para emprestimo: "; cin >> dias;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    Editora* editora = buscarEditoraPorNome(nomeEditora);
    Autor* autor = buscarAutorPorNome(nomeAutor);

    if (!editora) {
        throw ErroEditoraNaoExiste();
    }
    if (!autor) {
        throw ErroAutorNaoExiste();
    }

    int novoCodigo = proximoCodigoLivro++;
    Livro* novoLivro = new Livro(novoCodigo, titulo, *editora, {autor}, qtd);
    novoLivro->setNroDiasPermitidoEmprestimo(dias);
    acervo.acrescentarLivro(novoLivro);

    cout << "Livro '" << titulo << "' cadastrado com sucesso! (Codigo: " << novoCodigo << ")" << endl;
}


void GerenciadorDeLivros::cadastrarAutor() {
    string nome;
    cout << "--- Cadastro de Novo Autor ---" << endl;
    cout << "Nome: "; getline(cin, nome);

    int novoCodigo = proximoCodigoAutor++;
    Autor* novoAutor = new Autor(novoCodigo, nome);
    autores.push_back(novoAutor);

    cout << "Autor '" << nome << "' cadastrado com sucesso! (Codigo: " << novoCodigo << ")" << endl;
}


void GerenciadorDeLivros::cadastrarEditora() {
    string nome, rua, bairro, cidade, estado, cep;
    int numero;

    cout << "--- Cadastro de Nova Editora ---" << endl;
    cout << "Nome: "; getline(cin, nome);
    cout << "--- Endereco ---" << endl;
    cout << "Rua: "; getline(cin, rua);
    cout << "Numero: "; cin >> numero; cin.ignore();
    cout << "Bairro: "; getline(cin, bairro);
    cout << "Cidade: "; getline(cin, cidade);
    cout << "Estado (sigla): "; getline(cin, estado);
    cout << "CEP: "; getline(cin, cep);

    int novoCodigo = proximoCodigoEditora++;
    Endereco novoEndereco(rua, numero, bairro, cidade, estado, cep);
    Editora* novaEditora = new Editora(novoCodigo, nome, novoEndereco);
    editoras.push_back(novaEditora);

    cout << "Editora '" << nome << "' cadastrada com sucesso! (Codigo: " << novoCodigo << ")" << endl;
}


void GerenciadorDeLivros::removerLivro(const GerenciadorDeEmprestimos& gerenciadorEmprestimos) {
    cout << "--- Remocao de Livro ---" << endl;
    int opcao;
    do {
        cout << "\nComo deseja buscar o livro a ser removido?" << endl;
        cout << "1. Pelo Codigo" << endl;
        cout << "2. Pelo Titulo" << endl;
        cout << "0. Voltar" << endl;
        cout << "Escolha uma opcao: ";
        cin >> opcao;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cerr << "[ErroOpcaoInvalida]: A opcao digitada eh invalida. Por favor, insira um numero." << endl;
            opcao = -1; // Força a repetição do loop
        } else if (opcao < 0 || opcao > 2) {
            cerr << "[ErroOpcaoInvalida]: Opcao nao existe. Tente novamente." << endl;
        }
    } while (opcao < 0 || opcao > 2);

    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (opcao == 0) return;
    Livro* livro = nullptr;

    if (opcao == 1) {
        int codigo;
        cout << "Digite o codigo do livro: ";
        cin >> codigo;
        livro = buscarLivroPorCodigo(codigo);
    } else if (opcao == 2) {
        string titulo;
        cout << "Digite o titulo do livro: ";
        getline(cin, titulo);
        livro = buscarLivroPorNome(titulo);
    }

    if (!livro) {
        throw ErroLivroNaoExisteAcervo();
    }

    if (gerenciadorEmprestimos.contarEmprestimosAtivos(*livro) > 0 || gerenciadorEmprestimos.contarReservasAtivas(*livro) > 0) {
        throw ErroLivroEmUso();
    }

    char confirmacao;
    cout << "Tem certeza que deseja remover o livro '" << livro->getTitulo() << "' (Codigo: " << livro->getCodigo() << ")? (S/N): ";
    cin >> confirmacao;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (toupper(confirmacao) == 'S') {
        acervo.removerDoAcervo(livro);
    } else {
        cout << "Remocao cancelada." << endl;
    }
}


void GerenciadorDeLivros::removerAutor() {
    cout << "--- Remocao de Autor ---" << endl;
    cout << "Digite o codigo do autor a ser removido: ";
    int codigo;
    cin >> codigo;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    for (const auto& livro : acervo.getLivros()) {
        for (const auto& autorDoLivro : livro->getAutor()) {
            if (autorDoLivro->getCodigo() == codigo) {
                throw ErroAutorAssociado();
            }
        }
    }

    for (auto it = autores.begin(); it != autores.end(); ++it) {
        if ((*it)->getCodigo() == codigo) {
            cout << "Autor '" << (*it)->getNome() << "' removido com sucesso." << endl;
            delete *it;
            autores.erase(it);
            return;
        }
    }
    throw ErroAutorNaoExiste();
}


void GerenciadorDeLivros::removerEditora() {
    cout << "--- Remocao de Editora ---" << endl;
    cout << "Digite o codigo da editora a ser removida: ";
    int codigo;
    cin >> codigo;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    for (const auto& livro : acervo.getLivros()) {
        if (livro->getEditora().getCodigo() == codigo) {
            throw ErroEditoraAssociada();
        }
    }

    for (auto it = editoras.begin(); it != editoras.end(); ++it) {
        if ((*it)->getCodigo() == codigo) {
            cout << "Editora '" << (*it)->getNome() << "' removida com sucesso." << endl;
            delete *it;
            editoras.erase(it);
            return;
        }
    }
    throw ErroEditoraNaoExiste();
}


//-------------------- buscas --------------------


Livro* GerenciadorDeLivros::buscarLivroPorCodigo(int codigo) {
    for (auto temp : acervo.getLivros()) {
        if (temp->getCodigo() == codigo) return temp;
    }
    return nullptr;
}


Livro* GerenciadorDeLivros::buscarLivroPorNome(const std::string& nome) {
    for (auto temp : acervo.getLivros()) {
        if (temp->getTitulo() == nome) return temp;
    }
    return nullptr;
}


Autor* GerenciadorDeLivros::buscarAutorPorNome(const std::string& nome) {
    for (auto temp : autores) {
        if (temp->getNome() == nome) return temp;
    }
    return nullptr;
}


Editora* GerenciadorDeLivros::buscarEditoraPorNome(const std::string& nome) {
    for (auto temp : editoras) {
        if (temp->getNome() == nome) return temp;
    }
    return nullptr;
}


Acervo& GerenciadorDeLivros::getAcervo() { return acervo; }