#include "Usuario.h"
#include <iostream>

using std::cout;
using std::endl;

Usuario::Usuario(): codigo(0), nome(""), status(StatusUsuario::HABILITADO){}

Usuario::Usuario(int novoCodigo, string novoNome, StatusUsuario status) : codigo(novoCodigo), nome(novoNome), status(novoStatus) {}

int Usuario::getCodigo() const { return codigo; } 

string Usuario::getNome() const{ return nome; }

StatusUsuario Usuario::getStatus() const { return status; }

void Usuario::setCodigo(int novoCodigo) { this -> codigo = novoCodigo; }

void Usuario::setNome(string novoNome) { this -> nome = novoNome; }

void Usuario::setStatus(StatusUsuario novoStatus) { this -> status = novoStatus; }
