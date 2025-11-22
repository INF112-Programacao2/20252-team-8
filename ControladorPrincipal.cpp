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

        // Fábrica de telas
        if (proximaTela == TELA_PRINCIPAL) {
            telaAtual = new telaPrincipal();
        } 
        else if (proximaTela == TELA_PERFIL) {
            telaAtual = new telaPerfil();
        }
        else if (proximaTela == TELA_LOJA) {
            telaAtual = new telaLoja();
        }
        else if (proximaTela == TELA_INVENTARIO) {
            telaAtual = new telaInventario();
        }
        else if (proximaTela == TELA_ESTUDO) {
            telaAtual = new telaEstudo();
        }

        // Executa e depois deleta
        if (telaAtual != nullptr) {
            proximaTela = telaAtual->exibir(usuario);
            delete telaAtual;
        } else {
            std::cout << "Erro fatal: Tela nao encontrada." << std::endl;
            proximaTela = TELA_SAIR;
        }
    }
}