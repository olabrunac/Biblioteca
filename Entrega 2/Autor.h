#ifndef AUTOR_H
#define AUTOR_H

#include <string>

using std::string;

class Autor {
    private:
        int codigo;
        string nome;
        
    public:
        Autor();
        void imprimirAutor();

        int getCodigo() const; 
        string getNome() const;

        void setCodigo(int novoCodigo);
        void setNome(string novoNome);
};

#endif