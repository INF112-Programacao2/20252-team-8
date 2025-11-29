#ifndef USUARIO_H
#define USUARIO_H

#include <string>
#include "Loja.h" 
#include "RepositorioEstudos.h" 

class Usuario {
private:
    std::string nomeDeUsuario;
    int moedas;
    int pontos;
    int nivel;

    //Composicao 
    RepositorioEstudos Repositorio;
    Loja loja;

public:
    Usuario();

    int getMoedas() const; 

    std::string getNome() const;

    void setNome(const std::string& novoNome);

    Loja& getLoja();

    RepositorioEstudos& getRepositorio();
};
#endif

