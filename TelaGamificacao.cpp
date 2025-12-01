#include "TelaGamificacao.h"
#include <iostream>
#include <iomanip> // Para formatação se precisar

void TelaGamificacao::mostrarPerfil(Usuario* usuario) {
    if (!usuario) return;

    limparTela(); // Método da TelaBase
    mostrarCabecalho("PERFIL DO ESTUDANTE"); // Método da TelaBase

    std::cout << "Nome:   " << usuario->getNome() << std::endl;
    std::cout << "Nivel:  " << usuario->getNivel() << std::endl;
    std::cout << "Badge:  [" << usuario->getBadge() << "]" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "XP:     " << usuario->getXp() << " pts" << std::endl;
    std::cout << "Moedas: " << usuario->getMoedas() << " $" << std::endl;
    
    // --- BARRA DE PROGRESSO DINÂMICA ---
    // Calcula quanto falta para o próximo nível (0 a 99)
    int xpNesteNivel = usuario->getXp() % 100; 
    
    // Configura tamanho da barra
    int tamanhoBarra = 20; 
    int qtdPreenchida = (xpNesteNivel * tamanhoBarra) / 100;

    std::cout << "\nProximo Nivel:" << std::endl;
    std::cout << "[";
    
    // Loop para desenhar a barra
    for (int i = 0; i < tamanhoBarra; i++) {
        if (i < qtdPreenchida) 
            std::cout << "|"; // Parte cheia
        else 
            std::cout << " "; // Parte vazia
    }
    
    std::cout << "] " << xpNesteNivel << "%" << std::endl;
    // -----------------------------------

    std::cout << "\n----------------------------------------" << std::endl;
    
    // CORRIGIDO: Usa o método correto da TelaBase
    esperarEnter();
}

void TelaGamificacao::mostrarGanhoRecursos(int xp, int moedas) {
    // Exibe uma mensagem curta sem limpar a tela (feedback rápido)
    std::cout << "\n>>> [RECOMPENSA] ";
    if (xp > 0) std::cout << "+" << xp << " XP ";
    if (moedas > 0) std::cout << "| +" << moedas << " Moedas ";
    std::cout << "<<<" << std::endl;
}

void TelaGamificacao::mostrarLevelUp(int novoNivel, int moedasGanhas, const std::string& novaBadge) {
    std::cout << "\n";
    std::cout << "=========================================" << std::endl;
    std::cout << "         LEVEL UP! NIVEL " << novoNivel << "!" << std::endl;
    std::cout << "=========================================" << std::endl;
    std::cout << "Recompensa: +" << moedasGanhas << " Moedas" << std::endl;
    
    if (!novaBadge.empty()) {
        std::cout << "NOVA BADGE DESBLOQUEADA: " << novaBadge << std::endl;
    }
    std::cout << "=========================================\n" << std::endl;
    
    // CORRIGIDO: Usa o método correto da TelaBase
    esperarEnter(); 
}