#include <iostream>
using namespace std;


class Produto {
    private:
    int codigo;
    string nome;
    double preco;

    public:
    Produto(int c, string n, double p);  //Construtor
    void imprimir();
    
    void setNome(string nome);
    string getNome();
    void setCodigo(int codigo);
    int getCodigo();
    void setPreco(double preco);
    double getPreco();

    // Exercício 1.1
    void testarPassagemPorReferencia(string nome);
};
