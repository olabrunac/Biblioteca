#ifndef ERROS_H
#define ERROS_H

#include <stdexcept>
#include <string>

using std::string;
using std::runtime_error;

class Erros : public runtime_error {

    public:

        Erros(string msg)
            : runtime_error(msg) {}

};

class ErroUsuarioNaoHabilitado : public Erros {

    public:ErroUsuarioNaoHabilitado()

        
            : Erros("Osuario está em débito e não pode realizar emprestimos") {}

            //emprestimo.cpp nao imprime emprestimo se o usuario for nulo 
            //gerenciadorDeEmprestimo.cpp | linha 33; 95; 178; 237 | acontece se o usúario não estiver com status "Habilitado"
};

class ErroNenhumaReserva : public Erros {

    public:

        ErroNenhumaReserva()
            : Erros("O usuario não possui nenhuma reserva ativa") {}
};

class ErroUsuarioNaoExiste: public Erros {

    public:

        ErroUsuarioNaoExiste()
            : Erros("O usuario informado não existe"){}


};
class ErroUsuarioJaReservouLivro: public Erros {

    public:
        ErroUsuarioJaReservouLivro() : Erros("O usuario já tem uma reserva desse livro") {}
        //gerenciadorEmprestimo.cpp| linha 187
}; 

class ErroLivroNaoExisteAcervo : public Erros {

    public:

        ErroLivroNaoExisteAcervo()
            : Erros("Livro não encontrado") {}

            //no acervo.cpp ao remover um livro tem uma verificacão
            //emprestimo.cpp nao adiciona item se o exemplar for nulo
            //emprestimo.cpp nao permite set item no emprestimo se nao tiver exemplar disponivel

};

class ErroExemplarGuardado : public Erros {

    public:
        ErroExemplarGuardado()
        : Erros("Nenhum exemplar do livro está emprestado"){}
        
};
class ErroExemplarNulo : public Erros {

    ErroExemplarNulo ()
     : Erros("O exemplar informado não existe ou não foi encontrado"){}

};


class ErroIndisponivel: public Erros {

    ErroIndisponivel()
        : Erros(" O exemplar informado não está disponível"){

        }
};

class ErroData : public Erros {
    public:
        ErroData()
            : Erros("A data informada é inválida") {}

            //na data.cpp tem o teste de data valida

};


class ErroNenhumEmprestimo : public Erros {
    public:
        ErroNenhumEmprestimo()
            : Erros("Nenhum empréstimo relacionado com o usuário informado") {}


};
class ErroLivroIndisponivel : public Erros {

    public:
        ErroLivroIndisponivel()
            : Erros("O livro informado está indisponível no periodo"){}
};


class ErroNaoLivro : public Erros {
    public:
        ErroNaoLivro()
            : Erros(" A existência do livro é um mistério") {}
};

class ErroEmprestimoVazio : public Erros {

    public:
        ErroEmprestimoVazio()
            : Erros("O empréstimo está vazio") {}

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