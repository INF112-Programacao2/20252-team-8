#ifndef TELA_INVENTARIO_H
#define TELA_INVENTARIO_H

#include "TelaBase.h"

class telaInventario : public TelaBase {
public:
    int exibir(Usuario* usuario) override;
};

#endif