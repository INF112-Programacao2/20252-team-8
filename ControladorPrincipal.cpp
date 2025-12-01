#include "ControladorPrincipal.h"
#include "ControladorEstudo.h"
#include "ControladorLoja.h"
#include "ControladorInventario.h"
#include "ControladorGamificacao.h"

ControladorPrincipal::ControladorPrincipal() 
    : ctrlEstudo(nullptr), ctrlLoja(nullptr), 
      ctrlInventario(nullptr), ctrlGamificacao(nullptr) {
}

// Setters
void ControladorPrincipal::setControladorEstudo(ControladorEstudo* ctrl) {
    this->ctrlEstudo = ctrl;
}
void ControladorPrincipal::setControladorLoja(ControladorLoja* ctrl) {
    this->ctrlLoja = ctrl;
}
void ControladorPrincipal::setControladorInventario(ControladorInventario* ctrl) {
    this->ctrlInventario = ctrl;
}
void ControladorPrincipal::setControladorGamificacao(ControladorGamificacao* ctrl) {
    this->ctrlGamificacao = ctrl;
}

// Lógica de Roteamento
void ControladorPrincipal::executar() {
    bool rodando = true;
    Usuario* usuario = ctrlGamificacao->getUsuario();

    while (rodando) {
        int opcao = tela.exibir(usuario);

        switch (opcao) {
            case 1: // Estudos
                if (ctrlEstudo) ctrlEstudo->executar();
                else tela.mostrarErro("Controlador de Estudo nao configurado!");
                break;

            case 2: // Loja
                if (ctrlLoja) ctrlLoja->executar();
                else tela.mostrarErro("Controlador de Loja nao configurado!");
                break;

            case 3: // Inventário
                if (ctrlInventario) ctrlInventario->executar();
                else tela.mostrarErro("Controlador de Inventario nao configurado!");
                break;

            case 4: // Gamificação (Perfil)
                if (ctrlGamificacao) ctrlGamificacao->executar();
                else tela.mostrarErro("Controlador de Gamificacao nao configurado!");
                break;

            case 0: // Sair
                tela.limparTela();
                tela.mostrarMensagem("Saindo... Bons estudos!");
                rodando = false;
                break;

            default:
                tela.mostrarErro("Opcao invalida!");
        }
    }
}