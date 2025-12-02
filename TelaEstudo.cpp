#include "TelaEstudo.h"
#include <iostream>
#include <iomanip>

int TelaEstudo::mostrarMenuEstudos() {
    mostrarCabecalho("MONITOR DE ESTUDOS");
    std::cout << "1. Iniciar Nova Sessao" << std::endl;
    std::cout << "2. Ver Historico" << std::endl;
    std::cout << "0. Voltar" << std::endl;
    return lerOpcao();
}

int TelaEstudo::mostrarSessaoAtiva(const SessaoEstudo& sessao) {
    limparTela();
    std::cout << "=== ESTUDANDO: " << sessao.getDisciplina() << " ===" << std::endl;
    
    // Converte segundos em HH:MM:SS
    long long totalSeg = sessao.getSegundos();
    int h = totalSeg / 3600;
    int m = (totalSeg % 3600) / 60;
    int s = totalSeg % 60;

    std::cout << "\n          " 
              << std::setfill('0') << std::setw(2) << h << ":"
              << std::setfill('0') << std::setw(2) << m << ":"
              << std::setfill('0') << std::setw(2) << s << "\n" << std::endl;
    std::cout << "Status: ";

    switch (sessao.getEstado()) {
        case SessaoEstudo::rodando: 
            std::cout << "EM ANDAMENTO"; break;
        case SessaoEstudo::pausado: 
            std::cout << "PAUSADO"; break;
        case SessaoEstudo::parado:  
            std::cout << "PARADO"; break;
    }

    std::cout << std::endl;
    std::cout << "-------------------------" << std::endl;
    std::cout << "1. Pausar / Continuar" << std::endl;
    std::cout << "2. Finalizar Sessao" << std::endl;
    
    // Aqui usamos uma leitura simples para não travar o loop do controlador se possível,
    // ou bloqueamos esperando ação do usuário.
    int op;
    std::cin >> op;
    return op;
}

void TelaEstudo::mostrarHistorico(const std::vector<SessaoEstudo>& historico) {
    mostrarCabecalho("HISTORICO DE ESTUDOS");
    
    if (historico.empty()) {
        mostrarMensagem("Nenhuma sessao registrada ainda.");
    } else {
        for (size_t i = 0; i < historico.size(); i++) {
            const auto& s = historico[i];
            std::cout << "[" << (i + 1) << "] " 
                      << s.getDataInicio() << " - " 
                      << s.getDisciplina() << " (" 
                      << s.getSegundos() << "s)" << std::endl;
            
            if (!s.getDescricao().empty()) {
                std::cout << "    Desc: " << s.getDescricao() << std::endl;
            }
        }
    }
    
    std::cout << "\nPressione ENTER para voltar...";
    std::cin.ignore();
    std::cin.get();
}

int TelaEstudo::exibir(Usuario* usuario){
    return mostrarMenuEstudos();
}
