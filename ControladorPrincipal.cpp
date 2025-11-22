#include "ControladorPrincipal.h"
#include "Constantes.h"
#include "TelaPrincipal.h"
#include "TelaPerfil.h"
#include "TelaLoja.h"
#include "TelaInventario.h"
#include "TelaEstudo.h"
#include <iostream>

ControladorPrincipal::ControladorPrincipal(Usuario* u) {
    this->usuario = u;
}

void ControladorPrincipal::iniciar() {
    int proximaTela = TELA_PRINCIPAL;

    while (proximaTela != TELA_SAIR) {
        
        TelaBase* telaAtual = nullptr;

        // Fábrica de telas usando IF/ELSE em vez de SWITCH
        if (proximaTela == TELA_PRINCIPAL) {
            telaAtual = new TelaPrincipal();
        } 
        else if (proximaTela == TELA_PERFIL) {
            telaAtual = new TelaPerfil();
        }
        else if (proximaTela == TELA_LOJA) {
            telaAtual = new TelaLoja();
        }
        else if (proximaTela == TELA_INVENTARIO) {
            telaAtual = new TelaInventario();
        }
        else if (proximaTela == TELA_ESTUDO) {
            telaAtual = new TelaEstudo();
        }

        // Executa e depois deleta
        if (telaAtual != nullptr) {
            proximaTela = telaAtual->exibirTela(usuario);
            delete telaAtual; // Gerenciamento de memória!
        } else {
            std::cout << "Erro fatal: Tela nao encontrada." << std::endl;
            proximaTela = TELA_SAIR;
        }
    }
}