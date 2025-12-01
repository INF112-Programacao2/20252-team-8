#include "TelaInventario.h"
#include <iostream>
#include <iomanip> // Para formatar o output se quiser

int TelaInventario::mostrarInventario(const std::vector<Item*>& itens) {
    // 1. Usa o cabeçalho padrão da TelaBase
    mostrarCabecalho("MEU INVENTARIO");

    // 2. Exibe os itens
    if (itens.empty()) {
        mostrarMensagem("Sua mochila esta vazia. Visite a Loja para comprar itens!");
    } 
    else {
        std::cout << "--- Seus Itens ---" << std::endl;
        
        // Loop para listar ponteiros (Item*)
        for (size_t i = 0; i < itens.size(); i++) {
            // Exemplo de output: "[1] Bone Vermelho (Cosmetico)"
            // Usamos -> pois itens[i] é um ponteiro
            std::cout << "[" << (i + 1) << "] " 
                      << itens[i]->getNome() 
                      << " (" << itens[i]->getTipo() << ")" 
                      << std::endl;
        }
    }

    // 3. Mostra opções de navegação
    std::cout << "\n----------------------------------------" << std::endl;
    std::cout << "Digite o numero do item para ver detalhes" << std::endl;
    std::cout << "Ou digite 0 para Voltar" << std::endl;

    // 4. Usa a leitura segura da TelaBase
    return lerOpcao();
}