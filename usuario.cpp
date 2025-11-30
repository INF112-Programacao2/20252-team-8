#include "Usuario.h"
#include <iostream>
#include <string>

// Construtor usado na main - cria usuário novo
Usuario::Usuario(const std::string nome)
    : nome(nome), moedas(100), xp(0), nivel(1), badge("Iniciante") 
{
    // Usuário novo começa com 100 moedas e badge "Iniciante"
}

// Construtor usado pelo Repositorio - carrega usuário existente
Usuario::Usuario(std::string nome, int nivel, int xp, int moedas, std::string badge) 
    : nome(nome), nivel(nivel), xp(xp), moedas(moedas), badge(badge) 
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

// Adiciona XP e verifica se subiu de nível
void Usuario::adicionarXp(int quantidade) {
    if (quantidade > 0) {
        this->xp += quantidade;
        verificarSubidaNivel();
    }
}

// Adiciona moedas
void Usuario::adicionarMoedas(int quantidade) {
    if (quantidade > 0) {
        this->moedas += quantidade;
    }
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
void Usuario::setBadge(std::string badge) {
    if (!badge.empty()) {
        this->badge = badge;
    }
}

//verifica se subiu de nível (100 XP por nível)
void Usuario::verificarSubidaNivel() {
    int xpNecessario = nivel * 100;  //cada nível precisa de mais XP
    
    while (xp >= xpNecessario) {
        xp -= xpNecessario;  //reduz o XP gasto no nível
        nivel++;              //sobe de nível
        moedas += 50;         //recompensa por subir de nível
        
        std::cout << "🎉 Parabéns! Você subiu para o nível " << nivel << "!" << std::endl;
        std::cout << "💰 +50 moedas de recompensa!" << std::endl;
        //atualiza XP necessário para o próximo nível
        xpNecessario = nivel * 100;
        
        //atualiza badge baseado no nível
        if (nivel >= 10) {
            badge = "Mestre";  //nível mestre
        } else if (nivel >= 5) {
            badge = "Avançado";  //nível avançado
        } else if (nivel >= 3) {
            badge = "Intermediário";  //nível intermediário
        }
    }
}
