#include "ControladorGamificacao.h"
#include <iostream>
#include <cmath> // Para floor

ControladorGamificacao::ControladorGamificacao(Usuario* usuario, RepositorioGamificacao* repo)
    : usuarioAtual(usuario), repositorio(repo) {
}

// --- Lógica Principal ---

void ControladorGamificacao::adicionarXP(int quantidade) {
    if (!usuarioAtual || quantidade <= 0) return;

    // 1. Atualiza memória RAM (Usuario.h permite adicionar)
    usuarioAtual->adicionarXp(quantidade);
    
    // 2. Atualiza Arquivo imediatamente (Persistência)
    if (repositorio) {
        repositorio->setPontos(usuarioAtual->getXp());
    }

    std::cout << ">>> +" << quantidade << " XP ganho!\n";
    
    // 3. Verifica se isso causou um Level Up
    verificarEvolucao();
}

void ControladorGamificacao::verificarEvolucao() {
    // Calculamos o nível real baseado no XP total acumulado / 100
    int xpTotal = usuarioAtual->getXp();
    
    // O #define XP_POR_NIVEL é trocado por 100 aqui
    int nivelCalculado = xpTotal / XP_POR_NIVEL;
    
    // Compara com o nível salvo no ARQUIVO
    int nivelNoArquivo = repositorio->getNivel();

    if (nivelCalculado > nivelNoArquivo) {
        // --- LEVEL UP! ---
        int niveisSubidos = nivelCalculado - nivelNoArquivo;
        
        std::cout << "\n=========================================\n";
        std::cout << "   PARABENS! Voce subiu para o Nivel " << nivelCalculado << "!\n";
        std::cout << "=========================================\n";

        // Recompensa em Moedas (usa o #define RECOMPENSA_MOEDAS)
        int moedasGanhas = niveisSubidos * RECOMPENSA_MOEDAS;
        adicionarMoedas(moedasGanhas);

        // Atualiza Badge na memória
        std::string nomeBadge = calcularNomeBadge(nivelCalculado);
        usuarioAtual->setBadge(nomeBadge); 

        // --- SALVANDO NO ARQUIVO ---
        // Salva direto no repositorio pois Usuario não tem setNivel
        repositorio->setNivel(nivelCalculado);
        
        // Salva badge no repositorio
        repositorio->setBadge(calcularIdBadge(nivelCalculado));
    }
}

void ControladorGamificacao::adicionarMoedas(int quantidade) {
    if (!usuarioAtual) return;

    // Atualiza RAM
    usuarioAtual->adicionarMoedas(quantidade);
    
    // Atualiza Arquivo
    if (repositorio) {
        repositorio->setMoedas(usuarioAtual->getMoedas());
    }
    
    if (quantidade > 0) {
        std::cout << ">>> +" << quantidade << " Moedas!\n";
    }
}

void ControladorGamificacao::salvarTudo() {
    // Método de segurança para garantir sincronia
    if (repositorio && usuarioAtual) {
        repositorio->setPontos(usuarioAtual->getXp());
        repositorio->setMoedas(usuarioAtual->getMoedas());
    }
}

// --- Helpers de Badge ---

std::string ControladorGamificacao::calcularNomeBadge(int nivel) {
    if (nivel >= 20) return "Lenda";
    if (nivel >= 10) return "Veterano";
    if (nivel >= 5)  return "Estudante";
    if (nivel >= 2)  return "Calouro";
    return "Iniciante";
}

int ControladorGamificacao::calcularIdBadge(int nivel) {
    // Mapeia o nível para o ID que o RepositorioGamificacao.cpp espera
    if (nivel >= 20) return 4; 
    if (nivel >= 10) return 3; 
    if (nivel >= 5)  return 2; 
    if (nivel >= 1)  return 1; 
    return 0;
}

// --- Getters Inteligentes ---

Usuario* ControladorGamificacao::getUsuario() const {
    return usuarioAtual;
}

int ControladorGamificacao::getXP() const {
    return usuarioAtual ? usuarioAtual->getXp() : 0;
}

int ControladorGamificacao::getNivel() const {
    // Calcula nível baseado no XP total dividido por 100 (definido no header)
    if (!usuarioAtual) return 0;
    return usuarioAtual->getXp() / XP_POR_NIVEL;
}

int ControladorGamificacao::getMoedas() const {
    return usuarioAtual ? usuarioAtual->getMoedas() : 0;
}

std::string ControladorGamificacao::getBadge() const {
    return usuarioAtual ? usuarioAtual->getBadge() : "";
}