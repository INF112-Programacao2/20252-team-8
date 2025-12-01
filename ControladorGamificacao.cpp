#include "ControladorGamificacao.h"
#include <iostream>

ControladorGamificacao::ControladorGamificacao(int tempo_inicial) {
    // Inicialização completa
    _tempo_de_estudo = tempo_inicial;
    pontos = _tempo_de_estudo * 60; 
    
    // Inicializa novas variáveis
    xp = 0;
    nivel = 1;
    moedas = 0;
    badge = "Iniciante";

    // Define badges como falso inicialmente
    badge1 = false;
    badge2 = false;
    badge3 = false;
    badge4 = false;
    nivel1 = false;
    nivel2 = false;
    nivel3 = false;
    nivel4 = false;

    // Já roda a verificação para destravar o que vc já tem direito
    atualizarStatus();
}

ControladorGamificacao::~ControladorGamificacao() {
}

void ControladorGamificacao::atualizarStatus() {
    // --- Lógica Completa dos Níveis ---
    
    // Nível 1 (1 hora)
    if (_tempo_de_estudo >= 1) {
        badge1 = true;
        if (nivel1 == false) {
            std::cout << ">>> PARABENS! Voce atingiu o Nivel 1 (Calouro) <<<\n";
            nivel1 = true;
            // Recompensa por atingir nível 1
            moedas += 20;
        }
    }

    // Nível 2 (5 horas)
    if (_tempo_de_estudo >= 5) {
        badge2 = true;
        if (nivel2 == false) {
            std::cout << ">>> PARABENS! Voce atingiu o Nivel 2 (Estudante) <<<\n";
            nivel2 = true;
            // Recompensa por atingir nível 2
            moedas += 30;
        }
    }

    // Nível 3 (10 horas)
    if (_tempo_de_estudo >= 10) {
        badge3 = true;
        if (nivel3 == false) {
            std::cout << ">>> PARABENS! Voce atingiu o Nivel 3 (Veterano) <<<\n";
            nivel3 = true;
            // Recompensa por atingir nível 3
            moedas += 50;
        }
    }

    // Nível 4 (20 horas)
    if (_tempo_de_estudo >= 20) {
        badge4 = true;
        if (nivel4 == false) {
            std::cout << ">>> PARABENS! Voce atingiu o Nivel 4 (Formando) <<<\n";
            nivel4 = true;
            // Recompensa por atingir nível 4
            moedas += 100;
        }
    }
    
    // Atualiza pontos baseados no tempo
    pontos = _tempo_de_estudo * 60 + xp;
    
    // Verifica se subiu de nível por XP
    verificarSubidaNivel();
}

void ControladorGamificacao::mostrarBadges() {
    std::cout << "\n------- SEUS STATUS -------\n";
    std::cout << "Tempo Total: " << _tempo_de_estudo << " horas\n";
    std::cout << "Pontos Atuais: " << pontos << "\n";
    std::cout << "XP: " << xp << "\n";
    std::cout << "Nivel: " << nivel << "\n";
    std::cout << "Moedas: " << moedas << "\n";
    std::cout << "Badge Atual: " << badge << "\n";
    std::cout << "---------------------------\n";

    // Nivel 1
    std::cout << "Nivel 1 (Calouro):  ";
    if (badge1 == true) {
        std::cout << "[CONCLUIDO]\n";
    } else {
        std::cout << "[BLOQUEADO] (necessario: 1 hora)\n";
    }

    // Nivel 2
    std::cout << "Nivel 2 (Estudante): ";
    if (badge2 == true) {
        std::cout << "[CONCLUIDO]\n";
    } else {
        std::cout << "[BLOQUEADO] (necessario: 5 horas)\n";
    }

    // Nivel 3
    std::cout << "Nivel 3 (Veterano):  ";
    if (badge3 == true) {
        std::cout << "[CONCLUIDO]\n";
    } else {
        std::cout << "[BLOQUEADO] (necessario: 10 horas)\n";
    }

    // Nivel 4
    std::cout << "Nivel 4 (Formando):  ";
    if (badge4 == true) {
        std::cout << "[CONCLUIDO]\n";
    } else {
        std::cout << "[BLOQUEADO] (necessario: 20 horas)\n";
    }

    std::cout << "---------------------------\n";
}

int ControladorGamificacao::getPontos() {
    return pontos;
}

// Verifica se subiu de nível (100 XP por nível)
void ControladorGamificacao::verificarSubidaNivel() {
    // XP necessário para o próximo nível
    int xpNecessario = nivel * 100;
    
    bool subiu = false;

    // Enquanto tiver XP suficiente para subir de nível
    while (xp >= xpNecessario) {
        xp -= xpNecessario;  // Reduz o XP gasto no nível
        nivel++;              // Sobe de nível
        moedas += 50;         // Recompensa por subir de nível
        
        std::cout << "\n>>> PARABENS! Voce subiu para o nivel " << nivel << "! <<<\n";
        std::cout << ">>> +50 moedas de recompensa! <<<\n";
        
        // Atualiza badge baseado no nível
        std::string badgeAntiga = badge;
        
        if (nivel >= 15) {
            badge = "Lenda";
        } else if (nivel >= 10) {
            badge = "Mestre";
        } else if (nivel >= 7) {
            badge = "Avançado";
        } else if (nivel >= 4) {
            badge = "Intermediário";
        } else if (nivel >= 2) {
            badge = "Iniciante+";
        }
        
        // Se mudou de badge, mostra mensagem
        if (badge != badgeAntiga) {
            std::cout << ">>> NOVA BADGE DESBLOQUEADA: " << badge << " <<<\n";
        }
        
        // Recalcula XP necessário para o próximo nível
        xpNecessario = nivel * 100;
        subiu = true;
    }
    
    // Atualiza pontos
    pontos = _tempo_de_estudo * 60 + xp;
}

// Getters implementação
int ControladorGamificacao::getXp() const {
    return xp;
}

int ControladorGamificacao::getNivel() const {
    return nivel;
}

int ControladorGamificacao::getMoedas() const {
    return moedas;
}

std::string ControladorGamificacao::getBadge() const {
    return badge;
}

// Adiciona XP
void ControladorGamificacao::adicionarXp(int quantidade) {
    if (quantidade > 0) {
        xp += quantidade;
        std::cout << ">>> +" << quantidade << " XP adicionado! <<<\n";
        verificarSubidaNivel(); // Verifica se subiu de nível
    }
}

// Adiciona tempo de estudo (em minutos)
void ControladorGamificacao::adicionarTempoEstudo(int minutos) {
    if (minutos > 0) {
        // Converte minutos para horas (aproximado)
        float horas = minutos / 60.0f;
        _tempo_de_estudo += static_cast<int>(horas);
        
        // Adiciona XP baseado no tempo (1 minuto = 1 XP)
        adicionarXp(minutos);
        
        // Adiciona pontos (1 hora = 60 pontos)
        pontos += static_cast<int>(horas * 60);
        
        std::cout << ">>> +" << minutos << " minutos de estudo registrados! <<<\n";
        atualizarStatus(); // Atualiza badges
    }
}