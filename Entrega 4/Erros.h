#ifndef ERROS_H
#define ERROS_H

#include <stdexcept>
#include <iostream>
#include <limits>
#include <string>

using std::string;
using std::runtime_error;
using std::cerr;

class Erros : public runtime_error {
    public:
    Erros(string msg)
        : runtime_error(msg) {}
};

/*---------------------------- ERROS DE USUARIO ----------------------------*/

class ErroUsuarioNaoExiste: public Erros {
    public:
    ErroUsuarioNaoExiste()
        : Erros("[ErroUsuarioNaoExiste]: O usuario informado nao existe no sistema.") {}
        //gerenciadordeemprestimos.cpp  | 290;
        //gerenciadordeusuarios.cpp     | 82; 126;
};

class ErroUsuarioNaoHabilitado : public Erros {
    public:
    ErroUsuarioNaoHabilitado()
        : Erros("[ErroUsuarioNaoHabilitado]: O usuario esta em debito.") {}
        //gerenciadorDeEmprestimo.cpp   | linha 30; 86; 137; 189; 477; | acontece se o usúario não estiver com status "Habilitado"
};

class ErroTipoUsuarioInvalido : public Erros {
    public:
    ErroTipoUsuarioInvalido()
        : Erros("[ErroTipoUsuarioInvalido]: Tipo de usuario invalido. Use 1 para Aluno, 2 para Professor ou 3 para Pesquisador.") {}
        //GerenciadorDeUsuarios.cpp | 65;
};

class ErroUsuarioComPendencias : public Erros {
    public:
    ErroUsuarioComPendencias()
        : Erros("[ErroUsuarioComPendencias]: Usuario nao pode ser removido pois possui emprestimos ou reservas ativas.") {}
        //GerenciadorDeUsuarios.cpp | 87;
};

class ErroUsuarioJaExiste : public Erros {
    public:
    ErroUsuarioJaExiste(const string& nome)
        : Erros("[ErroUsuarioJaExiste]: Um usuario com o nome '" + nome + "' ja existe.") {}
        //gerenciadorDeUsuarios.cpp | 51;
};


/*---------------------------- ERROS DE RESERVA / EMPRESTIMO ----------------------------*/

class ErroNenhumaReserva : public Erros {
    public:
    ErroNenhumaReserva()
        : Erros("[ErroNenhumaReserva]: O usuario nao possui nenhuma reserva ativa.") {}
        //gerenciadorDeEmprestimos.cpp  | 306; 421;
        //sistemabiblioteca             | 371;
};

class ErroNenhumEmprestimo : public Erros {
    public:
    ErroNenhumEmprestimo()
        : Erros("[ErroNenhumEmprestimo]: Nenhum emprestimo ativo encontrado para esta busca.") {}
        //gerenciadordeEmprestimos.cpp  | 323; 412;
};

class ErroEmprestimoVazio : public Erros {
    public:
    ErroEmprestimoVazio()
        : Erros("[ErroEmprestimoVazio]: O emprestimo esta vazio, nenhum item valido foi adicionado.") {}
        //gerenciadordeemprestimos.cpp  | 130;
};

class ErroUsuarioJaReservouLivro: public Erros {
    public:
    ErroUsuarioJaReservouLivro()
        : Erros("[ErroUsuarioJaReservouLivro]: O usuario ja tem uma reserva ativa para este livro.") {}
        //gerenciadorEmprestimo.cpp | linha 197;
}; 

class ErroUsuarioJaEmprestouLivro: public Erros {
    public:
    ErroUsuarioJaEmprestouLivro()
        : Erros("[ErroUsuarioJaEmprestouLivro]: O usuario ja possui um emprestimo ativo deste livro.") {}
        //gerenciadorEmprestimos.cpp || linha 38;
};

/*---------------------------- ERROS DE LIVRO / EXEMPLAR ----------------------------*/

class ErroLivroNaoExisteAcervo : public Erros {
    public:
        ErroLivroNaoExisteAcervo()
        : Erros("[ErroLivroNaoExisteAcervo]: Livro nao encontrado no acervo.") {}
        //acervo.cpp                    | 52;
        //emprestimo.cpp                | 47; 96;
        //gerenciadordeemprestimos.cpp  | 443;
        //gerenciadordelivros.cpp       | 192;
        //sistemabiblioteca.cpp         | 207; 297; 422;
};

class ErroLivroEmUso : public Erros {
    public:
    ErroLivroEmUso()
        : Erros("[ErroLivroEmUso]: O livro nao pode ser removido pois possui emprestimos ou reservas ativas.") {}
        //gerenciadorDeLivros.cpp   | linha 192
};

class ErroLivroJaExiste : public Erros {
    public:
    ErroLivroJaExiste(const string& titulo)
        : Erros("[ErroLivroJaExiste]: Um livro com o titulo '" + titulo + "' ja existe no acervo.") {}
        //gerenciadordelivros.cpp   | 73;
};

class ErroExemplarGuardado : public Erros {
    public:
    ErroExemplarGuardado()
        : Erros("[ErroExemplarGuardado]: Nenhum exemplar do livro esta emprestado ou reservado no momento."){}    
        //gerenciadordemprestimos.cpp   | 345;
};

class ErroLivroIndisponivel : public Erros {
    public:
    ErroLivroIndisponivel()
        : Erros("[ErroLivroIndisponivel]: O livro informado esta indisponivel."){}
        //gerenciadordeEmprestimos.cpp  | 119; 142;
        //livro.cpp                     | 127;
};

class ErroLivroIndisponivelE : public Erros {
    public:
    ErroLivroIndisponivelE()
        : Erros("[ErroLivroIndisponivelE]: O livro informado esta indisponivel para emprestimo."){}
        //sistemabiblioteca.cpp | 211;
};

class ErroAutorNaoExiste : public Erros {
    public:
    ErroAutorNaoExiste()
        : Erros("[ErroAutorNaoExiste]: O autor informado nao foi encontrado.") {}
        //GerenciadorDeLivros.cpp   ||  linha 89; 231;
};

class ErroAutorJaExiste : public Erros {
    public:
    ErroAutorJaExiste(const string& nome)
        : Erros("[ErroAutorJaExiste]: Um autor com o nome '" + nome + "' ja existe.") {}
        //gerenciadordelivros.cpp   | 108;
};

class ErroEditoraJaExiste : public Erros {
    public:
    ErroEditoraJaExiste(const string& nome)
        : Erros("[ErroEditoraJaExiste]: Uma editora com o nome '" + nome + "' ja existe.") {}
        //gerenciadordelivros.cpp   | 128;
};

class ErroEditoraNaoExiste : public Erros {
    public:
    ErroEditoraNaoExiste()
        : Erros("[ErroEditoraNaoExiste]: A editora informada nao foi encontrada.") {}
        //GerenciadorDeLivros.cpp   |  linha 86; 256;
};

class ErroAutorAssociado : public Erros {
    public:
    ErroAutorAssociado()
        : Erros("[ErroAutorAssociado]: Autor nao pode ser removido pois esta associado a um ou mais livros.") {}
        //GerenciadorDeLivros.cpp   | 218;
};

class ErroEditoraAssociada : public Erros {
    public:
    ErroEditoraAssociada()
        : Erros("[ErroEditoraAssociada]: Editora nao pode ser removida pois esta associada a um ou mais livros.") {}
        //GerenciadorDeLivros.cpp   | 244;
};

/*---------------------------- ERROS VARIADOS ----------------------------*/

class ErroData : public Erros {
    public:
    ErroData()
        : Erros("[ErroData]: A data informada eh invalida.") {}
        //data.cpp  | linha 44; 47; 50; 94; 
};

class ErroSistemaVazio : public Erros {
    public:
    ErroSistemaVazio()
        : Erros("[ErroSistemaVazio]: Nao ha itens para listar.") {}
        //gerenciadordeemprestimos.cpp  | 278;
};

// função para limpar o buffer de entrada
inline void limparBufferEntrada() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}





#endif


/*

int main () {
    int n;
    cout << "Digite um numero inteiro positivo";
    cin >> n;

    try {
        if (n < 0){
            trow invalid_argument("Numero negativo nao é permitido");
        }
        cout << "Voce digitou: " << n << endl;
    } catch (const invalid_argument& e) {
    std::cerr <<"Erro: " << e.what() << endl;
    }
    return 0;
}





*/