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
        : Erros("O usuario informado não existe") {}
};

class ErroUsuarioNaoHabilitado : public Erros {
    public:
    ErroUsuarioNaoHabilitado()
        : Erros("[ErroUsuarioNaoHAbilitado]: O usuario esta em debito e nao pode realizar emprestimos") {}
        //emprestimo.cpp nao imprime emprestimo se o usuario for nulo 
        //gerenciadorDeEmprestimo.cpp | linha 33; 95; 178; 237; 545; | acontece se o usúario não estiver com status "Habilitado"
};

/*---------------------------- ERROS DE RESERVA / EMPRESTIMO ----------------------------*/

class ErroNenhumaReserva : public Erros {
    public:
    ErroNenhumaReserva()
        : Erros("O usuario não possui nenhuma reserva ativa") {}
};

class ErroNenhumEmprestimo : public Erros {
    public:
    ErroNenhumEmprestimo()
        : Erros("Nenhum empréstimo relacionado com o usuário informado") {}
};

class ErroReservaVazia : public Erros {
    public:
    ErroReservaVazia()
        : Erros("A reserva esta vazia") {}
};

class ErroEmprestimoVazio : public Erros {
    public:
    ErroEmprestimoVazio()
        : Erros("O empréstimo está vazio") {}
};

class ErroEmprestimoInvalido : public Erros {
    public:
    ErroEmprestimoInvalido()
        : Erros("[ErroEmprestimoInvalido]: Item invalido") {}
};

class ErroUsuarioJaReservouLivro: public Erros {
    public:
    ErroUsuarioJaReservouLivro()
        : Erros("[ErroUsuarioJaReservouLivro]: O usuario ja tem uma reserva desse livro") {}
        //gerenciadorEmprestimo.cpp| linha 69; 187;
}; 

class ErroUsuarioJaEmprestouLivro: public Erros {
    public:
    ErroUsuarioJaEmprestouLivro()
        : Erros("[ErroUsuarioJaEmprestouLivro]: O usuario ja tem um emprestimo desse livro") {}
        //gerenciadorEmprestimos.cpp || linha 113;
};

/*---------------------------- ERROS DE LIVRO / EXEMPLAR ----------------------------*/

class ErroLivroNaoExisteAcervo : public Erros {
    public:
        ErroLivroNaoExisteAcervo()
        : Erros("[ErroLivroNaoExisteAcervo]: Livro nao encontrado") {}
        //acervo.cpp || linha 52
};

class ErroLivroEmUso : public Erros {
    public:
    ErroLivroEmUso()
        : Erros("[ErroLivroEmUso]: Livro em uso, nao foi possivel completar a acao") {}
        //gerenciadorDeLivros.cpp || linha 129
};

class ErroExemplarGuardado : public Erros {
    public:
    ErroExemplarGuardado()
        : Erros("Nenhum exemplar do livro está emprestado"){}    
};

class ErroExemplarNulo : public Erros {
    public:
    ErroExemplarNulo ()
        : Erros("[ErroExemplarNulo]:O exemplar informado nao existe ou nao foi encontrado"){}
};

class ErroLivroIndisponivel : public Erros {
    public:
    ErroLivroIndisponivel()
        : Erros("[ErroLivroIndisponivel]: O livro informado esta indisponivel"){}
};

class ErroNaoLivro : public Erros {
    public:
    ErroNaoLivro()
        : Erros(" A existência do livro é um mistério") {}
};

/*---------------------------- ERROS VARIADOS ----------------------------*/

class ErroData : public Erros {
    public:
    ErroData()
        : Erros("[ErroData]: A data informada eh invalida") {}
        //data.cpp || linha 43; 46; 49; 90; 
};

class ErroSistemaVazio : public Erros {
    public:
    ErroSistemaVazio()
        : Erros("O sistema está vazio") {}
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