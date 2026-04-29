#include "Usuario.h"
#include <iostream>

using std::cout;
using std::endl;

Usuario::Usuario(): codigo(0), nome(""), status(StatusUsuario::HABILITADO){}             // Constructor "Initialization List": Essa é a maneira mais veloz no C++ de injetar estados iniciais antes mesmo do corpo do construtor '{ }' ser engatilhado

void Usuario::imprimirUsuario() const {                                                  // 'const' na assinatura garante que não faremos modificação no estado original do objeto
    cout << "Nome: " << nome << endl;
    cout << "Codigo: " << codigo << endl;
    cout << "Status do usuario: ";
    if (status == StatusUsuario::HABILITADO) {                                           // Avalia o enum (Note a obrigatoriedade de usar 'StatusUsuario::' graças ao enum class)
        cout << "Habilitado" << endl;                                                    // Resultado formatado de sucesso
    } else {                                                                             // Caso contrário 
        cout << "Em debito" << endl;                                                     // Resultado formatado de penalidade (debito)
    }
}

int Usuario::getCodigo() const { return codigo; }                                        // getCodigo é o método e o codigo é o parametro

string Usuario::getNome() const{ return nome; }

StatusUsuario Usuario::getStatus() const { return status; }                              //Retorna a configuração do enumerador (tipo seguro StatusUsuario)


void Usuario::setCodigo(int novoCodigo) { this -> codigo = novoCodigo; }                 //this -> evita conflito de nomes e injeta valor passado de fora

void Usuario::setNome(string novoNome) { this -> nome = novoNome; }

void Usuario::setStatus(StatusUsuario novoStatus) { this -> status = novoStatus; } // Para Enums,não precisa passar por referência
// (Setter) Enums de tamanho pequeno são armazenados e copiados como inteiros simples sob a engrenagem, portanto cópia direta aqui custa muito pouco e dispensa o uso de '&'
