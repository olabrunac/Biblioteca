#ifndef RESERVA_H
#define RESERVA_H

#include "ItemReserva.h"
#include "Usuario.h"    //pro polimorfismo


#include <vector>
using std::vector;

class Reserva {
    private:
        int ID;
        Data dataRealizacao;
        Usuario* usuario;       //relação polimórfica
        vector<ItemReserva*> itens;     //vetor de ponteiros

    public:
        Reserva(); //Constrotores padrão; com vetor e sem vetor de itens
        Reserva(int novoID, const Data& novaDataRealizacao, Usuario* novoUsuario);
        Reserva(int novoID, const Data& novaDataRealizacao, Usuario* novoUsuario, const vector<ItemReserva*>& itens);
        ~Reserva();
        void imprimirReserva() const;
        void adicionarItem(ItemReserva* novoItem);

        int getID() const;
        Data getDataRealizacao() const;
        Usuario* getUsuario() const;
        const vector<ItemReserva*>& getItens() const;
        bool possuiLivro(const Livro* livroBuscado) const;
        ItemReserva* getItemPorLivro(Livro* livro) const; //Usado no gerenciador

        void setID(int novoID);
        void setDataRealizacao(Data& novaDataReserva);
        void setUsuario(Usuario* novoUsuario);
};

#endif