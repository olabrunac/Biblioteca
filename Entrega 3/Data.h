#ifndef DATA
#define DATA

#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

class Data {

    private:
        int data; //Padrão AAAAMMDD
        int dia;
        int mes;
        int ano;

        bool testeDataValida(int d, int m, int a);

    public:
        Data();
        Data(int dia, int mes, int ano);
        Data(int dataInteira);
        ~Data();

        void imprimirData() const;

        int getDia() const;
        int getMes() const;
        int getAno() const;
        int getDataInteira() const;

        void setDataAtual(int novaData);


        Data operator+(int dias) const; //Utilizado no calculo da DataPrevistaDevolução.
        int operator-(const Data& outraData) const; //Utilizado para descobrir os dias de atraso
        bool operator<(const Data& outraData) const;
        bool operator>(const Data& outraData) const;
        bool operator==(const Data& outraData) const;
    };

#endif // DATA