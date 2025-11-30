#ifndef USUARIO_H
#define USUARIO_H

#include <string>

class Usuario {
private:
    std::string nome;
    int moedas;
    int xp;
    int nivel;
    std::string badge;

public:
    // Construtor usado na main
    Usuario(const std::string nome);

    // Construtor usado pelo Repositorio
    Usuario (std::string nome, int nivel, int pontos, int moedas, std::string badge);

    // Getters
    std::string getNome() const;
    int getNivel() const;
    int getXp() const;
    int getMoedas() const; 
    std::string getBadge() const;

    // Setters / Modificadores
    void adicionarXp(int quantidade);
    void adicionarMoedas(int quantidade);
    bool gastarMoedas(int quantidade);
    void setBadge (std::string badge);
    
    // Método para verificar se subiu de nível
    void verificarSubidaNivel();

};

#endif
