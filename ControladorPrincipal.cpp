#include "ControladorPrincipal.h"
#include "ControladorEstudo.h"
#include "ControladorLoja.h"
#include "ControladorInventario.h"
#include "ControladorGamificacao.h"
#include "Constantes.h"

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
            case TELA_ESTUDO: // Estudos
                if (ctrlEstudo) ctrlEstudo->executar();
                else tela.mostrarErro("Controlador de Estudo nao configurado!");
                break;

            case TELA_LOJA: // Loja
                if (ctrlLoja) ctrlLoja->executar();
                else tela.mostrarErro("Controlador de Loja nao configurado!");
                break;

            case TELA_INVENTARIO: // Inventário
                if (ctrlInventario) ctrlInventario->executar();
                else tela.mostrarErro("Controlador de Inventario nao configurado!");
                break;

            case TELA_PERFIL: // Gamificação (Perfil)
                if (ctrlGamificacao) ctrlGamificacao->executar();
                else tela.mostrarErro("Controlador de Gamificacao nao configurado!");
                break;

            case TELA_SAIR:
            case 0: // Sair
                tela.limparTela();
                tela.mostrarMensagem("Saindo... Bons estudos!");
                rodando = false;
                break;

            default:
                break;
        }
    }
}