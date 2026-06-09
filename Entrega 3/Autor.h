#ifndef AUTOR_H
#define AUTOR_H

#include <string>
#include <vector>

using std::string;
using std::vector;

class Autor {
    private:
        int codigo;
        string nome;
        
    public:
        Autor();
        Autor(int novoCodigo, string novoNome);
        ~Autor();

        void imprimirAutor();
        static void imprimirTodos(const vector<Autor*>& listaAutores);          //static nao pertence a nenhum autor especifico e sim a classe autor

        int getCodigo() const; 
        string getNome() const;

        void setCodigo(int novoCodigo);
        void setNome(string novoNome);
};

#endif