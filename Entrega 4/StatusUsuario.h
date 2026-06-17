#ifndef STATUSUSUARIO_H
#define STATUSUSUARIO_H

#include <string>

enum class StatusUsuario {
    HABILITADO,
    EM_DEBITO
};

inline std::string toString(const StatusUsuario status) {
    switch (status) {
        case StatusUsuario::HABILITADO: return "HABILITADO";
        case StatusUsuario::EM_DEBITO: return "EM_DEBITO";
        default: return "DESCONHECIDO";
    }
}

#endif