#include "tocarmusica.h" // Inclui a classe "neta" (que já inclui o resto)
#include <iostream>
#include <string>
// A biblioteca <limits> não é mais necessária

int main() {
    int horasDeEstudo = 0;

    // --- 1. Entrada de Horas de Estudo ---
    std::cout << "--- BEM-VINDO AO SISTEMA DE FOCO ---" << std::endl;
    std::cout << "Por favor, insira o total de horas de estudo que voce acumulou: ";


    std::cout << "Digite as horas: ";
    std::cin >> horasDeEstudo;

    while (horasDeEstudo < 0) {
        std::cout << "Entrada invalida. Por favor, digite um numero positivo: ";
        std::cin >> horasDeEstudo;
    }


    // --- 2. Criação do Objeto Principal ---
    TocarMusicas meuSistema(horasDeEstudo);

    // --- 3. Feedback Inicial (Métodos da classe-avó) ---
    std::cout << "\n--- PROCESSANDO SUAS RECOMPENSAS ---" << std::endl;
    meuSistema.Badges();
    meuSistema.ComunicarSubidaDeNivel();
    meuSistema.ComunicarBadges();
    std::cout << "\nVoce acumulou um total de " << meuSistema.getPontos() << " pontos!" << std::endl;

    // --- 4. Menu Principal Interativo ---
    int escolhaMenu = 0;
    while (true) {
        std::cout << "\n--- MENU PRINCIPAL ---" << std::endl;
        std::cout << "1. Ir para a Loja de Musicas" << std::endl;
        std::cout << "2. Ir para o Player de Musicas" << std::endl;
        std::cout << "3. Ver meus Badges e Pontos" << std::endl;
        std::cout << "4. Sair" << std::endl;
        std::cout << "Escolha uma opcao: ";

        // Validação da escolha do menu (também simplificada)
        if (!(std::cin >> escolhaMenu)) {
            std::cout << "Entrada invalida. Tente novamente." << std::endl;
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            continue; // Volta ao início do loop
        }

        // Lógica do Menu com if/else
        if (escolhaMenu == 1) {
            meuSistema.loja();
        } 
        else if (escolhaMenu == 2) {
            meuSistema.mostrarMenuMusicas();
        } 
        else if (escolhaMenu == 3) {
            meuSistema.ComunicarBadges();
            std::cout << "Pontos atuais: " << meuSistema.getPontos() << std::endl;
        } 
        else if (escolhaMenu == 4) {
            std::cout << "Obrigado por usar o sistema. Ate mais!" << std::endl;
            break; // Quebra o loop 'while(true)' para sair
        } 
        else {
            std::cout << "Opcao invalida. Tente novamente." << std::endl;
        }
    }

    return 0; // Encerra o programa
}    