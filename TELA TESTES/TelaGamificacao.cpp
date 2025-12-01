#include "TelaGamificacao.h"
#include <iostream>

int TelaGamificacao::mostrarPerfil(const Usuario& usuario) {
    mostrarCabecalho("MEU PERFIL");

    // Exibe os dados formatados
    std::cout << "Nome:   " << usuario.getNome() << std::endl;
    std::cout << "Nivel:  " << usuario.getNivel() << std::endl;
    std::cout << "XP:     " << usuario.getXp() << " pts" << std::endl;
    std::cout << "Moedas: " << usuario.getMoedas() << " $" << std::endl;
    std::cout << "Badge:  [" << usuario.getBadge() << "]" << std::endl;
    
    // Barra de progresso visual (Opcional, mas legal)
    std::cout << "\nProgresso p/ proximo nivel:" << std::endl;
    std::cout << "[|||||||       ] 45%" << std::endl; // (Logica ficticia aqui)

    std::cout << "\n----------------------------------------" << std::endl;
    std::cout << "0. Voltar ao Menu Principal" << std::endl;

    return lerOpcao();
}