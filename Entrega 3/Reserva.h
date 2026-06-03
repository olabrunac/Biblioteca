#ifndef RESERVA_H
#define RESERVA_H

#include "ItemReserva.h"

#include <vector>
using std::vector;

class Reserva {
    private:
        int ID;
        ///*************ADICIONAR A RELAÇÃO COM O USUARIO, CASO NECESSARIO UTILIZE POLIMORFISMO */
        int dataRealizacao;
        vector<ItemReserva*> itens;

    public:
        Reserva();
        void imprimirReserva();

        int getID();
        int getDataRealizacao();

        void setID(int novoID);
        void setDataRealizacao(int novaDataReserva);
};

#endif