#ifndef DATA
#define DATA

#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

class Data {

    private:
        int dia;
        int mes;
        int ano;

    public:
        Data();
        Data(int dia, int mes, int ano);
        Data(int dataInteira);
        Data(int d, int m, int a, bool pularValidacao); //Construtor pula validacao
        static bool testeDataValida(int d, int m, int a);

        Data(const Data& outra); //Construtor de copia
        ~Data();

        void imprimirData() const;

        int getDia() const;
        int getMes() const;
        int getAno() const;
        int getDataInteira() const;

        void setData(int novaData);

        Data operator+(int dias) const; //Utilizado no calculo da DataPrevistaDevolução.


        bool operator<(const Data& outraData) const;
        bool operator>(const Data& outraData) const;

        bool operator==(const Data& outraData) const;
        int operator-(const Data& outraData) const; //Talvez use


    };

#endif // DATA