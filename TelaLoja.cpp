#include "TelaLoja.h"
#include <iostream>

int TelaLoja::mostrarVitrine(const std::vector<Item*>& itens, const Usuario& usuario) {
    mostrarCabecalho("LOJA DE ITENS");

    // Mostra o saldo para o usuário saber se pode comprar
    std::cout << "SEU SALDO: " << usuario.getMoedas() << " moedas" << std::endl;
    std::cout << "----------------------------------------" << std::endl;

    if (itens.empty()) {
        std::cout << "(Loja fechada ou sem estoque)" << std::endl;
    } else {
        for (size_t i = 0; i < itens.size(); i++) {
            Item* item = itens[i];
            
            // Ex: [1] Bone (50 moedas) - Cosmetico
            std::cout << "[" << (i + 1) << "] " 
                      << item->getNome() 
                      << " (" << item->getValor() << "$) - " 
                      << item->getTipo() << std::endl;
        }
    }

    std::cout << "\nDigite o numero do item para COMPRAR" << std::endl;
    std::cout << "Ou 0 para Sair" << std::endl;

    return lerOpcao();
}

int TelaLoja::exibir(Usuario* usuario){
    return 1;
}