#ifndef RESERVA_H
#define RESERVA_H

class Reserva {
    private:
        int ID;
        int dataRealizacao;
        
    public:
        Reserva();
        void imprimirReserva();

        int getID();
        int getDataRealizacao();

        void setID(int novoID);
        void setDataRealizacao(int novaDataReserva);
};

#endif