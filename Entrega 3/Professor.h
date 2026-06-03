#ifndef PROFESSOR_H
#define PROFESSOR_H

#include "Usuario.h"
#include <iostream>

using std::cout;
using std::endl;

class Professor : public Usuario {
    private:

    public:
        Professor():Usuario() {}

        void imprimirUsuario() const override {
            cout << "Professor: " << endl;
        }
};

#endif