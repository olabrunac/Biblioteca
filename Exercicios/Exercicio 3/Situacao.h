#ifndef SITUACAO_H
#define SITUACAO_H
#include <string>

using std::string;

class Situacao {
    public:
        enum Valor {
            ABERTO,
            EM_PREPARO,
            FINALIZADO,
            CANCELADO
        };

        Situacao(Valor v) : valor(v) {}
        Situacao() : valor() {}

        string toString() const {
            switch (valor) {
                case ABERTO : return "Aberto";
                case EM_PREPARO : return "Em preparo";
                case FINALIZADO : return "Finalizado";
                case CANCELADO : return "Cancelado";
                default: return "Desconhecido";
            }
        }
    private:
    Valor valor;
};

#endif