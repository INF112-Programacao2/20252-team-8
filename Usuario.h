#ifndef USUARIO_H
#define USUARIO_H

#include <string>
class Usuario {
private:
    const std::string nome;
    int moedas;
    int xp;
    int nivel;
    std::string badge;

public:
    // Construtor usado na main
    Usuario(const std::string& nome);

    // Construtor usado pelo Repositorio
    Usuario (std::string& nome, int nivel, int pontos, int moedas, const std::string& badge);

    // Getters
    std::string getNome() const;
    int getNivel() const;
    int getXp() const;
    int getMoedas() const; 
    std::string getBadge() const;

    // Setters / Modificadores
    void setMoedas(int novasMoedas);
    void adicionarXp(int quantidade);
    void adicionarMoedas(int quantidade);
    bool gastarMoedas(int quantidade);  // Retorna true se conseguiu gastar, false se não tinha saldo
    void setBadge (std::string& badge);
    void setNivel(int novoNivel);
};

#endif
