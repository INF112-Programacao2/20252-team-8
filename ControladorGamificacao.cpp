#include "ControladorGamificacao.h"
#include <iostream>

ControladorGamificacao::ControladorGamificacao(int tempo_inicial) {
    // Inicialização simples dentro das chaves
    _tempo_de_estudo = tempo_inicial;
    pontos = _tempo_de_estudo * 60; 

    // Define tudo como falso inicialmente
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
        }
    }

    // Nível 2 (5 horas)
    if (_tempo_de_estudo >= 5) {
        badge2 = true;
        if (nivel2 == false) {
            std::cout << ">>> PARABENS! Voce atingiu o Nivel 2 (Estudante) <<<\n";
            nivel2 = true;
        }
    }

    // Nível 3 (10 horas)
    if (_tempo_de_estudo >= 10) {
        badge3 = true;
        if (nivel3 == false) {
            std::cout << ">>> PARABENS! Voce atingiu o Nivel 3 (Veterano) <<<\n";
            nivel3 = true;
        }
    }

    // Nível 4 (20 horas)
    if (_tempo_de_estudo >= 20) {
        badge4 = true;
        if (nivel4 == false) {
            std::cout << ">>> PARABENS! Voce atingiu o Nivel 4 (Formando) <<<\n";
            nivel4 = true;
        }
    }
}

void ControladorGamificacao::mostrarBadges() {
    std::cout << "\n------- SEUS STATUS -------\n";
    std::cout << "Tempo Total: " << _tempo_de_estudo << " horas\n";
    std::cout << "Pontos Atuais: " << pontos << "\n";
    std::cout << "---------------------------\n";

    // Nivel 1
    std::cout << "Nivel 1 (Calouro):  ";
    if (badge1 == true) {
        std::cout << "[CONCLUIDO]\n";
    } else {
        std::cout << "[BLOQUEADO]\n";
    }

    // Nivel 2
    std::cout << "Nivel 2 (Estudante): ";
    if (badge2 == true) {
        std::cout << "[CONCLUIDO]\n";
    } else {
        std::cout << "[BLOQUEADO]\n";
    }

    // Nivel 3
    std::cout << "Nivel 3 (Veterano):  ";
    if (badge3 == true) {
        std::cout << "[CONCLUIDO]\n";
    } else {
        std::cout << "[BLOQUEADO]\n";
    }

    // Nivel 4
    std::cout << "Nivel 4 (Formando):  ";
    if (badge4 == true) {
        std::cout << "[CONCLUIDO]\n";
    } else {
        std::cout << "[BLOQUEADO]\n";
    }

    std::cout << "---------------------------\n";
}

int ControladorGamificacao::getPontos() {
    return pontos;
}