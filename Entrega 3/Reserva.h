#ifndef RESERVA_H
#define RESERVA_H

#include "ItemReserva.h"
#include "Usuario.h"    //pro polimorfismo

#include <vector>
using std::vector;

class Reserva {
    private:
        int ID;
        int dataRealizacao;
        Usuario* usuario;       //relação polimórfica
        vector<ItemReserva*> itens;     //vetor de ponteiros

    public:
        Reserva();
        ~Reserva();
        void imprimirReserva() const;
        void adicionarItem(ItemReserva* novoItem);

        int getID() const;
        int getDataRealizacao() const;
        Usuario* getUsuario() const;

        void setID(int novoID);
        void setDataRealizacao(int novaDataReserva);
        void setUsuario(Usuario* novoUsuario);
};

#endif