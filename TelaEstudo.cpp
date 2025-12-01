#include "TelaEstudo.h"
#include "ControladorEstudo.h"
#include "Constantes.h"
#include "SessaoEstudo.h"
#include "RepositorioEstudos.h"
#include <iostream>
#include <limits>

telaEstudo::telaEstudo(ControladorEstudo& controlador) {
}

int telaEstudo::exibir(Usuario* usuario) {
    ControladorEstudo ctrl(nullptr);

    while (true) {
        limparTela();
        std::cout << "=== MODO ESTUDO ===" << std::endl;
        std::cout << "1. Iniciar Nova Sessao" << std::endl;
        std::cout << "2. Ver Historico e Progresso" << std::endl;
        std::cout << "0. Voltar ao Menu Principal" << std::endl;
        std::cout << "Escolha: ";
        
        int op;
        std::cin >> op;
        
        // Tratamento de erro se digitar letra
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            op = -1; 
        }

        if (op == 0) {
            return TELA_PRINCIPAL;
        }
        
        if (op == 1) {
            // Inicia a sessão
            ctrl.iniciarSessao();
            
            bool sessaoRodando = true;
            while (sessaoRodando) {
                // Verifica se realmente iniciou (pode ter dado erro)
                if (!ctrl.temSessaoAtiva()) break;

                std::cout << "\n--- Sessao em Andamento ---" << std::endl;
                std::cout << "1. Pausar" << std::endl;
                std::cout << "2. Continuar" << std::endl;
                std::cout << "3. Finalizar" << std::endl;
                std::cout << "4. Cancelar" << std::endl;
                std::cout << "Opcao: ";
                
                int opSessao;
                std::cin >> opSessao;

                if (opSessao == 1) ctrl.pausarSessao();
                else if (opSessao == 2) ctrl.continuarSessao();
                else if (opSessao == 3) {
                    ctrl.finalizarSessao(usuario);
                    sessaoRodando = false;
                    aguardarEnter();
                }
                else if (opSessao == 4) {
                    ctrl.cancelarSessao();
                    sessaoRodando = false;
                    aguardarEnter();
                }
                else {
                    std::cout << "Opcao invalida." << std::endl;
                }
            }
        }
        else if (op == 2) {
            ctrl.mostrarHistoricoCompleto(usuario);
            aguardarEnter();
        }
        else {
            std::cout << "Opcao invalida!" << std::endl;
            aguardarEnter();
        }
    }
}