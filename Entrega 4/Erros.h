#ifndef ERROS_H
#define ERROS_H

#include <stdexcept>
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
};

class ErroUsuarioNaoHabilitado : public Erros {
    public:
    ErroUsuarioNaoHabilitado()
        : Erros("[ErroUsuarioNaoHabilitado]: O usuario esta em debito e nao pode realizar esta acao.") {}
        //emprestimo.cpp nao imprime emprestimo se o usuario for nulo 
        //gerenciadorDeEmprestimo.cpp | linha 33; 95; 178; 237; 545; | acontece se o usúario não estiver com status "Habilitado"
};

class ErroTipoUsuarioInvalido : public Erros {
    public:
    ErroTipoUsuarioInvalido()
        : Erros("[ErroTipoUsuarioInvalido]: Tipo de usuario invalido. Use 1 para Aluno ou 2 para Professor.") {}
        //GerenciadorDeUsuarios.cpp
};

class ErroUsuarioComPendencias : public Erros {
    public:
    ErroUsuarioComPendencias()
        : Erros("[ErroUsuarioComPendencias]: Usuario nao pode ser removido pois possui emprestimos ou reservas ativas.") {}
        //GerenciadorDeUsuarios.cpp
};

/*---------------------------- ERROS DE RESERVA / EMPRESTIMO ----------------------------*/

class ErroNenhumaReserva : public Erros {
    public:
    ErroNenhumaReserva()
        : Erros("[ErroNenhumaReserva]: O usuario nao possui nenhuma reserva ativa.") {}
};

class ErroNenhumEmprestimo : public Erros {
    public:
    ErroNenhumEmprestimo()
        : Erros("[ErroNenhumEmprestimo]: Nenhum emprestimo ativo encontrado para esta busca.") {}
};

class ErroEmprestimoVazio : public Erros {
    public:
    ErroEmprestimoVazio()
        : Erros("[ErroEmprestimoVazio]: O emprestimo esta vazio, nenhum item valido foi adicionado.") {}
};

class ErroUsuarioJaReservouLivro: public Erros {
    public:
    ErroUsuarioJaReservouLivro()
        : Erros("[ErroUsuarioJaReservouLivro]: O usuario ja tem uma reserva ativa para este livro.") {}
        //gerenciadorEmprestimo.cpp| linha 69; 187;
}; 

class ErroUsuarioJaEmprestouLivro: public Erros {
    public:
    ErroUsuarioJaEmprestouLivro()
        : Erros("[ErroUsuarioJaEmprestouLivro]: O usuario ja possui um emprestimo ativo deste livro.") {}
        //gerenciadorEmprestimos.cpp || linha 113;
};

/*---------------------------- ERROS DE LIVRO / EXEMPLAR ----------------------------*/

class ErroLivroNaoExisteAcervo : public Erros {
    public:
        ErroLivroNaoExisteAcervo()
        : Erros("[ErroLivroNaoExisteAcervo]: Livro nao encontrado no acervo.") {}
        //acervo.cpp || linha 52
};

class ErroLivroEmUso : public Erros {
    public:
    ErroLivroEmUso()
        : Erros("[ErroLivroEmUso]: O livro nao pode ser removido pois possui emprestimos ou reservas ativas.") {}
        //gerenciadorDeLivros.cpp || linha 129
};

class ErroExemplarGuardado : public Erros {
    public:
    ErroExemplarGuardado()
        : Erros("[ErroExemplarGuardado]: Nenhum exemplar do livro esta emprestado ou reservado no momento."){}    
};

class ErroLivroIndisponivel : public Erros {
    public:
    ErroLivroIndisponivel()
        : Erros("[ErroLivroIndisponivel]: O livro informado esta indisponivel para emprestimo ou reserva."){}
};

class ErroAutorNaoExiste : public Erros {
    public:
    ErroAutorNaoExiste()
        : Erros("[ErroAutorNaoExiste]: O autor informado nao foi encontrado.") {}
        //GerenciadorDeLivros.cpp   ||  linha 94; 214;
};

class ErroEditoraNaoExiste : public Erros {
    public:
    ErroEditoraNaoExiste()
        : Erros("[ErroEditoraNaoExiste]: A editora informada nao foi encontrada.") {}
        //GerenciadorDeLivros.cpp   ||  linha 91; 239;
};

class ErroAutorAssociado : public Erros {
    public:
    ErroAutorAssociado()
        : Erros("[ErroAutorAssociado]: Autor nao pode ser removido pois esta associado a um ou mais livros.") {}
        //GerenciadorDeLivros.cpp   ||  201;
};

class ErroEditoraAssociada : public Erros {
    public:
    ErroEditoraAssociada()
        : Erros("[ErroEditoraAssociada]: Editora nao pode ser removida pois esta associada a um ou mais livros.") {}
        //GerenciadorDeLivros.cpp   || 227;
};

/*---------------------------- ERROS VARIADOS ----------------------------*/

class ErroData : public Erros {
    public:
    ErroData()
        : Erros("[ErroData]: A data informada eh invalida.") {}
        //data.cpp || linha 43; 46; 49; 90; 
};

class ErroSistemaVazio : public Erros {
    public:
    ErroSistemaVazio()
        : Erros("[ErroSistemaVazio]: Nao ha itens para listar.") {}
};

class ErroOpcaoInvalida : public Erros {
    public:
    ErroOpcaoInvalida()
        : Erros("[ErroOpcaoInvalida]: A opcao digitada eh invalida. Por favor, insira um numero.") {}
        //SistemaBiblioteca.cpp
};




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