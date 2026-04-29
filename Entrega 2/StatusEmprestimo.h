#ifndef STATUSEMPRESTIMO_H
#define STATUSEMPRESTIMO_H

#include <string>

enum class StatusEmprestimo {
    DISPONIVEL,
    EMPRESTADO
};

inline std::string toString(const StatusEmprestimo status) {
    switch (status) {
        case StatusEmprestimo::DISPONIVEL: return "DISPONIVEL";
        case StatusEmprestimo::EMPRESTADO: return "EMPRESTADO";
        default: return "DESCONHECIDO";
    }
}

#endif