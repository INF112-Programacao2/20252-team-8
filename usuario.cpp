#include "Usuario.h"
#include <iostream>
#include <string>

// Construtor usado na main - cria usuário novo
Usuario::Usuario(const std::string& nome)
    : nome(nome), moedas(100), xp(0), nivel(1), badge("Iniciante")
{
    // Usuário novo começa com 100 moedas e badge "Iniciante"
}

// Construtor usado pelo Repositorio - carrega usuário existente
Usuario::Usuario(std::string& nome, int nivel, int xp, int moedas, const std::string& badge) 
    : nome(nome), nivel(nivel), xp(xp), moedas(moedas), badge(badge.empty() || badge == "NULL" ? "Iniciante" : badge)
{
}


// métodos Getters
std::string Usuario::getNome() const {
    return this->nome;
}

int Usuario::getNivel() const {
    return this->nivel;
}

int Usuario::getXp() const {
    return this->xp;
}

int Usuario::getMoedas() const {
    return this->moedas;
}

std::string Usuario::getBadge() const {
    return this->badge;
}

// Adiciona XP 
void Usuario::adicionarXp(int quantidade) {
    this->xp += quantidade;

    // MODO FÁCIL (TESTE): Meta = Nivel * 10
    int xpNecessario = this->nivel * 10;

    // Loop while: Permite subir múltiplos níveis de uma vez se ganhar muito XP
    while (this->xp >= xpNecessario) {
        this->xp = this->xp - xpNecessario; // O que sobra fica para o próximo nível
        this->nivel++;                      // Sobe o nível
        
        xpNecessario = this->nivel * 10;    // Recalcula a nova meta
    }
}

// Adiciona moedas
void Usuario::adicionarMoedas(int quantidade) {
    if (quantidade > 0) {
        this->moedas += quantidade;
    }
}

//sets
void Usuario::setMoedas(int novasMoedas) {
    this->moedas = novasMoedas;
}

// Gasta moedas se tiver suficiente
bool Usuario::gastarMoedas(int quantidade) {
    if (quantidade > 0 && this->moedas >= quantidade) {
        this->moedas -= quantidade;
        return true;
    }
    return false;
}

// Define badge
void Usuario::setBadge(std::string& badge) {
    if (!badge.empty()) {
        this->badge = badge;
    }
}
void Usuario::setNivel(int novoNivel) {
    if (novoNivel >= 1) { // Garante que o nível não seja 0 ou negativo
        this->nivel = novoNivel;
    }
}
