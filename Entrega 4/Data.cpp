#include <iostream>
#include <string>
#include "Data.h"
#include "Erros.h"


Data::Data(): dia(1), mes(1), ano(2026) {}  //data padrao 1/1/26 para ver débito e etc


Data::Data(int dia, int mes, int ano) {
    if (testeDataValida(dia, mes, ano)) {
        this->dia = dia;
        this->mes = mes;
        this->ano = ano;
    } else {
        cout << "Aplicando data padrao (01/01/2026)." << endl;
        this->dia = 1;
        this->mes = 1;
        this->ano = 2026;
    }
}


Data::Data(int dataInteira)
    : Data(dataInteira % 100, (dataInteira % 10000) / 100, dataInteira / 10000) {}


Data::Data(int d, int m, int a, bool pularValidacao) {
    this->dia = d;
    this->mes = m;
    this->ano = a;
}


Data::Data(const Data& outra) 
    : dia(outra.dia), mes(outra.mes), ano(outra.ano) {}


Data::~Data() {}


bool Data::testeDataValida(int d, int m, int a) {
    if (a < 1500) {
        throw ErroData();
    }
    if (m < 1 || m > 12) {
       throw ErroData();
    }
    if (d < 1 || d > 31) {
        throw ErroData();
    }
    return true;
}


void Data::imprimirData() const {
    cout << (dia < 10 ? "0" : "") << dia << "/" << (mes < 10 ? "0" : "") << mes << "/" << ano;
}


//-------------------- sets e gets --------------------


int Data::getDia() const {
    return dia;
}


int Data::getMes() const {
    return mes;
}


int Data::getAno() const {
    return ano;
}


int Data::getDataInteira() const {
    return ano * 10000 + mes * 100 + dia;
}


void Data::setData(int novaData) {
    int novaDia = novaData % 100;
    int novaMes = (novaData % 10000) / 100;
    int novoAno = novaData / 10000;

    if (testeDataValida(novaDia, novaMes, novoAno)) {
        this->dia = novaDia;
        this->mes = novaMes;
        this->ano = novoAno;
    } else {
        throw ErroData();
    }
}


//-------------------- operadores --------------------


Data Data::operator+(int dias) const {
    int novoDia = this->dia + dias;
    int novoMes = this->mes;
    int novoAno = this->ano;

    while (novoDia > 30) {
        novoDia -= 30;
        novoMes += 1;

        if (novoMes > 12) {
            novoMes = 1;
            novoAno += 1;
        }
    }

    return Data(novoDia, novoMes, novoAno, true);
}


bool Data::operator<(const Data& outraData) const { return this->getDataInteira() < outraData.getDataInteira(); }


bool Data::operator>(const Data& outraData) const { return this->getDataInteira() > outraData.getDataInteira(); }


bool Data::operator==(const Data& outraData) const { return this->getDataInteira() == outraData.getDataInteira(); }


int Data::operator-(const Data& outraData) const {
    // converte as datas pra dias absolutos (meses de 30 dias igual o operator+)
    int diasDestaData = ano * 360 + mes * 30 + dia;
    int diasDaOutraData = outraData.ano * 360 + outraData.mes * 30 + outraData.dia;
    return diasDestaData - diasDaOutraData;
}
