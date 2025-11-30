#include "TelaInventario.h"
#include "ControladorInventario.h"
#include "Constantes.h"
#include <iostream>
#include <vector>

int telaInventario::exibir(Usuario* usuario) {
    limparTela();
    std::cout << "=== INVENTARIO ===" << std::endl;
    
    std::vector<Item> itens = usuario->getInventario().getItens();
    if(itens.empty()) {
        std::cout << "(Vazio)" << std::endl;
    } else {
        for(size_t i=0; i<itens.size(); i++) {
             std::cout << "- " << itens[i].getNome() << std::endl;
        }
    }
    
    std::cout << "0. Voltar" << std::endl;
    int op;
    std::cin >> op;
    return TELA_PRINCIPAL;
}