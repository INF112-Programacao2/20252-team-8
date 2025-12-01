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
    // Calculamos o nível real baseado no XP total acumulado
    // Ex: 250 XP / 100 = Nível 2
    int xpTotal = usuarioAtual->getXp();
    int nivelCalculado = xpTotal / XP_POR_NIVEL;
    
    // O nível salvo no objeto Usuario (usuarioAtual->getNivel()) 
    // pode estar desatualizado pois não temos 'setNivel'. 
    // Então comparamos com o nível que está salvo no ARQUIVO via repositorio.
    int nivelNoArquivo = repositorio->getNivel();

    if (nivelCalculado > nivelNoArquivo) {
        // --- LEVEL UP! ---
        int niveisSubidos = nivelCalculado - nivelNoArquivo;
        
        std::cout << "\n=========================================\n";
        std::cout << "   PARABENS! Voce subiu para o Nivel " << nivelCalculado << "!\n";
        std::cout << "=========================================\n";

        // Recompensa em Moedas
        int moedasGanhas = niveisSubidos * RECOMPENSA_MOEDAS;
        adicionarMoedas(moedasGanhas);

        // Atualiza Badge na memória e no arquivo
        std::string nomeBadge = calcularNomeBadge(nivelCalculado);
        usuarioAtual->setBadge(nomeBadge); // Usuario.h permite setBadge

        // --- SALVANDO NO ARQUIVO ---
        // Como não podemos dar 'setNivel' no Usuario RAM, salvamos direto no arquivo
        repositorio->setNivel(nivelCalculado);
        
        // Salvamos a badge usando o índice (assumindo que repo usa int para badge)
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
        // O nível já é salvo automaticamente no verificarEvolucao
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
    // Mapeia o nível para o ID que o RepositorioGamificacao.cpp espera (switch case)
    if (nivel >= 20) return 4; // Formando/Lenda
    if (nivel >= 10) return 3; // Veterano
    if (nivel >= 5)  return 2; // Estudante
    if (nivel >= 1)  return 1; // Calouro
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
    // TRUQUE: Como não podemos atualizar o nível dentro do objeto Usuario (falta setNivel),
    // nós calculamos o nível "real" dividindo o XP total por 100.
    // Assim a TelaLoja sempre recebe o nível correto, mesmo que o objeto Usuario esteja "atrasado".
    if (!usuarioAtual) return 0;
    return usuarioAtual->getXp() / XP_POR_NIVEL;
}

int ControladorGamificacao::getMoedas() const {
    return usuarioAtual ? usuarioAtual->getMoedas() : 0;
}

std::string ControladorGamificacao::getBadge() const {
    return usuarioAtual ? usuarioAtual->getBadge() : "";
}