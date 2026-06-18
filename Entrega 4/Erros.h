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

    public:

        ErroUsuarioNaoHabilitado()
            : Erros("Erro relacionado ao usuario") {}

            //emprestimo.cpp nao imprime emprestimo se o usuario for nulo
};


class ErroLivro : public Erros {

    public:

        ErroLivro()
            : Erros("Erro relacionado ao livro") {}

            //no acervo.cpp ao remover um livro tem uma verificacão
            //emprestimo.cpp nao adiciona item se o exemplar for nulo
            //emprestimo.cpp nao permite set item no emprestimo se nao tiver exemplar disponivel

};


class ErroData : public Erros {
    public:
        ErroData()
            : Erros("Erro relacionado a data") {}

            //na data.cpp tem o teste de data valida

};


class ErroEmprestimo : public Erros {
    public:
        ErroEmprestimo()
            : Erros("Erro relacionado ao emprestimo") {}

            //gerenciadordeemprestimos.cpp nao criaemprestimo para usuario em débito
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