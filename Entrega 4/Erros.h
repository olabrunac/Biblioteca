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

class ErroUsuarioNãoHabilitado : public Erros {

public:

    ErroUsuarioNãoHabilitado()
        : Erros("Erro relacionado ao usuario") {}

};


class ErroLivro : public Erros {

public:

    ErroLivro()
        : Erros("Erro relacionado ao livro") {}

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