#include "TelaEstudo.h"
#include <iostream>

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

    std::cout << "\n      " << h << ":" << m << ":" << s << "\n" << std::endl;
    std::cout << "Status: " << (int)sessao.getEstado() << std::endl; // Pode melhorar convertendo enum pra string
    
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
    
    for (const auto& s : historico) {
        std::cout << "Data: " << s.getDataInicio() 
                  << " | " << s.getDisciplina() 
                  << " | " << s.getSegundos() << "s" << std::endl;
    }
    
    std::cout << "\nPressione ENTER para voltar...";
    std::cin.ignore();
    std::cin.get();
}

int TelaEstudo::exibir(Usuario* usuario){
    
}
