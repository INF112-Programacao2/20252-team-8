#include "TelaLoja.h"
#include "ControladorLoja.h"
#include "Constantes.h"
#include <iostream>
#include <vector>

int TelaLoja::exibir(Usuario* usuario) {
    limparTela();
    
    ControladorLoja ctrl(0); 

    std::cout << "=== LOJA DE MUSICAS ===" << std::endl;
    std::cout << "Seu saldo: " << usuario->getMoedas() << std::endl;
    std::cout << "-----------------------" << std::endl;

    // Pega a lista de músicas do controlador
    std::vector<Musica>& listaMusicas = ctrl.getMusicas();

    if (listaMusicas.empty()) {
        std::cout << "Nenhuma musica disponivel no momento." << std::endl;
    } else {
        // Lista as músicas com numeração (1, 2, 3...)
        for (size_t i = 0; i < listaMusicas.size(); i++) {
            std::cout << (i + 1) << ". " << listaMusicas[i].nome 
                 << " (Preco: " << listaMusicas[i].valor << ")" << std::endl;
        }
    }

    std::cout << "-----------------------" << std::endl;
    std::cout << "Digite o numero da musica para comprar ou 0 para voltar: ";

    int opcao;
    std::cin >> opcao;

    if (opcao == 0) {
        return TELA_PRINCIPAL; // Volta pro menu
    }

    // Verifica se a opção é válida (dentro do tamanho do vetor)
    if (opcao > 0 && (size_t)opcao <= listaMusicas.size()) {
        
        // O vetor começa em 0, mas o menu começa em 1. Então diminuímos 1.
        int indice = opcao - 1; 
        
        // Chama o método de compra
        bool sucesso = ctrl.comprarMusica(indice);

        if (sucesso) {
            Musica m = listaMusicas[indice];
            if (usuario->getMoedas() >= m.valor) {
                usuario->addMoedas(-m.valor); // Desconta
                // usuario->getInventario().adicionarItem(m); // Adiciona (se Musica for Item)
                std::cout << "Compra realizada com sucesso!" << std::endl;
            } else {
                std::cout << "Saldo insuficiente!" << std::endl;
            }
        } else {
            std::cout << "Nao foi possivel realizar a compra (Erro do controlador)." << std::endl;
        }
    } else {
        std::cout << "Opcao invalida!" << std::endl;
    }

    aguardarEnter();
    return TELA_LOJA; // Recarrega a loja para comprar mais coisas
}