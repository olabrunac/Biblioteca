#ifndef CARRO_H
#define CARRO_H

#include <iostream>
#include <string>

class Carro : public Veiculo {
    private:
        string tipoSensor();
        TetoSolar teto();

        Motor* motor;

    public:
        Carro(const string& ma, const string mo, string t) : Veiculo(ma, mo), tipoSensor(t) {}
        ~Carro();

        TetoSolar getTetoSolar() { return teto; }
        void setTetoSolar() { this -> teto = teto; }

        void imprimirInfo() const override {
            cout << "Veiculo do tipo: CARRO" << endl;
            cout << "Marca: " << getMarca() << endl;
            cout << "Modelo: " << getModelo() << endl;
            cout << "Tipo do sensor: " << tipoSensor << endl;
        }
}
#endif