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
    
    // Barra de progresso visual simples (simulação)
    std::cout << "\nProgresso Geral:" << std::endl;
    std::cout << "[|||||||       ] (Em desenvolvimento)" << std::endl;

    std::cout << "\n----------------------------------------" << std::endl;
    
    // CORRIGIDO: Agora chama o método exato que existe na sua TelaBase
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
    
    // CORRIGIDO: Usa esperarEnter() da TelaBase para pausar
    esperarEnter(); 
}