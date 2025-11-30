#ifndef USUARIO_H
#define USUARIO_H

#include <string>

class Usuario {
private:
    std::string nome;
    int moedas;
    int xp;
    int nivel;

public:
    // Construtor usado na main
    Usuario(std::string nome);

    // Construtor usado pelo Repositorio
    Usuario (std::string, int nivel, int xp, int moedas);

    // Getters
    std::string getNome() const;
    int getNivel() const;
    int getXp() const;
    int getMoedas() const; 

    // Setters / Modificadores
    void adicionarXp(int quantidade);
    void adicionarMoedas(int quantidade);
    bool gastarMoedas(int quantidade);

};

#endif

