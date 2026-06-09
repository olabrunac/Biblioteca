#include <iostream>
#include <string>
#include "Data.h"

using std::cout;
using std::endl;

bool Data::testeDataValida(int d, int m, int a) {
    if (a < 1500) {
        cout << "Erro: Ano invalido" << endl;
        return false;
    }
    if (m < 1 || m > 12) {
        cout << "Erro: Mes invalido." << endl;
        return false;
    }
    if (d < 1 || d > 31) {
        cout << "Erro: Dia invalido." << endl;
        return false;
    }
    return true;
}

Data::Data(): dia(7), mes(6), ano(2026) {}

Data::Data(int dia, int mes, int ano) {
    if (testeDataValida(dia, mes, ano)) {
        this->dia = dia;
        this->mes = mes;
        this->ano = ano;
    } else {
        cout << "Aplicando data padrao (07/06/2026)." << endl;
        this->dia = 7;
        this->mes = 6;
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

void Data::imprimirData() const {
    cout << "Data: " << dia << "/" << mes << "/" << ano << endl;
}

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
        cout << "Data nao alterada devido a entrada invalida." << endl;
    }
}

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

    // Retorna chamando o construtor que pula a validação
    return Data(novoDia, novoMes, novoAno, true);
}


int Data::operator-(const Data& outraData) const {
    // Converte ambas as datas para dias absolutos (assumindo meses de 30 dias como no seu operator+)
    int diasDestaData = ano * 360 + mes * 30 + dia;
    int diasDaOutraData = outraData.ano * 360 + outraData.mes * 30 + outraData.dia;
    return diasDestaData - diasDaOutraData;
}

bool Data::operator<(const Data& outraData) const { return this->getDataInteira() < outraData.getDataInteira(); }


bool Data::operator>(const Data& outraData) const { return this->getDataInteira() > outraData.getDataInteira(); }


bool Data::operator==(const Data& outraData) const { return this->getDataInteira() == outraData.getDataInteira(); }
