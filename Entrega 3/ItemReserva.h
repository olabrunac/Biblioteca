#ifndef ITEMRESERVA_H
#define ITEMRESERVA_H

#include "Livro.h"

class ItemReserva {
    private:
        int nroDoItem;
        int dataDeRetirada;
        Livro* livro;
        
    public:
        ItemReserva();
        void imprimirItemReserva();

        int getNroDoItem();
        int getDataDeRetirada();
        Livro* getLivro();

        void setNroDoItem(int novoNroDoItem);
        void setDataDeRetirada(int novaDataDeRetirada);
        void setLivro(Livro* novoLivro);
};

#endif