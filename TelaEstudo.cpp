#include "TelaEstudo.h"
#include "ControladorEstudo.h"
#include "Constantes.h"
#include "SessaoEstudo.h"
#include <iostream>

int telaEstudo::exibir(Usuario* usuario) {
    limparTela();
    std::cout << "=== ESTUDO ===" << std::endl;
    std::cout << "1. Iniciar Sessao" << std::endl;
    std::cout << "0. Voltar" << std::endl;
    
    int op;
    std::cin >> op;
    
    if (op == 1) {
        SessaoEstudo sessao(0, 0, "Geral", "Tag", "Desc");
        sessao.iniciar();
        std::cout << "Estudando... Digite algo para parar: ";
        int stop;
        std::cin >> stop;
        
        ControladorEstudo ctrl;
        ctrl.salvarSessao(usuario, sessao);
        
        std::cout << "Salvo!" << std::endl;
        aguardarEnter();
    }
    
    return TELA_PRINCIPAL;
}