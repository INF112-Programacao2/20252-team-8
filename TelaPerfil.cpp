#include "TelaPerfil.h"
#include "ControladorPerfil.h"
#include "Constantes.h"

#include <iostream>

int telaPerfil::exibir(Usuario* usuario) {
    limparTela();
    std::cout << "=== MEU PERFIL ===" << std::endl;
    std::cout << "Nome: " << usuario->getNome() << std::endl;
    std::cout << "------------------" << std::endl;
    std::cout << "1. Alterar Nome" << std::endl;
    std::cout << "0. Voltar" << std::endl;
    std::cout << "Escolha: ";

    int opcao;
    std::cin >> opcao;

    if (opcao == 1) {
        std::string novo;
        std::cout << "Digite o novo nome: ";
        std::cin >> novo;
        
        ControladorPerfil ctrl;
        ctrl.alterarNome(usuario, novo);
        
        std::cout << "Nome alterado!" << std::endl;
        aguardarEnter();
        return TELA_PERFIL;
    }
    
    return TELA_PRINCIPAL;
}