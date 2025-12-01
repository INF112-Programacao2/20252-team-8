#ifndef CONTROLADOR_PRINCIPAL_H
#define CONTROLADOR_PRINCIPAL_H

#include "ControladorEstudo.h"
#include "ControladorGamificacao.h"
#include "ControladorInventario.h"
#include "ControladorLoja.h"
#include "TelaPrincipal.h"

class ControladorPrincipal {
private:
    // --- AGREGAÇÃO (Ponteiros para os sub-controladores) ---
    ControladorEstudo* ctrlEstudo;
    ControladorLoja* ctrlLoja;
    ControladorInventario* ctrlInventario;
    ControladorGamificacao* ctrlGamificacao;

    // --- COMPOSIÇÃO ---
    TelaPrincipal tela;

public:
    // Construtor padrão
    ControladorPrincipal();

    // Setters (Injeção de Dependência conforme sua main.cpp)
    void setControladorEstudo(ControladorEstudo* ctrl);
    void setControladorLoja(ControladorLoja* ctrl);
    void setControladorInventario(ControladorInventario* ctrl);
    void setControladorGamificacao(ControladorGamificacao* ctrl);

    // O Loop principal do programa
    void executar();
};

#endif