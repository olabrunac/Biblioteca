#ifndef MOTO_H
#define MOTO_H

#include <iostream>

class Moto : public Veiculo {
    public:
        Moto(const string& ma, const string mo) : Veiculo(ma, mo) {}
        ~Moto();
        void imprimirInfo() const override {
            cout << "Veiculo do tipo: MOTO" << endl;
            cout << "Marca: " << getMarca() << endl;
            cout << "Modelo: " << getModelo() << endl;
        }
}
#endif