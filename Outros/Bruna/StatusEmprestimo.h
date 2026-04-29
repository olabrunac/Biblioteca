#ifndef STATUSEMPRESTIMO_H                                              // "Include Guard": Verifica com o compilador se esta flag ainda NÃO foi definida (evita recompilar o mesmo arquivo repetidas vezes)
#define STATUSEMPRESTIMO_H                                              // Se não estava definida antes, define a tag agora protegendo todo este código

#include <string>

enum class StatusEmprestimo {                                           // 'enum class': Cria um enumerador com "Escopo Forte" (Scoped Enum). Ele protege de bugs pq não deixa ser comparado acidentalmente a inteiros simples ou com outros enums e te obriga a usar 'StatusEmprestimo::'
    DISPONIVEL,                                                         // Equivalente lógico ao valor numérico 0 na memória
    EMPRESTADO                                                          // Equivalente lógico ao valor numérico 1 na memória
};

inline std::string toString(const StatusEmprestimo status) {            // 'inline': Sugere ao compilador substituir as chamadas a essa função no código-fonte pelo código real dela. Isso é OBRIGATÓRIO aqui pois evita erros de linkagem (múltiplas definições) já que a função foi escrita diretamente num header (.h)
    switch (status) {                                                   // Checa e abre as possibilidades para o argumento status fornecido
        case StatusEmprestimo::DISPONIVEL: return "DISPONIVEL";         // Se foi DISPONIVEL, devolve em texto formatado cortando o switch
        case StatusEmprestimo::EMPRESTADO: return "EMPRESTADO";         // Se foi EMPRESTADO, devolve em texto formatado cortando o switch
        default: return "DESCONHECIDO";                                 // Opção genérica fallback de segurança
    }
}

#endif                                                                  // Finaliza o bloco Include Guard do #ifndef aberto lá no começo