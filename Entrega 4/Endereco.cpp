#include <iostream>

#include "Endereco.h"

using std::cout;
using std::endl;


Endereco::Endereco() {}


Endereco::Endereco(string novaRua, int novoNumero, string novoBairro, string novaCidade, string novoEstado, string novoCep)
    : rua(novaRua), numero(novoNumero), bairro(novoBairro), cidade(novaCidade), estado(novoEstado), cep(novoCep) {}


Endereco::~Endereco() {}        //outro que nao faz alocacao dinamica


void Endereco::imprimirEndereco() {
    cout << "Endereco: " << rua << ", " << numero << ", " << bairro << ", " << cidade << "- " << estado << ", " << cep << endl;
}


//-------------------- sets e gets --------------------


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
