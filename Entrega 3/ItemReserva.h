#ifndef ITEMRESERVA_H
#define ITEMRESERVA_H

#include "Livro.h"
#include "Data.h"

//Esta utilizando objetos Data

class ItemReserva {
    private:
        int nroDoItem;
        Data dataDeRetirada;
        Livro* livro;
        
    public:
        ItemReserva();
        ItemReserva(int novoNroDoItem, const Data& novaDataDeRetirada, Livro* novoLivro);
        ~ItemReserva();                                             //reserva já faz esse trampo
        void imprimirItemReserva() const;

        int getNroDoItem() const;
        Data getDataDeRetirada() const;
        Livro* getLivro()const ;

        void setNroDoItem(const int novoNroDoItem);
        void setDataDeRetirada(const Data& novaDataDeRetirada);
        void setLivro(Livro* novoLivro);
};

#endif