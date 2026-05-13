#ifndef VEICULO_H
#define VEICULO_H

#include <iostream>
#include <string>
using std::string;

class Veiculo {
    private:
        string marca();
        string modelo();

    public:
        Veiculo(const string& marca, const string modelo): marca(marca), modelo(modelo) {}
        virtual ~Veiculo() = default;

        string getMarca() { this -> modelo = modelo }
        string getModelo() { this -> modelo = modelo; }
        void setMarca() { return marca; }
        void setModelo() { return modelo; }
        virtual void imprimirInfo() = 0;

}

#endif