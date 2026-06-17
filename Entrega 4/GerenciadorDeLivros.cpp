#include "GerenciadorDeLivros.h"
#include "Endereco.h"
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
    Endereco endRocco("Rua Julio Diniz", 56, "Vila Olimpia", "São Paulo", "SP", "04547-090");
    Endereco endPanini("Alameda Caiapos", 425, "Barueri", "Sao Paulo", "SP", "06460-110");
    editoras.push_back(new Editora(0, "Rocco", endRocco));
    editoras.push_back(new Editora(1, "Panini", endPanini));
    proximoCodigoEditora = 2;

    // ---- AUTORES ----
    autores.push_back(new Autor(0, "Suzanne Collins"));
    autores.push_back(new Autor(1, "Walter Tevis"));
    autores.push_back(new Autor(2, "Mauricio de Souza"));
    proximoCodigoAutor = 3;

    // ---- LIVROS ----
    Livro* l1 = new Livro(201, "Jogos Vorazes", *editoras[0], vector<Autor*> {autores[0]}, 2);
    l1->setNroDiasPermitidoEmprestimo(2);
    acervo.acrescentarLivro(l1);

    Livro* l2 = new Livro(202, "O Gambito da Rainha", *editoras[0], vector<Autor*> {autores[1], autores[2]}, 1);
    l2->setNroDiasPermitidoEmprestimo(2);
    acervo.acrescentarLivro(l2);

    Livro* l3 = new Livro(203, "Turma da Monica", 3, 4.99f, *editoras[1], 2021, 4, 7, vector<Autor*> {autores[2]}, 132);
    acervo.acrescentarLivro(l3);

    Livro* l4 = new Livro(204, "Em Chamas", 1, 59.90f, *editoras[0], 2023, 3, 7, vector<Autor*> {autores[0]}, 400);
    acervo.acrescentarLivro(l4);

    Livro* l5 = new Livro(205, "O Homem Que Caiu na Terra", 0, 49.90f, *editoras[1], 1963, 0, 7, vector<Autor*> { autores[1] }, 256);
    acervo.acrescentarLivro(l5);

    proximoCodigoLivro = 206;
}

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
        cout << "Erro: Editora '" << nomeEditora << "' nao encontrada. Cadastre-a primeiro." << endl;
        return;
    }
    if (!autor) {
        cout << "Erro: Autor '" << nomeAutor << "' nao encontrado. Cadastre-o primeiro." << endl;
        return;
    }

    int novoCodigo = proximoCodigoLivro++;
    Livro* novoLivro = new Livro(novoCodigo, titulo, *editora, {autor}, qtd);
    novoLivro->setNroDiasPermitidoEmprestimo(dias);
    acervo.acrescentarLivro(novoLivro);

    cout << "Livro '" << titulo << "' cadastrado com sucesso! (Codigo: " << novoCodigo << ")" << endl;
}

void GerenciadorDeLivros::removerLivro(const GerenciadorDeEmprestimos& gerenciadorEmprestimos) {
    cout << "--- Remocao de Livro ---" << endl;
    cout << "Como deseja buscar o livro a ser removido?" << endl;
    cout << "1. Pelo Codigo" << endl;
    cout << "2. Pelo Titulo" << endl;
    cout << "Escolha uma opcao: ";
    int opcao;
    cin >> opcao;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    Livro* livro = nullptr;

    if (opcao == 1) {
        int codigo;
        cout << "Digite o codigo do livro: ";
        cin >> codigo;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        livro = buscarLivroPorCodigo(codigo);
    } else if (opcao == 2) {
        string titulo;
        cout << "Digite o titulo do livro: ";
        getline(cin, titulo);
        livro = buscarLivroPorNome(titulo);
    } else {
        cout << "Opcao invalida." << endl;
        return;
    }

    if (!livro) {
        cout << "Erro: Livro nao encontrado." << endl;
        return;
    }

    if (gerenciadorEmprestimos.contarEmprestimosAtivos(*livro) > 0 || gerenciadorEmprestimos.contarReservasAtivas(*livro) > 0) {
        cout << "ERRO: Livro nao pode ser removido pois possui emprestimos ou reservas ativas." << endl;
        return;
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

void GerenciadorDeLivros::cadastrarAutor() {
    string nome;
    cout << "--- Cadastro de Novo Autor ---" << endl;
    cout << "Nome: "; getline(cin, nome);

    int novoCodigo = proximoCodigoAutor++;
    Autor* novoAutor = new Autor(novoCodigo, nome);
    autores.push_back(novoAutor);

    cout << "Autor '" << nome << "' cadastrado com sucesso! (Codigo: " << novoCodigo << ")" << endl;
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
                cout << "ERRO: Autor nao pode ser removido pois esta associado ao livro '" << livro->getTitulo() << "'." << endl;
                return;
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
    cout << "Erro: Autor com codigo " << codigo << " nao encontrado." << endl;
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

void GerenciadorDeLivros::removerEditora() {
    cout << "--- Remocao de Editora ---" << endl;
    cout << "Digite o codigo da editora a ser removida: ";
    int codigo;
    cin >> codigo;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    for (const auto& livro : acervo.getLivros()) {
        if (livro->getEditora().getCodigo() == codigo) {
            cout << "ERRO: Editora nao pode ser removida pois esta associada ao livro '" << livro->getTitulo() << "'." << endl;
            return;
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
    cout << "Erro: Editora com codigo " << codigo << " nao encontrada." << endl;
}

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