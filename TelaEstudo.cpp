#include "TelaEstudo.h"
#include "ControladorEstudo.h"
#include "Constantes.h"
#include "SessaoEstudo.h"
#include "RepositorioEstudos.h"
#include <iostream>


std::string formatarTempo(long long int totalSegundos) {
    int horas = totalSegundos / 3600;
    int minutos = (totalSegundos % 3600) / 60;
    int segundos = totalSegundos % 60;
    
    char buffer[50];
    sprintf(buffer, "%02dh %02dm %02ds", horas, minutos, segundos);
    return std::string(buffer);
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
        
        if (op == 0) {
            return TELA_PRINCIPAL;
        }
        
        if (op == 1) {
            // Inicia a sessão
            ctrl.iniciarSessao(0);
            
            // Simulação de espera
            std::cout << "Pressione ENTER para finalizar a sessao...";
            std::cin.ignore(); 
            std::cin.get();
            
            // Finaliza
            ctrl.finalizarSessao(usuario);
            
            // Pausa para o usuário ler o resumo
            std::cout << "\nPressione ENTER para continuar...";
            std::cin.get();
        }
        else if (op == 2) {
            RepositorioEstudos& repo = ctrl.recuperarHistorico(usuario);
            
            mostrarProgressoEstudo(&repo);
            
            std::cout << "Pressione ENTER para voltar...";
            std::cin.ignore();
            std::cin.get();
        }
        else {
            std::cout << "Opcao invalida!" << std::endl;
        }
    }
}

void telaEstudo::mostrarProgressoEstudo(RepositorioEstudos* repositorio){
    limparTela();

    std::cout << "=== PROGRESSO DE ESTUDO ===" << std::endl;
    std::cout << "Usuario: " << repositorio->getIdUsuario() << std::endl;
    std::cout << "Total de Sessoes: " << repositorio->getQuantidade() << std::endl;
    std::cout << "----------------------------" << std::endl;

    int qtd = repositorio->getQuantidade();

    if (qtd == 0) {
        std::cout << "Nenhuma sessao registrada ainda." << std::endl;
    } else {
        // Loop percorrendo o array do repositório
        for (int i = 0; i < qtd; i++) {
            // Pede ao repositório o ponteiro para a sessão 'i'
            SessaoEstudo* sessao = repositorio->getSessao(i);
            
            if (sessao != nullptr) {
                std::cout << "Sessao " << (i + 1) << ":" << std::endl;
                std::cout << "  Disciplina: " << sessao->getDisciplina() << std::endl;
                std::cout << "  Duracao:    " << formatarTempo(sessao->getSegundos()) << std::endl;
                
                // Mostra data/hora se não estiverem vazias
                if (!sessao->getDataInicio().empty()) {
                    std::cout << "  Data:       " << sessao->getDataInicio() << std::endl;
                }
                std::cout << "----------------------------" << std::endl;
            }
        }
    }

    // Atualiza e mostra o total
    repositorio->calcularTempoTotal();
    std::cout << "TEMPO TOTAL ACUMULADO: " << formatarTempo(repositorio->getTempoTotal()) << std::endl;
    std::cout << "\n";
}