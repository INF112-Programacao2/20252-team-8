#ifndef TELA_PRINCIPAL_H
#define TELA_PRINCIPAL_H

#include "TelaBase.h"
#include <iostream>


class telaPrincipal : public telaBase {
    private:
        void mostrarLoja();
        void mostrarPerfil();
        void mostrarInventario();
        void mostrarMenuEstudo();

    public:
        telaPrincipal();
        void exibirTela() override;
};

#endif