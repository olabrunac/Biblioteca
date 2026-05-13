#include "Produto.h"


Produto::Produto(int c, string n, double p) : codigo(c), nome(n), preco(p) {}

void Produto::imprimir() {
    cout << "Código: " << codigo << ", Nome: " << nome << ", Preço: R$ " << preco << endl;
}


void Produto::setNome(string nome) {
    this-> nome = nome;
}

string Produto::getNome() {
    return nome;
}

void Produto::setCodigo(int codigo) {
    this-> codigo = codigo;
}

int Produto::getCodigo() {
    return codigo;
}

void Produto::setPreco(double preco) {
    this-> preco = preco;
}

double Produto::getPreco() {
    return preco;
}


int main() {

    // Forma estática (stack)
    cout << "Forma estática (stack) p1, p2 e p3:" << endl;
    Produto Alho(1, "Alho", 0.80);
    Alho.imprimir();

    Produto Brioche(2, "Brioche", 1.70);
    Brioche.imprimir();

    Produto Cebola(3, "Cebola", 0.30);
    Cebola.imprimir();


    // Forma dinâmica (heap)
    cout << endl << "Forma dinâmica (heap) p4 e p5:" << endl;
    Produto* Desodorante = new Produto(4, "Desodorante", 12.90);
    Desodorante->imprimir();
    delete Desodorante;

    Produto* Escova = new Produto(5, "Escova", 5.50);
    Escova->imprimir();
    delete Escova;

    // Usando set e get
    cout << endl << "Usando o set e get: " << endl;
    cout << "Atualmente " << Brioche.getNome() << " custa " << Brioche.getPreco() << " reais." << endl;
    Brioche.setPreco(2.10);
    cout << "Preço de " << Brioche.getNome() << " mudou para " << Brioche.getPreco() << " reais." << endl << endl;

    Brioche.imprimir();
    cout << endl;

    // Acessando algum atributo privado
    cout << "Tentando acessar atributos privados: " << endl;
    //cout << "O nome do produto 1 é:::: " << Alho.nome << endl;
    //cout << "O valor dele é:::: " << Alho.preco << endl;
    cout << endl;
}