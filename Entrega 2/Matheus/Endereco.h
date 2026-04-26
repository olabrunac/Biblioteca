#ifndef ENDERECO_H
#define ENDERECO_H

#include <string>

using std::string;

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
        void imprimirEndereco();

        string getRua();
        int getNumero();
        string getBairro();
        string getCidade();
        string getEstado();
        string getCep();

        void setRua(string novaRua);
        void setNumero(int novoNumero);
        void setBairro(string novoBairro);
        void setCidade(string novaCidade);
        void setEstado(string novoEstado);
        void setCep(string novoCep);
};

#endif