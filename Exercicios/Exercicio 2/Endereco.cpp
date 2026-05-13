#include "Endereco.h"



// Construtor
    Endereco::Endereco() {}
    Endereco::Endereco(string r, int n, string b, string c, string e, string cp) : rua(r), numero(n), cidade(c), estado(e), cep(cp) {}

// Imprimir Endereco
    void Endereco::imprimirEndereco() {
        cout << "Endereco: " << rua << ", " << numero << ", " << bairro << ", " << estado << ", " << cep << endl;
    }
// set e get Rua
    void Endereco::setRua(string rua) { this -> rua = rua; }
    string Endereco::getRua() { return rua; }

// set e get Numero
    void Endereco::setNumero(int numero) { this -> numero = numero; }
    int Endereco::getNumero() { return numero; }

// set e get Bairro
    void Endereco::setBairro(string bairro) { this -> bairro = bairro; }
    string Endereco::getBairro() { return bairro; }

// set e get Cidade
    void Endereco::setCidade(string cidade) { this -> cidade = cidade; }
    string Endereco::getCidade() { return cidade; }

// set e get Estado
    void Endereco::setEstado(string estado) { this -> estado = estado; }
    string Endereco::getEstado() { return estado; }

// set e get CEP
    void Endereco::setCEP(string cep) { this -> cep = cep; }
    string Endereco::getCEP() { return cep; }