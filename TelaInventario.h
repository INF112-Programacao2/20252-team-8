#ifndef TELA_INVENTARIO_H
#define TELA_INVENTARIO_H

#include "TelaBase.h"
#include <iostream>

class telaInventario : public telaBase {
    private:
        void mostrarItensAdquiridos();

    public:
        telaInventario();
        void exibirTela() override;
};

#endif