#include <iostream>

#include "Endereco.h"

using std::cout;
using std::endl;

Endereco::Endereco() {}

void Endereco::imprimirEndereco() {
    cout << "Rua: " << rua << endl;
    cout << "Numero: " << numero << endl;
    cout << "Bairro: " << bairro << endl;
    cout << "Cidade: " << cidade << endl;
    cout << "Estado: " << estado << endl;
    cout << "CEP: " << cep << endl;
}

string Endereco::getRua() { return rua; }

int Endereco::getNumero() { return numero; }

string Endereco::getBairro() { return bairro; }

string Endereco::getCidade() { return cidade; }

string Endereco::getEstado() { return estado; }

string Endereco::getCep() { return cep; }

void Endereco::setRua(string novaRua) { this -> rua = novaRua; }

void Endereco::setNumero(int novoNumero) { this -> numero = novoNumero; }

void Endereco::setBairro(string novoBairro) { this -> bairro = novoBairro; }

void Endereco::setCidade(string novaCidade) { this -> cidade = novaCidade; }

void Endereco::setEstado(string novoEstado) { this -> estado = novoEstado; }

void Endereco::setCep(string novoCep) { this -> cep = novoCep; }
