#ifndef ENDERECO_H
#define ENDERECO_H
#include <iostream>
using namespace std;

class Endereco {
    private:
    string rua;
    int numero;
    string bairro;
    string cidade;
    string estado;
    string cep;

    public:
    Endereco();
    Endereco(string r, int n, string b, string c,  string e, string cp);
    void imprimirEndereco();
    
    void setRua(string rua);
    string getRua();
    void setNumero(int numero);
    int getNumero();
    void setBairro(string bairro);
    string getBairro();
    void setCidade(string cidade);
    string getCidade();
    void setEstado(string estado);
    string getEstado();
    void setCEP(string cep);
    string getCEP();

};

#endif