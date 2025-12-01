#include "TelaBase.h"
#include <iostream>
#include <limits> // Necessário para limpar o buffer do cin
#include <cstdlib> // Necessário para system()

void TelaBase::limparTela() {
    // Verifica o Sistema Operacional para usar o comando certo
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void TelaBase::mostrarCabecalho(std::string titulo) {
    limparTela();
    std::cout << "========================================" << std::endl;
    std::cout << "       " << titulo << "       " << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << std::endl;
}

void TelaBase::mostrarMensagem(std::string mensagem) {
    std::cout << ">> " << mensagem << std::endl;
}

void TelaBase::mostrarErro(std::string erro) {
    std::cerr << "[ERRO] " << erro << std::endl;
    esperarEnter(); // Pausa para o usuário ler o erro
}

void TelaBase::esperarEnter() {
    std::cout << "\nPressione ENTER para continuar...";
    // Se houver lixo no buffer, ignora. Se não, espera input.
    if (std::cin.peek() == '\n') std::cin.ignore();
    std::cin.get();
<<<<<<< HEAD
}

int TelaBase::lerOpcao() {
    int opcao;
    std::cout << ">> Escolha uma opcao: ";
    
    // Tenta ler um inteiro
    while (!(std::cin >> opcao)) {
        // Se falhar (ex: usuário digitou "a"), entra aqui:
        std::cin.clear(); // Limpa a flag de erro do cin
        
        // Ignora o restante da linha inválida no buffer
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        std::cout << "Entrada invalida! Digite apenas numeros: ";
    }
    
    // Limpa o buffer após ler o número (para não pular o próximo getline)
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    return opcao;
=======
>>>>>>> 6f0e72ab77fab84b7a3039e748b26fb8cc2d22e7
}

int TelaBase::lerOpcao() {
    int opcao;
    std::cout << ">> Escolha uma opcao: ";
    
    // Tenta ler um inteiro
    while (!(std::cin >> opcao)) {
        // Se falhar (ex: usuário digitou "a"), entra aqui:
        std::cin.clear(); // Limpa a flag de erro do cin
        
        // Ignora o restante da linha inválida no buffer
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        std::cout << "Entrada invalida! Digite apenas numeros: ";
    }
    
    // Limpa o buffer após ler o número (para não pular o próximo getline)
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    return opcao;
}