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
    // Define a meta
    int nivelAtual = (usuario->getNivel() > 0) ? usuario->getNivel() : 1; // Proteção contra nível 0
    int metaDoNivel = nivelAtual * 10;

    // Pega o XP atual
    int xpAtual = usuario->getXp();

    // Configura tamanho da barra
    int tamanhoBarra = 20; 

    // 4. Regra de 3 para saber quantos tracinhos pintar
    // Proteção: Se meta for 0, evita divisão por zero
    int qtdPreenchida = 0;
    if (metaDoNivel > 0) {
        qtdPreenchida = (xpAtual * tamanhoBarra) / metaDoNivel;
    }
    
    // Garante que a barra não estoure o visual (trava em 20)
    if (qtdPreenchida > tamanhoBarra) qtdPreenchida = tamanhoBarra;

    // 5. Calcula porcentagem para texto (0 a 100%)
    int porcentagemTexto = 0;

    if (metaDoNivel > 0) {
        porcentagemTexto = (xpAtual * 100) / metaDoNivel;
    }

    std::cout << "\nProximo Nivel (Meta: " << metaDoNivel << " XP):" << std::endl;
    std::cout << "[";
    
    // Loop para desenhar a barra
    for (int i = 0; i < tamanhoBarra; i++) {
        if (i < qtdPreenchida) 
            std::cout << "|"; // Parte cheia
        else 
            std::cout << " "; // Parte vazia
    }
    
    std::cout << "] " << porcentagemTexto << "%" << std::endl;
    // -----------------------------------

    std::cout << "\n----------------------------------------" << std::endl;
    
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
    
    esperarEnter(); 
}