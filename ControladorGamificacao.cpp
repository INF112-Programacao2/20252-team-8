#include "ControladorGamificacao.h"
#include <iostream>
#include <cmath> 

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
    // 1. Recalcula o nível baseado no XP atual
    int xpTotal = usuarioAtual->getXp();
    int nivelCalculado = xpTotal / XP_POR_NIVEL; 
    
    // 2. Pega o nível que estava salvo antes
    int nivelNoArquivo = repositorio->getNivel();

    if (nivelCalculado > nivelNoArquivo) {
        
        std::string nomeBadgeNova = calcularNomeBadge(nivelCalculado); // Ex: "Estudante"
        int idBadgeNova = calcularIdBadge(nivelCalculado);

        usuarioAtual->setNivel(nivelCalculado);
        usuarioAtual->setBadge(nomeBadgeNova); 

        if (repositorio) {
            repositorio->setNivel(nivelCalculado);
            repositorio->setBadge(idBadgeNova);
        }

        std::cout << "\n=========================================\n";
        std::cout << "   PARABENS! LEVEL UP!\n";
        std::cout << "=========================================\n";
        std::cout << "Voce alcancou o Nivel " << nivelCalculado << "!\n";

        std::cout << "Nova Badge: " << nomeBadgeNova << "\n"; 
        
        std::cout << "=========================================\n";

        int niveisSubidos = nivelCalculado - nivelNoArquivo;
        int moedasGanhas = niveisSubidos * RECOMPENSA_MOEDAS;
        adicionarMoedas(moedasGanhas);
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
    if (usuarioAtual) {
        return usuarioAtual->getNivel(); 
    }
    return 0;
}

int ControladorGamificacao::getMoedas() const {
    return usuarioAtual ? usuarioAtual->getMoedas() : 0;
}

std::string ControladorGamificacao::getBadge() const {
    return usuarioAtual ? usuarioAtual->getBadge() : "";
}

void ControladorGamificacao::executar() {
    if (usuarioAtual != nullptr) {
        
        int nivelReal = getNivel(); 
        
        std::string badgeEsperada = calcularNomeBadge(nivelReal);

        if (usuarioAtual->getBadge() != badgeEsperada) {
            std::cout << "[Debug] Corrigindo Badge antiga (" << usuarioAtual->getBadge() 
                      << ") para nova (" << badgeEsperada << ")...\n";
            
            usuarioAtual->setBadge(badgeEsperada);
            
            if (repositorio) {
                repositorio->setBadge(calcularIdBadge(nivelReal));
            }
        }

        tela.mostrarPerfil(usuarioAtual);
    }
}