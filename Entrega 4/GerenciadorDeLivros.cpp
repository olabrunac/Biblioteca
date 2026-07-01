#include "GerenciadorDeLivros.h"
#include "Endereco.h"
#include "GerenciadorDeEmprestimos.h"
#include "Inicializador.h"
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


void GerenciadorDeLivros::setAutores(const std::vector<Autor*>& novosAutores) {
    this->autores = novosAutores;
    // Calcula o próximo código de autor disponível
    if (!novosAutores.empty()) {
        proximoCodigoAutor = novosAutores.back()->getCodigo() + 1;
    }
}

void GerenciadorDeLivros::setEditoras(const std::vector<Editora*>& novasEditoras) {
    this->editoras = novasEditoras;
    // Calcula o próximo código de editora disponível
    if (!novasEditoras.empty()) {
        proximoCodigoEditora = novasEditoras.back()->getCodigo() + 1;
    }
}

void GerenciadorDeLivros::setLivros(const std::vector<Livro*>& novosLivros) {
    for (Livro* livro : novosLivros) {
        this->acervo.acrescentarLivro(livro);
    }
    // Calcula o próximo código de livro disponível
    if (!novosLivros.empty()) {
        proximoCodigoLivro = novosLivros.back()->getCodigo() + 1;
    }
}



//-------------------- cadastra e remove --------------------

void GerenciadorDeLivros::cadastrarLivro() {
    int qtd, dias;
    string titulo, nomeEditora, nomeAutor;
    
    cout << "--- Cadastro de Novo Livro ---" << endl;
    cout << "Titulo: "; getline(cin, titulo);

    // Verifica se o livro já existe
    if (buscarLivroPorNome(titulo) != nullptr) {
        throw ErroLivroJaExiste(titulo);
    }

    // insere editora e valida
    cout << "Nome da Editora: "; getline(cin, nomeEditora);
    Editora* editora = buscarEditoraPorNome(nomeEditora);
    if (!editora) {
        throw ErroEditoraNaoExiste();
    }

    // faz o msm com autor
    cout << "Nome do Autor: "; getline(cin, nomeAutor);
    Autor* autor = buscarAutorPorNome(nomeAutor);
    if (!autor) {
        throw ErroAutorNaoExiste();
    }

    cout << "Quantidade de exemplares: "; cin >> qtd;
    cout << "Dias para emprestimo: "; cin >> dias;
    limparBufferEntrada();

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

    // Verifica se o autor já existe
    if (buscarAutorPorNome(nome) != nullptr) {
        throw ErroAutorJaExiste(nome);
    }

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

    // Verifica se a editora já existe
    if (buscarEditoraPorNome(nome) != nullptr) {
        throw ErroEditoraJaExiste(nome);
    }

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
            limparBufferEntrada();
            cerr << "[ErroOpcaoInvalida]: A opcao digitada eh invalida. Por favor, insira um numero." << endl;
            opcao = -1; // Força a repetição do loop
        } else if (opcao < 0 || opcao > 2) {
            cerr << "[ErroOpcaoInvalida]: Opcao nao existe. Tente novamente." << endl;
        }
    } while (opcao < 0 || opcao > 2);

    limparBufferEntrada();

    if (opcao == 0) return;
    Livro* livro = nullptr;

    if (opcao == 1) {
        int codigo;
        cout << "Digite o codigo do livro: ";
        cin >> codigo;
        limparBufferEntrada();
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
    limparBufferEntrada();

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
    limparBufferEntrada();

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
    limparBufferEntrada();

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


void GerenciadorDeLivros::listarTodosAutores() const {
    cout << "\n--- Lista de Todos os Autores ---" << endl;
    if (autores.empty()) {
        throw ErroSistemaVazio();
    }
    for (const auto& autor : autores) {
        autor->imprimirAutor();
    }
}


void GerenciadorDeLivros::listarTodasEditoras() const {
    cout << "\n--- Lista de Todas as Editoras ---" << endl;
    if (editoras.empty()) {
        throw ErroSistemaVazio();
    }
    for (const auto& editora : editoras) {
        editora->imprimirEditora();
    }
}