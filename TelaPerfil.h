#ifndef TELA_PERFIL_H
#define TELA_PERFIL_H

#include "TelaBase.h"
#include <iostream>

class telaPerfil : public telaBase {
    private:
        void mostrarDadosUsuario();
        void mostrarOpcoesEdicao();
        void mostrarEstatisticas();
    public:
        telaPerfil();
        void exibirTela() override;
};

#endif