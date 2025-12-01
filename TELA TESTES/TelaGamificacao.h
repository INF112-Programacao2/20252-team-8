#ifndef TELA_GAMIFICACAO_H
#define TELA_GAMIFICACAO_H

#include "TelaBase.h"
#include "Usuario.h"

class TelaGamificacao : public TelaBase {
public:
    // Recebe o usuário como referência constante (apenas leitura)
    int mostrarPerfil(const Usuario& usuario);
};

#endif