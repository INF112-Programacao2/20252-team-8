#include "TelaPrincipal.h"
#include "Constantes.h"
#include <iostream>

int telaPrincipal::exibir(Usuario* usuario) {
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

    int opcao;
    std::cin >> opcao;

    if (opcao == 1) return TELA_ESTUDO;
    if (opcao == 2) return TELA_PERFIL;
    if (opcao == 3) return TELA_LOJA;
    if (opcao == 4) return TELA_INVENTARIO;
    if (opcao == 0) return TELA_SAIR;
    
    return TELA_PRINCIPAL;
}