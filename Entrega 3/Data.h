#ifndef DATA_EMPRESTIMO_H
#define DATA_EMPRESTIMO_H

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

    // Função que valida as datas de AMBOS os construtores, retorna true se a data for válida, false se for inválida.
    // Está como private para ser impossivel de ser chamada fora do construtor
    bool testeDataValida(int d, int m, int a) {

        if (a < 2026) { // Sistema surgiu em 2026, não faz sentido aceitar datas anteriores
            cout << "Erro: Viajante do tempo detectado (Ano < 2026)." << endl;
            return false;
        }
        if (m < 1 || m > 12) { //Testa mês
            cout << "Erro: Mes invalido." << endl;
            return false;
        }
        if (d < 1 || d > 31) { //Testa dia
            cout << "Erro: Dia invalido." << endl;
            return false;
        }
        return true; // Se passou por todos os ifs, a data é válida!
    }

    public:
        //Construtor padrão, atribui a data padrão por atributos individuais.
        Data(): data(20260607), dia(7), mes(6), ano(2026) {} //Construtor padrão, data padrão

        //Construtor para atributos separados
        Data(int dia, int mes, int ano) {
       
            if (testeDataValida(dia, mes, ano )) {
            // Se for válida, atribui os valores do usuário
                this->dia = dia;
                this->mes = mes;
                this->ano = ano;
            } else {
            // Se for inválida, o próprio construtor atribui a data padrão
                cout << "Aplicando data padrao (07/06/2026)." << endl;
                this->dia = 7;
                this->mes = 6;
                this->ano = 2026;
            }
        }
        //Construtor para a data do tipo INT, de formato AAAAMMDD, usado na função de empréstimo.
        Data(int dataInteira) : Data(dataInteira % 100, (dataInteira % 10000) / 100, dataInteira / 10000) {
        // Corpo vazio, usa o construtor de cima para validar e já atribui.
        
        //tambem da pra declarar as atribuições direto aqui

        }

        
        ~Data();
        void imprimirData() const{

            cout << "Data: " << dia << "/" << mes << "/" << ano << endl;
        }

        int getDia() const{

            return dia;

        }


        int getMes() const{

            return mes;

        }
        int getAno() const{

            return ano;
        }


    

};

#endif // DATA_EMPRESTIMO_H