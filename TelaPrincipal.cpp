#include "TelaPrincipal.h"
#include "Constantes.h"
#include <iostream>

int TelaPrincipal::exibir(Usuario* usuario) {
    int opcao;
    
    do {
        limparTela();
        std::cout << "=== STUDY TRACKER ===" << std::endl;
        std::cout << "Bem-vindo, " << usuario->getNome() << "!" << std::endl;
        std::cout << "Moedas: " << usuario->getMoedas() << std::endl;
        std::cout << "---------------------" << std::endl;
        std::cout << "1. Estudar" << std::endl;
        std::cout << "2. Perfil" << std::endl;
        std::cout << "3. Loja" << std::endl;
        std::cout << "4. Inventario" << std::endl;
        std::cout << "0. Sair" << std::endl;
        std::cout << "Escolha: ";

        std::cin >> opcao;

        // Limpa o erro se usuário digitou algo inválido (letra)
        if (std::cin.fail()) {
            std::cin.clear(); // Limpa o estado de erro
            std::cin.ignore(10000, '\n'); // Descarta entrada inválida
            opcao = -1; // Força repetição
        }

        if (opcao < 0 || opcao > 4) {
            std::cout << "\nOpcao invalida! Pressione ENTER para tentar novamente...";
            std::cin.ignore(10000, '\n');
            std::cin.get();
        }

    } while (opcao < 0 || opcao > 4);

    // Retorna a tela correspondente
    if (opcao == 1) return TELA_ESTUDO;
    if (opcao == 2) return TELA_PERFIL;
    if (opcao == 3) return TELA_LOJA;
    if (opcao == 4) return TELA_INVENTARIO;
    
    return TELA_SAIR; // opcao == 0
}